#include "stdafx.h"
#include "BackGroundTwo.h"
#include "BackGround.h"
#include"Game.h"
#include"Player.h"
#include"FirstFloor.h"
#include"SecondFloor.h"

BackGroundTwo::BackGroundTwo() {

}

BackGroundTwo::~BackGroundTwo() {

}

bool BackGroundTwo::Start()
{
	modelRender.Init("Assets/modelData/Stage2/Stage2second.tkm");
	modelRender.SetPosition(m_position);
	modelRender.SetScale(m_scale);
	modelRender.Update();

	//PhysicsStaticObjectの初期化
	m_physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());
	return true;
}

void BackGroundTwo::Update() {
	modelRender.SetPosition(m_position);

	//モデルを描画
	modelRender.Update();
}

void BackGroundTwo::Render(RenderContext& rc) {
	modelRender.Draw(rc);
}

