#include "stdafx.h"
#include "Pyramid.h"
#include"SecondFloor.h"
#include"ThirdFloor.h"
#include"Player.h"
#include"Game.h"
#include"Loading.h"

Pyramid::Pyramid() {

}
Pyramid::~Pyramid() {

}

bool Pyramid::Start() {
	m_modelRender.Init("Assets/modelData/Stage2/pyramid/pyramid.tkm");
	
	m_player = FindGO<Player>("Player");
	return true;

}

void Pyramid::Update() {
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(0.01f, 0.01f, 0.01f);
	m_modelRender.Update();
}

void Pyramid::Render(RenderContext& renderContext) {

	m_modelRender.Draw(renderContext);
}