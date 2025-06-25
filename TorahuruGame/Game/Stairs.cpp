#include "stdafx.h"
#include "Stairs.h"
#include"Game.h"
#include"Player.h"
#include"GameClear.h"
#include"FirstFloor.h"
namespace
{
	const Vector3 COLLISION_HEIGHT = Vector3(0.0f, 150.0f, 0.0f);
	const Vector3 COLLISION_SIZE = Vector3(500.0f, 500.0f, 500.0f);//コリジョンの大きさ

}
Stairs::Stairs() {

}
Stairs::~Stairs() {
	
}
bool Stairs::Start() {
	m_modelRender.Init("Assets/modelData/Stage1/Stairs/Stairs.tkm");	//髫取ｮｵ繧ｪ繝悶ず繧ｧ繧ｯ繝・
	
	//繝励Ξ繧､繝､繝ｼ蛛ｴ縺ｮ繧ｪ繝悶ず繧ｧ繧ｯ繝医ｒ謖√▲縺ｦ縺上ｋ
	m_player = FindGO<Player>("player");
	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,	//座標
		Quaternion::Identity,			//回転
		COLLISION_SIZE					//大きさ
	);
	return true;
}

void Stairs::Update() {

	m_modelRender.SetPosition(m_position);
	
	m_modelRender.Update();	
}

void Stairs::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}