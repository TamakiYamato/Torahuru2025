#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "Tutorial.h"

namespace

{
	// 逕ｻ蜒上・菴咲ｽｮ縲・
	//Vector3 TEXT_POSITION = Vector3(-500.0f, 500.0f, 0.0f);
	Vector3 TEXT_POSITION = Vector3(500.0f, 500.0f, 0.0f);
	// 逕ｻ蜒上・螟ｧ縺阪＆縲・
	Vector3 TEXT_SCALE = Vector3(0.5f, 0.5f, 0.5f);
	Vector3 SCALE = Vector3{ 5.0f,5.0f,5.0f };
	Vector4 TEXT_COLOR = Vector4::White;
}

Tutorial::Tutorial()
{

}

Tutorial::~Tutorial()
{

}

bool Tutorial::Start()
{
	// 繝懊ャ繧ｯ繧ｹ繧定ｪｭ縺ｿ霎ｼ繧縲・
	m_modelRender.Init("Assets/Tutorial/TutorialObject.tkm");
	// 逕ｻ蜒上ｒ隱ｭ縺ｿ霎ｼ繧縲・
	// 縺ゅ∋縺薙∋蠎翫・
	m_spriteRender.Init("Assets/Tutorial/reverseTutorial1.DDS", 600.0f, 250.0f);
	// 菴咲ｽｮ縲・
	//m_spriteRender.SetPosition((m_position));
	//m_spriteRender.SetPosition((TEXT_POSITION));

	// 螟ｧ縺阪＆縲・
	m_modelRender.SetScale(Vector3(SCALE));
	//m_fontRender.SetText(L"縺ゅ∋縺薙∋蠎・);
	//m_fontRender.SetPosition((TEXT_POSITION));
	//m_fontRender.SetColor((TEXT_COLOR));
	return true;
}

void Tutorial::HintText()
{
	
}

void Tutorial::Update()
{
	// 繝昴ず繧ｷ繝ｧ繝ｳ縲・
	m_modelRender.SetPosition(m_position);
	// 譖ｴ譁ｰ蜃ｦ逅・・
	m_modelRender.Update();
	m_spriteRender.Update();

	
}

void Tutorial::Render(RenderContext& rc)
{
	// 繝｢繝・Ν繝ｬ繝ｳ繝繝ｼ
	m_modelRender.Draw(rc);
	// 繧ｹ繝励Λ繧､繝医Ξ繝ｳ繝繝ｼ縲・
	m_spriteRender.Draw(rc);
	// 繝輔か繝ｳ繝医Ξ繝ｳ繝繝ｼ縲・
	m_fontRender.Draw(rc);
}

