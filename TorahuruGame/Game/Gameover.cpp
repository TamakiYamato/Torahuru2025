#include "stdafx.h"
#include "Gameover.h"
#include"Game.h"
#include"Player.h"
#include"Title.h"
#include "GameManager.h"

Gameover::Gameover() {

}
Gameover::~Gameover() {

}

bool Gameover::Start()
{

	m_spriteRender.Init("Assets/modelData/Gameover/gameover.DDS", 1920, 1080);
	
	return true;
}

void Gameover::Update() {
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_isReturnTitle = true;
	}
	if (m_isReturnTitle) {
		m_isReturnTitle = false;
		m_gameManager = FindGO<GameManager>("gameManager");
		m_gameManager->CreateTitle();
		m_gameManager->DeleteGameOver();
	}

	m_spriteRender.Update();
}
void Gameover::Render(RenderContext& rc) {
	m_spriteRender.Draw(rc);
}