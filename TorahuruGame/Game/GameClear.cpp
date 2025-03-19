#include "stdafx.h"
#include "GameClear.h"
#include"Game.h"
#include"Player.h"
#include"kaidan.h"
#include"Title.h"
GameClear::GameClear() {
	m_spriteRender.Init("Assets/modelData/takatora.DDS", 1920, 1080);


}
GameClear::~GameClear() {
	
}
void GameClear::Update() {
	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(this);//自身を削除する
		NewGO<Title>(0, "title");
		
		

	}
	//画像の更新。
	m_spriteRender.Update();
}
void GameClear::Render(RenderContext& rc) {
	//画像の描画。
	m_spriteRender.Draw(rc);
}