#include "stdafx.h"
#include "TutorialUI.h"
#include "Tutorial.h"
#include "Player.h"
#include "Game.h"

namespace
{
	// 距離。
// constで定義した変数を変更不可にする。(不可にする)
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
	// 火炎放射器とプレイヤーの距離を計算する。
	Vector3 toTextLenght = m_game->m_tutorial4->m_position - m_player->m_position;
	float disToTextLenght = toTextLenght.Length();
	// もし距離が100以下だったら。
	if (disToTextLenght <= LENGTH)
	{
		// 画像を表示。
		NewGO<Tutorial>(0, "tutorial");
	}
	// それ以外。
	//else
	//{
	//	// 表示しない。
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