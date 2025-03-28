#include "stdafx.h"
//#include "Floor1.h"
//#include"Game.h"
//#include"Player.h"
//
//Floor1::Floor1() {
//
//}
//Floor1::~Floor1() {
//
//}
//
//bool Floor1::Start()
//{
//	m_modelRender.Init("Assets/modelData/tokusyuyuka2.tkm");
//	m_modelRender.SetPosition(m_position);
//	
//	m_modelRender.SetScale(m_scale);
//
//	m_modelRender.Update();
//
//	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
//
//	m_defPosition = m_position;	//èâä˙ç¿ïWÇê›íËÅB
//
//	return true;
//}
//void Floor1::Update() {
//	m_modelRender.SetPosition(m_position);
//
//	m_modelRender.Update();
//}
//void Floor1::Render(RenderContext& rc) {
//	m_modelRender.Draw(rc);
//}