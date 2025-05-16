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

TutorialUI::TutorialUI()
{
	
}

TutorialUI::~TutorialUI()
{

}

bool TutorialUI::Start()
{
	Show();			//最初のUIの表示
	PanelUI();		//UIパネルの表示
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_floorManager = FindGO<FloorManager>("floorManager");
	return true;
}

void TutorialUI::Update()
{
	m_spriteRender.Update();
	if (onGimmicPassed == true) {
		Cheak();	//次のUIステートに変更
		Show();		//UIを表示
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
void TutorialUI::Show()
{
	wchar_t textUI[256];
	switch (m_textState) {
	case reverse:
		swprintf_s(textUI, 256, L"< チュートリアル >\n火炎放射器に当たるとノックバックが発生！\nあべこべ床を踏むと操作が反転する。");
		break; 
	case slow:
		swprintf_s(textUI, 256, L"< チュートリアル >\n鈍足床を踏むと移動速度が半減する。\n一つの床の効果を受けるとその他の床の効果は受けない。");
																						
		break; 
	case blind:
		swprintf_s(textUI, 256, L"< チュートリアル >\n視界制限床を踏むと一定範囲内が暗くなる。");
		break;
	case Stairs:
		swprintf_s(textUI, 256, L"< チュートリアル >\nクリア条件を満たして階段に触れると、\n次のフロアへ進むことができる。");
		break;
	case CollectItems:
		swprintf_s(textUI, 256, L"< 条件 >\n3つのアイテムを集めて階段へ行こう！");
		break;
	case SolvePuzzle:
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
	onGimmicPassed = false;
}
/// <summary>
/// 次のUIを表示するかの判定
/// </summary>
void TutorialUI::Cheak()
{
	switch (m_textState) {
	case reverse:
		if (onGimmicPassed == true) {	//あべこべ床を踏んだ場合
			m_textState = slow;			//UIを鈍足床に変更
		}
		break;

	case slow:
		if (onGimmicPassed == true) {		//鈍足床を踏んだ場合
			m_textState = blind;		//UIを視界制限床に変更
		}
		break;
	case blind:		
		if (onGimmicPassed == true) {	//視界制限床を踏んだ場合
			m_textState = Stairs;		//UIを階段用に変更
		}
		break;

	case Stairs:
		//if (m_game-> == m_game->floor2) {						//プレイヤーがフロア2に移動した場合
		//	onGimmicPassed = true;
		//	m_textState = CollectItems;	//UIをフロア２クリア条件用に変更
		//}
		break;

	case CollectItems:
		//if (m_game->playerFloor == m_game->floor3) {						//プレイヤーがフロア３に移動した場合
		//	onGimmicPassed = true;
		//	m_textState = SolvePuzzle;	//UIをフロア３クリア条件用に変更
		//}
		break;

	default:
		break;
	}
	
}

void TutorialUI::PanelUI()
{
	m_spriteRender.Init("Assets/modelData/item/UIPanel1.dds", 600.0f, 100.0f);
	m_spriteRender.SetPosition(Vector3(-550.0f, 290.0f, 0.0f));
	m_spriteRender.SetScale(Vector3(1.2f, 1.2f, 1.0f));
	m_spriteRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.7f));
}
