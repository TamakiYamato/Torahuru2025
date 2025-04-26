#include "stdafx.h"
#include "TutorialUI.h"
#include "Tutorial.h"
#include "Player.h"
#include "Game.h"

namespace
{
	// 霍晞屬縲・
// const縺ｧ螳夂ｾｩ縺励◆螟画焚繧貞､画峩荳榊庄縺ｫ縺吶ｋ縲・荳榊庄縺ｫ縺吶ｋ)
	const float LENGTH = 1500;
}

TutorialUI::TutorialUI()
{

}

TutorialUI::~TutorialUI()
{

}

bool TutorialUI::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	return true;
}

void TutorialUI::Update()
{
	// 轣ｫ轤取叛蟆・勣縺ｨ繝励Ξ繧､繝､繝ｼ縺ｮ霍晞屬繧定ｨ育ｮ励☆繧九・
	Vector3 toTextLenght = m_game->m_tutorial4->m_position - m_player->m_position;
	float disToTextLenght = toTextLenght.Length();
	// 繧ゅ＠霍晞屬縺・00莉･荳九□縺｣縺溘ｉ縲・
	if (disToTextLenght <= LENGTH)
	{
		// 逕ｻ蜒上ｒ陦ｨ遉ｺ縲・
		NewGO<Tutorial>(0, "tutorial");
	}
	// 縺昴ｌ莉･螟悶・
	//else
	//{
	//	// 陦ｨ遉ｺ縺励↑縺・・
	//	DeleteGO(this);
	//	m_text = State_Normal;
	//}
}

void TutorialUI::Render(RenderContext& rc)
{
	/*switch (m_text)
	{
	case State_Fire:

		break;
	}*/
}