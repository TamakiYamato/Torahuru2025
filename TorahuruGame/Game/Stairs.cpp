#include "stdafx.h"
#include "Stairs.h"
#include"Game.h"
#include"Player.h"
#include"GameClear.h"
Stairs::Stairs() {

}
Stairs::~Stairs() {
	MessageBox(NULL, L"Stairs Deleted", L"Debug", MB_OK);
}
bool Stairs::Start() {
	m_modelRender.Init("Assets/modelData/kaidan.tkm");//階段オブジェクト
	
	//プレイヤー側のオブジェクトを持ってくる
	m_player = FindGO<Player>("player");
	return true;
}
void Stairs::Update() {

	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

	Vector3 diff = m_player->m_position - m_position;
    
	if (diff.Length() <= 100.0f)
	{
		NewGO<GameClear>(0, "GameClear");
		//m_player->StairsCount =1; 
		//MessageBox(NULL, L"階段がきえたよ!", L"Debug", MB_OK);
		DeleteGO(this);
	}
	
}

void Stairs::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}