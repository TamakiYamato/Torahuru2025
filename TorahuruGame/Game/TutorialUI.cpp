#include "stdafx.h"
#include "TutorialUI.h"
#include "ReverseFloor.h"
#include "FloorManager.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "Player.h"
#include "Game.h"

namespace
{

}

bool TutorialUI::Start()
{
	DisplayText();			//最初のUIの表示
	InitBackTextBoxColor();		//UIパネルの表示
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_floorManager = FindGO<FloorManager>("floorManager");
	return true;
}

void TutorialUI::Update()
{
	m_spriteRender.Update();
	if (m_onGimmicPassed == true) {
		CheckNextUIFlag();	//次のUIステートに変更
		DisplayText();		//UIを表示
	}
}

void TutorialUI::Render(RenderContext& rc)
{
	//画像の描画
	m_spriteRender.Draw(rc);
	//文字の描画
	m_fontRender.Draw(rc);
}

/// <summary>
/// テキストの表示
/// </summary>
void TutorialUI::DisplayText()
{
	wchar_t textUI[256];
	switch (m_textState) {
	case enReverse:
		swprintf_s(textUI, 256, L"< チュートリアル >\n火炎放射器に当たるとノックバックが発生！\nあべこべ床を踏むと操作が反転する。");
		break; 

	case enSlow:
		swprintf_s(textUI, 256, L"< チュートリアル >\n鈍足床を踏むと移動速度が半減する。\n一つの床の効果を受けるとその他の床の効果は受けない。");
																						
		break; 

	case enBlind:
		swprintf_s(textUI, 256, L"< チュートリアル >\n視界制限床を踏むと一定範囲内が暗くなる。");
		break;

	case enStairs:
		swprintf_s(textUI, 256, L"< チュートリアル >\nクリア条件を満たして階段に触れると、\n次のフロアへ進むことができる。");
		break;

	case enCollectItem:
		swprintf_s(textUI, 256, L"< 条件 >\n3つのアイテムを集めて階段へ行こう！");
		break;

	case enSolvePuzzle:
		swprintf_s(textUI, 256, L"< 特殊 > ステージのどこにいても敵が追いかけてくる。\n< 条件 > ステージ内のどこかにある絵が描かれた石を\n同じ方向に向けて扉から出よう！");
		break; 

	default:
		break;
	}
	// 文字のセット
	m_fontRender.SetText(textUI);
	// 文字の座標
	m_fontRender.SetPosition(Vector3(-880.0f, 340.0f, 0.0f));
	// 文字の大きさ
	m_fontRender.SetScale(0.6f);
	// 文字の色
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });
	//次のテキストがでないようにする。
	m_onGimmicPassed = false;
}
/// <summary>
/// 次のUIを表示するかの判定
/// </summary>
void TutorialUI::CheckNextUIFlag()
{
	switch (m_textState) {
	case enUIText::enReverse:
		if (m_onGimmicPassed == true) {	//あべこべ床を踏んだ場合
			m_textState = enSlow;			//UIを鈍足床に変更
		}
		break;

	case enUIText::enSlow:
		if (m_onGimmicPassed == true) {		//鈍足床を踏んだ場合
			m_textState = enBlind;		//UIを視界制限床に変更
		}
		break;
	case enUIText::enBlind:
		if (m_onGimmicPassed == true) {	//視界制限床を踏んだ場合
			m_textState = enStairs;		//UIを階段用に変更
		}
		break;

	case enStairs:
		//if (m_game-> == m_game->floor2) {						//プレイヤーがフロア2に移動した場合
		//	onGimmicPassed = true;
		//	m_textState = CollectItems;	//UIをフロア２クリア条件用に変更
		//}
		break;

	case enCollectItem:
		//if (m_game->playerFloor == m_game->floor3) {						//プレイヤーがフロア３に移動した場合
		//	onGimmicPassed = true;
		//	m_textState = SolvePuzzle;	//UIをフロア３クリア条件用に変更
		//}
		break;

	default:
		break;
	}
	
}

void TutorialUI::InitBackTextBoxColor()
{
	m_spriteRender.Init("Assets/Tutorial/UIPanel1.dds", 600.0f, 100.0f);
	m_spriteRender.SetPosition(Vector3(-550.0f, 290.0f, 0.0f));
	m_spriteRender.SetScale(Vector3(1.2f, 1.2f, 1.0f));
	m_spriteRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.7f));
}
