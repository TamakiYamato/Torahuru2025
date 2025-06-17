#include "stdafx.h"
#include "BlindFloor.h"
#include "Player.h"
#include "Enemy.h"
#include "collision/CollisionObject.h"

namespace
{
	const Vector3 COLLISION_HEIGHT	(0.0f, 10.0f, 0.0f);
	const Vector3 COLLISION_SIZE	(360.0f, 150.0f, 370.0f);
}

BlindFloor::BlindFloor()
{

}

BlindFloor::~BlindFloor()
{
	DeleteGO(m_collisionObject);	//コリジョンオブジェクトを削除
}

bool BlindFloor::Start()
{
	m_modelRender.Init("Assets/modelData/BlindFloor/BlindFloor.tkm");		//モデルを実装
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,	//座標
		Quaternion::Identity,			//回転
		COLLISION_SIZE					//大きさ
	);

	m_player = FindGO<Player>("player");

	m_collisionObject->SetIsEnableAutoDelete(false);	//自動で削除されないようにする
	return true;
}

void BlindFloor::BlindControlFloor()
{
	//コリジョンとplayerが当たった場合
	//floorManagerで効果を与える
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		m_onPlayerBlindFloor = true;
	}
	else
	{
		m_onPlayerBlindFloor = false;
	}

}

void BlindFloor::Update()
{
	BlindControlFloor();
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void BlindFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}


