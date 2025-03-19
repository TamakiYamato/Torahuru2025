#include "stdafx.h"
#include "kaidan.h"
#include"Game.h"
#include"Player.h"
#include"Title.h"
#include"GameClear.h"
kaidan::kaidan() {

}
kaidan::~kaidan() {

}
bool kaidan::Start() {

	m_modelRender.Init("Assets/modelData/kaidan.tkm");
	
	m_modelRender.SetPosition(m_position);

	m_modelRender.SetScale(m_scale);

	m_modelRender.Update();

	m_player = FindGO<Player>("player");

	return true;
}

void kaidan::Update() {

	


	Vector3 diff = m_player->m_position - m_position;

	if (diff.Length() < 100.0f) {
		m_player->ClearCount++;
	    NewGO<GameClear>(0, "gameclear");
		
		DeleteGO(this);
	}
	m_modelRender.Update();
}
void kaidan::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}