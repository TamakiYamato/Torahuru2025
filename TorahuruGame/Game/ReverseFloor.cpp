#include "stdafx.h"
#include "ReverseFloor.h"
#include "Player.h"
#include "collision/CollisionObject.h"

namespace 
{
	const Vector3 COLLISION_HEIGHT = Vector3(0.0f, 0.0f, 10.0f);
	const Vector3 COLLISION_SIZE = Vector3(200.0f, 150.0f, 300.0f);
}

ReverseFloor::ReverseFloor()
{

}

ReverseFloor::~ReverseFloor()
{

}

bool ReverseFloor::Start()
{
	//m_modelRender.Init("Assets/modelData/background/ReverseFloor.tkm");		//あべこべ床の読み込み。
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,	//判定の座標。
		Quaternion::Identity,			//判定の回転。
		COLLISION_SIZE					//判定の大きさ。
	);

	m_player = FindGO<Player>("player");

	m_collisionObject->SetIsEnableAutoDelete(false);	//コリジョンが消えないようにする。
	return true;
}

void ReverseFloor::ReverseControlFloor()
{
	//プレイヤーが床の上にいたらtrue。
	//player.hにて効果を発動
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		m_onReverseFloor = true;
	}
	else
	{
		m_onReverseFloor = false;
	}
}

void ReverseFloor::Update()
{
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void ReverseFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

}


