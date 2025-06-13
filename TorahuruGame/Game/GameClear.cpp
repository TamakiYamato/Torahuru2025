#include "stdafx.h"
#include "GameClear.h"
#include"Stairs.h"
#include"Player.h"
#include"Enemy.h"
#include"Title.h"

GameClear::GameClear()
{

}

GameClear::~GameClear() {

}

bool GameClear:: Start() {
	
	m_spriteRender.Init("Assets/modelData/GameClear/GameClear.DDS", 1920, 1080);
	m_player = FindGO<Player>("player");
	m_stairs = FindGO<Stairs>("stairs");

	return true;
}
void GameClear::Update()
{

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(m_player);
		DeleteGO(m_stairs);

		NewGO<Title>(0, "title");
		DeleteGO(this);
		//閾ｪ霄ｫ繧貞炎髯､縺吶ｋ
	}
	//逕ｻ蜒上・譖ｴ譁ｰ縲・
	m_spriteRender.Update();
}


void GameClear::Render(RenderContext& rc)
{
	//逕ｻ蜒上・謠冗判縲・
	m_spriteRender.Draw(rc);
}