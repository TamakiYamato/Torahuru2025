#include "stdafx.h"
#include "BackGround.h"
#include"Game.h"
#include"Player.h"

BackGround::BackGround() {
	modelRender.Init("Assets/modelData/Stage1.tkm");

	modelRender.Update();
}
BackGround::~BackGround() {

}
bool BackGround::Start()
{

	//	//蠖薙◆繧雁愛螳壹ｒ菴懈・縺吶ｋ縲・
	m_physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());
	//蠖薙◆繧雁愛螳壹ｒ蜿ｯ隕門喧縺吶ｋ縲・
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}
void BackGround::Render(RenderContext& rc) {
	modelRender.Draw(rc);
}
void BackGround::Update() {
	//繝｢繝・Ν縺ｮ譖ｴ譁ｰ蜃ｦ逅・・
	modelRender.Update();
}
