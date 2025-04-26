#include "stdafx.h"
#include "BlindFloor.h"
#include "Player.h"
#include "collision/CollisionObject.h"

namespace
{
	const Vector3 COLLISION_HEIGHT	= Vector3(0.0f, 10.0f, 0.0f);
	const Vector3 COLLISION_SIZE	= Vector3(360.0f, 150.0f, 370.0f);
}

BlindFloor::BlindFloor()
{

}

BlindFloor::~BlindFloor()
{
}

bool BlindFloor::Start()
{
	m_modelRender.Init("Assets/modelData/BlindFloor.tkm");		//隕也阜蛻ｶ髯仙ｺ翫・隱ｭ縺ｿ霎ｼ縺ｿ縲・
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,	//蛻､螳壹・蠎ｧ讓吶・
		Quaternion::Identity,			//蛻､螳壹・蝗櫁ｻ｢縲・
		COLLISION_SIZE					//蛻､螳壹・螟ｧ縺阪＆縲・
	);

	m_player = FindGO<Player>("player");

	m_collisionObject->SetIsEnableAutoDelete(false);	//繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ縺梧ｶ医∴縺ｪ縺・ｈ縺・↓縺吶ｋ縲・
	return true;
}

void BlindFloor::BlindControlFloor()
{
	//繝励Ξ繧､繝､繝ｼ縺悟ｺ翫・荳翫↓縺・◆繧液rue縲・
	//player.h縺ｫ縺ｦ蜉ｹ譫懊ｒ逋ｺ蜍輔・
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		m_onBlindFloor = true;
	}
	else
	{
		m_onBlindFloor = false;
	}
}

void BlindFloor::Update()
{
	BlindControlFloor();
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void BlindFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

}


