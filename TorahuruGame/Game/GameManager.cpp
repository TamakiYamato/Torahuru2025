#include "stdafx.h"
#include "GameManager.h"
#include "Title.h"
#include "Loading.h"
#include "Game.h"
#include "GameClear.h"
#include "Gameover.h"

bool GameManager::Start() 
{
	CreateTitle();
	return true;
}
void GameManager::Update() 
{
	if (m_title == nullptr) {
		m_title = FindGO<Title>("title");
	}
	if (m_loading == nullptr) {
		m_loading = FindGO<Loading>("loading");
	}
	if (m_game == nullptr) {
		m_game = FindGO<Game>("game");
	}

}
