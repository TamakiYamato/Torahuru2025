#include "stdafx.h"
#include "BackGroundThree.h"
#include"ThirdFloor.h"
BackGroundThree::BackGroundThree()
{
}

BackGroundThree::~BackGroundThree()
{
}

bool BackGroundThree::Start()
{
	modelRender.Init("Assets/modelData/Stage3/BackGround3.tkm");
	modelRender.SetPosition(m_position);
	modelRender.SetScale(m_scale);
	modelRender.Update();

	//PhysicsStaticObjectの初期化
	m_physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());
	return true;
}

void BackGroundThree::Update()
{
	modelRender.SetPosition(m_position);

	//モデルを描画
	modelRender.Update();
}

void BackGroundThree::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
