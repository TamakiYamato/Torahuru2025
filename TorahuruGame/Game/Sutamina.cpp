#include "stdafx.h"
#include "Sutamina.h"
#include "Player.h"

namespace
{
	// 繧ｹ繧ｿ繝溘リ繝舌・縺ｮ菴咲ｽｮ縲・
	Vector3 SUTAMINA_POSITION = Vector3(0.0f, -400.0f, 0.0f);
	Vector3 SUTAMINA_POSITION2 = Vector3(-240.0f, -400.0f, 0.0f);

	// 繧ｹ繧ｿ繝溘リ繝舌・縺ｮ螟ｧ縺阪＆縲・
	Vector3 SUTAMINA_SCALE = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 SUTAMINA_SCALE2 = Vector3(0.96f, 0.85f, 0.85f);

	// 繝斐・繝・ヨ縲・蜿ｳ遶ｯ蜴溽せ)
	Vector2 SET_PIVOT = Vector2(0.0f, 0.5f);
	//
	//Vector3 SCALE = Vector3{ 0.425f,0.48f,0.5f };
	Vector3 SCALE = Vector3{ 0.8f,0.5f,0.5f };
}

Sutamina::Sutamina()
{

}

Sutamina::~Sutamina()
{

}

bool Sutamina::Start()
{
	// 逕ｻ蜒上ｒ隱ｭ縺ｿ霎ｼ繧縲・
	// 繧ｹ繧ｿ繝溘リ繝舌・(譫邨・∩)縺ｮ逕ｻ蜒上・
	m_spriteRender.Init("Assets/PlayerUI/sutaminaBar.DDS", 500.0f, 100.0f);
	// 繧ｹ繧ｿ繝溘リ繝舌・(貂帙ｉ縺咎Κ蛻・縺ｮ逕ｻ蜒上・
	m_spriteRender2.Init("Assets/PlayerUI/sutamina.DDS", 500.0f, 100.0f);

	// player繧呈爾縺吶や・謗｢縺輔↑縺・→nullptr蛻､螳壹↓縺ｪ繧九・
	m_player = FindGO<Player>("player");

	// 繧ｹ繧ｿ繝溘リ繝舌・(譫邨・縺ｮ菴咲ｽｮ縲・
	m_spriteRender.SetPosition(Vector3(SUTAMINA_POSITION));
	// 繧ｹ繧ｿ繝溘リ繝舌・(貂帙ｉ縺咎Κ蛻・縺ｮ菴咲ｽｮ縲・
	m_spriteRender2.SetPosition(Vector3(SUTAMINA_POSITION2));

	// 繧ｹ繧ｿ繝溘リ繝舌・(譫邨・∩)縺ｮ螟ｧ縺阪＆縲・
	m_spriteRender.SetScale(Vector3(SUTAMINA_SCALE));
	// 繧ｹ繧ｿ繝溘リ繝舌・(貂帙ｉ縺咎Κ蛻・縺ｮ螟ｧ縺阪＆縲・
	m_spriteRender2.SetScale(Vector3(SUTAMINA_SCALE2));

	// 繝斐・繝・ヨ縺ｮ菴咲ｽｮ縲・
	m_spriteRender2.SetPivot(Vector2(SET_PIVOT));

	return true;
}

void Sutamina::SutaminaCalk()
{
		// 繝励Ξ繧､繝､繝ｼ縺ｮ譛螟ｧ繧ｹ繧ｿ繝溘リ縺ｮ蛟､縲・
		float MaxVitality = m_player->m_max_sutamina;
		// 繝励Ξ繧､繝､繝ｼ縺ｮ迴ｾ蝨ｨ縺ｮ繧ｹ繧ｿ繝溘リ縺ｮ蛟､縲・
		float newVitality = m_player->m_sutamina;
		// 蜑ｲ蜷医ｒ險育ｮ冷・scale縺ｮX蛟､縺ｫ謗帙￠邂冷・繝舌・縺檎ｸｮ蟆上☆繧九・
		float wari = (float)newVitality / (float)MaxVitality;
		Vector3 scal = { SUTAMINA_SCALE2 };
		// 蜑ｲ蜷医・險育ｮ礼ｵ先棡繧剃ｻ｣蜈･縲・
		// 蜑ｲ蜷医・蠢懊§縺ｦ讓ｪ蟷・□縺醍ｸｮ繧√ｋ縲・
		scal.x *= wari;
		m_spriteRender2.SetScale(scal);
}

void Sutamina::Update()
{
	// 繧ｹ繧ｿ繝溘リ險育ｮ励→譖ｴ譁ｰ縲・
	SutaminaCalk();
	// 繧ｹ繝励Λ繧､繝医ｒ譖ｴ譁ｰ縲・
	m_spriteRender.Update();
	m_spriteRender2.Update();
}

void Sutamina::Render(RenderContext& rc)
{
	// 逕ｻ蜒上ｒ謠冗判縲・
	m_spriteRender.Draw(rc);
	m_spriteRender2.Draw(rc);
}