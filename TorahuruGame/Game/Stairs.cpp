#include "stdafx.h"
#include "Stairs.h"
#include"Game.h"
#include"Player.h"
#include"GameClear.h"
#include"FirstFloor.h"

namespace
{
	const Vector3 COLLISION_HEIGHT = Vector3(0.0f, 150.0f, 0.0f);    // 当たり判定の大きさ
	const Vector3 COLLISION_SIZE = Vector3(500.0f, 500.0f, 500.0f); // コリジョンの大きさ
}

bool Stairs::Start()
{
	m_modelRender.Init("Assets/modelData/Stage1/Stairs/Stairs.tkm");

	m_player = FindGO<Player>("player");

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");

	// コリジョンの当たり範囲の設定
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,	// 階段の座標
		Quaternion::Identity,			// 階段の回転
		COLLISION_SIZE					// 階段の大きさ
	);

	return true;
}

void Stairs::Update()
{
	m_modelRender.SetPosition(m_position);
	
	m_modelRender.Update();	
}

void Stairs::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}