#include "stdafx.h"
#include "RotationFloor.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Title.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "FloorManager.h"
#include "Stairs.h"
#include "Stamina.h"
#include "GameClear.h"
#include "Gameover.h"
#include "Loading.h"
#include "FireGimmic.h"
#include "FirstFloor.h"
#include "TutorialUI.h"
#include"SecondFloor.h"
RotationFloor::RotationFloor() {

}

RotationFloor::~RotationFloor() {

}

bool RotationFloor::Start() {
	m_modelRender.Init("Assets/modelData/Stage2/kaitenyuka.tkm");	//髫取ｮｵ繧ｪ繝悶ず繧ｧ繧ｯ繝・

	//繝励Ξ繧､繝､繝ｼ蛛ｴ縺ｮ繧ｪ繝悶ず繧ｧ繧ｯ繝医ｒ謖√▲縺ｦ縺上ｋ
	m_player = FindGO<Player>("player");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void RotationFloor::Update() {
	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();
	
}

void RotationFloor::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}