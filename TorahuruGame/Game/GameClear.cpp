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
	
	m_spriteRender.Init("Assets/modelData/GameClear/GameClear.DDS", 1920, 1080);	//繧ｲ繝ｼ繝繧ｯ繝ｪ繧｢
	m_player = FindGO<Player>("player");
	m_stairs = FindGO<Stairs>("stairs");	//縺薙％縺ｧ繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ繧貞他縺ｳ霎ｼ繧!!

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