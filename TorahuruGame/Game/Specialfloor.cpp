#include "stdafx.h"
#include "Specialfloor.h"
#include"Game.h"
#include"Player.h"

Specialfloor::Specialfloor() {

}
Specialfloor::~Specialfloor() {

}

bool Specialfloor::Start()
{
	m_modelRender.Init("Assets/modelData/tokusyuyuka2.tkm");
	m_modelRender.SetPosition(m_position);
	
	m_modelRender.SetScale(m_scale);

	m_modelRender.Update();

	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_defPosition = m_position;	//èâä˙ç¿ïWÇê›íËÅB

	return true;
}
void Specialfloor::Update() {
	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();
}
void Specialfloor::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}