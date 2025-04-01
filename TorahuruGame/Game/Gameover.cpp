#include "stdafx.h"
#include "Gameover.h"
#include"Game.h"
#include"Player.h"
#include"Title.h"
Gameover::Gameover() {
	m_timer = 0;
}
Gameover::~Gameover() {

}

bool Gameover::Start()
{

	m_spriteRender.Init("Assets/modelData/gameover.DDS", 1920, 1080);//ÉQÅ[ÉÄÉNÉäÉA
	
	return true;
}

void Gameover::Update() {
	m_timer--;
	if (m_timer <=0.0f , g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Title>(0, "Title");
		DeleteGO(this);
	}
	
	m_spriteRender.Update();
}
void Gameover::Render(RenderContext& rc) {
	m_spriteRender.Draw(rc);
}