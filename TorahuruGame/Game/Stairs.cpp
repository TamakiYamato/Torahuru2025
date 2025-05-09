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
	m_modelRender.Init("Assets/modelData/Stairs.tkm");	//髫取ｮｵ繧ｪ繝悶ず繧ｧ繧ｯ繝・
	
	//繝励Ξ繧､繝､繝ｼ蛛ｴ縺ｮ繧ｪ繝悶ず繧ｧ繧ｯ繝医ｒ謖√▲縺ｦ縺上ｋ
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