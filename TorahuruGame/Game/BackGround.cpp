#include "stdafx.h"
#include "BackGround.h"
#include"Game.h"
#include"Player.h"

BackGround::BackGround() {
	modelRender.Init("Assets/modelData/BackGround1.tkm");

	modelRender.Update();
}
BackGround::~BackGround() {

}
bool BackGround::Start()
{

	//	//当たり判定を作成する。
	m_physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());

	return true;
}
void BackGround::Render(RenderContext& rc) {
	modelRender.Draw(rc);
}
void BackGround::Update() {
	//モデルの更新処理。
	modelRender.Update();
}
