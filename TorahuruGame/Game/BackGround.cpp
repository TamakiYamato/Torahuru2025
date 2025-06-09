#include "stdafx.h"
#include "BackGround.h"
#include"Game.h"
#include"Player.h"

BackGround::BackGround() {

}
BackGround::~BackGround() {

}
bool BackGround::Start()
{
	modelRender.Init("Assets/modelData/Stage1/Stage1.tkm");

	modelRender.Update();

	//PhysicsStaticObjectの初期化
	m_physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());
	//蠖薙◆繧雁愛螳壹ｒ蜿ｯ隕門喧縺吶ｋ縲・
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}
void BackGround::Render(RenderContext& rc) {
	modelRender.Draw(rc);
}
void BackGround::Update() {
	//モデルを描画
	modelRender.Update();
}
