#include "stdafx.h"
#include "GameClear.h"
#include"Stairs.h"
#include"Player.h"
#include"Enemy.h"
#include"Title.h"
#include "GameManager.h"

GameClear::GameClear()
{

}

GameClear::~GameClear() {

}

bool GameClear:: Start() {
	
	m_spriteRender.Init("Assets/modelData/GameClear/GameClear.DDS", 1920, 1080);
	return true;
}
void GameClear::Update()
{

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_isReturnTitle = true;
	}
	if(m_isReturnTitle)
	{
		m_gameManager = FindGO<GameManager>("gameManager");
		m_gameManager->CreateTitle();
		m_gameManager->DeleteGameClear();
	}
	//逕ｻ蜒上・譖ｴ譁ｰ縲・
	m_spriteRender.Update();
}


void GameClear::Render(RenderContext& rc)
{
	//逕ｻ蜒上・謠冗判縲・
	m_spriteRender.Draw(rc);
}