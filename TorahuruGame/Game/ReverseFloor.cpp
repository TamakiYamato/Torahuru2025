#include "stdafx.h"
#include "ReverseFloor.h"
#include "Player.h"
#include "collision/CollisionObject.h"

namespace 
{
	const Vector3 COLLISION_HEIGHT = Vector3(0.0f, 10.0f, 0.0f);
	const Vector3 COLLISION_SIZE = Vector3(320.0f, 150.0f, 320.0f);//コリジョンの大きさ

}

ReverseFloor::ReverseFloor()
{

}

ReverseFloor::~ReverseFloor()
{

}

bool ReverseFloor::Start()
{
	m_modelRender.Init("Assets/modelData/Stage1/ReverseFloor/ReverseFloor.tkm");		//あべこべ床の初期化
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,	//座標
		Quaternion::Identity,			//回転
		COLLISION_SIZE					//大きさ
	);

	m_player = FindGO<Player>("player");

	m_collisionObject->SetIsEnableAutoDelete(false);	//自動で消えないようにする
	return true;
}

void ReverseFloor::ReverseControlFloor()
{
	//プレイヤーが床を踏んだかどうかの判定
	//floorManagerにて効果を入れる
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		m_onPlayerReverseFloor = true;
	}
	else
	{
		m_onPlayerReverseFloor = false;
	}
}

void ReverseFloor::Update()
{
	ReverseControlFloor();
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void ReverseFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

}


