#include "stdafx.h"
#include "Stairs.h"
#include"Game.h"
#include"Player.h"
#include"GameClear.h"
Stairs::Stairs() {

}
Stairs::~Stairs() {
	
}
bool Stairs::Start() {
	m_modelRender.Init("Assets/modelData/Stairs.tkm");	//階段オブジェクト
	
	//プレイヤー側のオブジェクトを持ってくる
	m_player = FindGO<Player>("player");
	return true;
}
void Stairs::Update() {

	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();	
}

void Stairs::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}