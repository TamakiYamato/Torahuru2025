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
		DeleteGO(this);//���g���폜����
		NewGO<Title>(0, "title");
		
		

	}
	//�摜�̍X�V�B
	m_spriteRender.Update();
}
void GameClear::Render(RenderContext& rc) {
	//�摜�̕`��B
	m_spriteRender.Draw(rc);
}