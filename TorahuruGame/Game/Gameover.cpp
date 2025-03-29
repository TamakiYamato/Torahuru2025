#include "stdafx.h"
#include "Gameover.h"
#include"Game.h"
#include"Player.h"
#include"Title.h"
Gameover::Gameover() {

}
Gameover::~Gameover() {

}

bool Gameover::Start()
{

	m_spriteRender.Init("Assets/modelData/niji.DDS", 1920, 1080);//ƒQ[ƒ€ƒNƒŠƒA
	
	return true;
}

void Gameover::Update() {

	
	m_spriteRender.Update();

}
void Gameover::Render(RenderContext& rc) {
	m_spriteRender.Draw(rc);
}
