#include "stdafx.h"
#include "GameClear.h"
#include"Stairs.h"
#include"Player.h"
#include"Title.h"

GameClear::GameClear()
{

}

GameClear::~GameClear() {

}

bool GameClear:: Start() {
	
	m_spriteRender.Init("Assets/modelData/takatora2.DDS", 1920, 1080);
	return true;
}
void GameClear::Update()
{

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0, "title");		
		DeleteGO(this);
		//���g���폜����
	}
	//�摜�̍X�V�B
	m_spriteRender.Update();
}


void GameClear::Render(RenderContext& rc)
{
	//�摜�̕`��B
	m_spriteRender.Draw(rc);
}