#include "stdafx.h"
#include "FireTriggerFloor.h"
#include "Player.h"
#include "Enemy.h"

namespace
{
	const Vector3 COLLISION_HEIGHT = Vector3(0.0f, 10.0f, 0.0f);
	const Vector3 COLLISION_SIZE = Vector3(360.0f, 150.0f, 370.0f);
}

bool FireTriggerFloor::Start() 
{
	m_modelRender.Init("Assets/modelData/FireTriggerFloor.tkm"); //モデルを実装
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,	//座標
		Quaternion::Identity,			//回転
		COLLISION_SIZE					//大きさ
	);

	m_player = FindGO<Player>("player");
	//m_enemy = FindGO<Enemy>("enemy");

	m_collisionObject->SetIsEnableAutoDelete(false);	//自動で削除されないようにする
	return true;
}
void FireTriggerFloor::FireTriggerControlFloor()
{
	//コリジョンとplayerが当たった場合
	//floorManagerで効果を与える
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		m_onFireTriggerFloor = true;
	}
	else
	{
		m_onFireTriggerFloor = false;
	}
	//コリジョンとenemyが当たった場合
	if(m_collisionObject->IsHit(m_enemy->GetCharacterController()) == true)
	{
		m_onFireTriggerFloor = true;
	}
	else
	{
		m_onFireTriggerFloor = false;
	}
}
void FireTriggerFloor::Update() 
{
	FireTriggerControlFloor();
}

void FireTriggerFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
