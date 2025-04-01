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
	m_modelRender.Init("Assets/modelData/kaidan.tkm");//階段オブジェクト
	return true;
}
void Stairs::Update() {

	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();//ここで階段を更新する!!(持ってくる)!!
}

void Stairs::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}