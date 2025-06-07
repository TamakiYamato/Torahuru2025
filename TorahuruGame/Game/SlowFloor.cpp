#include "stdafx.h"
#include "SlowFloor.h"
#include "Player.h"
#include "Enemy.h"
#include "collision/CollisionObject.h"

namespace
{
	const Vector3 COLLISION_HEIGHT (0.0f, 10.0f, 0.0f);
	const Vector3 COLLISION_SIZE (320.0f, 150.0f, 320.0f);
}

SlowFloor::SlowFloor()
{

}

SlowFloor::~SlowFloor()
{

}

bool SlowFloor::Start()
{
	m_modelRender.Init("Assets/modelData/SlowFloor.tkm");		//鈍足床の初期化
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,	//座標
		Quaternion::Identity,			//回転
		COLLISION_SIZE					//大きさ
	);

	m_player = FindGO<Player>("player");
	m_enemy = FindGO<Enemy>("enemy");

	m_collisionObject->SetIsEnableAutoDelete(false);	//自動で消えないようにする
	return true;
}

void SlowFloor::SlowControlFloor()
{
	//プレイヤーが床の上にいるかどうか
	//FloorManagerで効果を設定
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		m_onPlayerSlowFloor = true;
	}
	else
	{
		m_onPlayerSlowFloor = false;
	}

	//エネミーが床の上にいるかどうか
	//FloorManagerで効果を設定
	/*if (m_collisionObject->IsHit(m_enemy->GetCharacterController()) == true)
	{
		m_onEnemySlowFloor = true;
	}
	else
	{
		m_onEnemySlowFloor = false;
	}*/
}

void SlowFloor::Update()
{
	SlowControlFloor();
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void SlowFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
