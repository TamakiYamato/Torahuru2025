#include "stdafx.h"
#include "FloorManager.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "Player.h"
#include "Game.h"

namespace {
	const float PLAYER_MOVE_SLOW = 0.5;		//プレイヤーの速度を変更。
}

FloorManager::FloorManager()
{

}

FloorManager::~FloorManager()
{
	
}

bool FloorManager::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");	
	

	return true;
}

void FloorManager::Update()
{
	
	////タイマーが動いてない＝他の床が作動してないとき////
	if (m_floorTimer >= 7.0f) {
		FindFloor();		//3種類の床をすべて見つける
	}

	AddStatus();			//状態ごとの効果反映

	////プレイヤーが床の影響を受けている場合////
	if (m_saveState != Normal) {
		AddStatusTimer();       //状態の時間
		CalcStatusTime();	//効果時間のタイマーを動かす
	}

	////プレイヤーが視界制限状態の場合////
	if (m_saveState == BlindState) {
		pointLightPosition = m_player->m_position +Vector3(0.0f,200.0f,0.0f);
		m_pointL->SetPosition(pointLightPosition);
	}
}


void FloorManager::Render(RenderContext& rc)
{
	if (m_spriteRender) {
		m_spriteRender->Draw(rc);
	}

	if (m_fontRender) {
		m_fontRender->Draw(rc);
	}
}


void FloorManager::FindFloor()
{
	//ステージ内にあるreversefloorをすべて見つける。
	const auto& reverseFloors = FindGOs<ReverseFloor>("ReverseFloor");

	//forはすべてのreversefloorを繰り返す。
	for (auto reverseFloor : reverseFloors) {
		//プレイヤーが床の上にいたとき、操作を逆にする。
		if (reverseFloor->m_onReverseFloor == true) {
			m_floorState = ReverseState;
		}
	}

	///////////////////////////////////////////////////
	//ステージ内にあるslowfloorをすべて見つける。
	const auto& slowFloors = FindGOs<SlowFloor>("SlowFloor");

	//forはすべてのslowfloorを繰り返す
	for (auto slowFloor : slowFloors) {
		//プレイヤーが床の上にいたとき、スピードが半分になる
		if (slowFloor->m_onSlowFloor == true) {
			m_floorState = SlowState;
		}
	}

	//////////////////////////////////////////////////
	//forはすべてのblindfloorを繰り返す
	//ステージ内にあるblindfloorをすべて見つける。
	const auto& blindFloors = FindGOs<BlindFloor>("BlindFloor");

	for (auto blindFloor : blindFloors) {
		//プレイヤーが床の上にいたとき、状態を変更
		if (blindFloor->m_onBlindFloor == true) {
			m_floorState = BlindState;
		}
	}
}


void FloorManager::AddStatus()	/////状態ごとの効果反映/////
{
	if (m_floorTimer == 7.0f) {		//時間が初期化されている＝他の効果がない場合
		if (!m_isAddStatus && m_floorState != Normal) {
			switch (m_floorState) {
			case ReverseState:
				if (m_spriteRender) {
					DeleteGO(m_spriteRender);
				}

				//テクスチャを読み込む
				m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
				m_spriteRender->Init("Assets/sprite/reverse.DDS", 100.0f, 100.0f);
				m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));
				m_player->m_moveDir *= -1.0f;

				AddStatusTimer();

				break;

			case SlowState:
				if (m_spriteRender) {
					DeleteGO(m_spriteRender);
				}

				m_floorTimer -= g_gameTime->GetFrameDeltaTime();

				//テクスチャを読み込む

				m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
				m_spriteRender->Init("Assets/sprite/slow.DDS", 100.0f, 100.0f);
				m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));
				m_player->m_moveDir *= PLAYER_MOVE_SLOW;

				AddStatusTimer();

				break;

			case BlindState:
				if (m_spriteRender) {
					DeleteGO(m_spriteRender);
				}

				m_floorTimer -= g_gameTime->GetFrameDeltaTime();

				//テクスチャを読み込む

				m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
				m_spriteRender->Init("Assets/sprite/blind.DDS", 100.0f, 100.0f);
				m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));

				AddStatusTimer();

				//////////////ステージを暗くする///////////////////////////

				// 環境光の計算のためのIBLテクスチャをセットする。
				g_renderingEngine->SetAmbientByIBLTexture(m_game->m_skyCube->GetTextureFilePath(), 0.01f);

				// シーンの中間の明るさを示す明度率を指定する。
				g_renderingEngine->SetSceneMiddleGray(0.01f);

				// ブルームが発生する閾値を設定。
				// ブルーム…明るい部分がにじむように見える視覚効果、光を強調し、リアル・美しい・幻想的に見せる
				g_renderingEngine->SetBloomThreshold(10.0f);

				//////////////スポットライト//////////////////////////////
				SetPointLight();

				break;
			default:
				break;
			}
			m_saveState = m_floorState;
			m_floorState = Normal;
		}
	}
}

void FloorManager::AddStatusTimer()
{
	//効果時間の表示
	int effectTimer_minute = 0.0f;
	int effectTimer_sec = m_floorTimer;

	m_fontRender = NewGO<FontRender>(0, "fontrender");
	//効果時間タイマーの表示
	wchar_t reverse_text[256];
	swprintf_s(reverse_text, 256, L"%02d:%02d", effectTimer_minute, effectTimer_sec);
	//表示するテキストを設定。
	m_fontRender->SetText(reverse_text);
	//フォントの位置を設定。
	m_fontRender->SetPosition(Vector3(700.0f, 390.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender->SetScale(1.5f);
	//フォントの色を設定。
	m_fontRender->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	
}


void FloorManager::SetPointLight()
{
	m_pointL = NewGO<PointLight>(0,"pointLight");
	
	m_pointL->Init();
	m_pointL->SetPosition(pointLightPosition);
	m_pointL->SetAffectPowParam(0.7f);				//影響力を持たせる。
	m_pointL->SetColor(Vector3(5.0f, 5.0f, 5.0f));
	m_pointL->SetRange(250.0f);
	m_pointL->Update();	
}

void FloorManager::DeletePointLight()
{
	DeleteGO(m_pointL);
}


void FloorManager::CalcStatusTime()
{
	m_floorTimer -= g_gameTime->GetFrameDeltaTime();	//効果時間のカウントダウン7秒
	if (m_floorTimer <= 0) {							//時間が0になった場合
		RevertState();									//床の効果を消す
		m_floorTimer = 7.0f;							//効果時間をリセット
		DeleteGO(m_spriteRender);                       //テクスチャを消す
		DeleteGO(m_fontRender);
		m_spriteRender = nullptr;
		m_fontRender = nullptr;
	}
}

/// <summary>
/// プレイヤーが床から受けた効果を戻す
/// </summary>
void FloorManager::RevertState()
{
	if (!m_isAddStatus) {
		return;
	}
	switch (m_saveState) {
	case Normal:
		m_player->m_moveDir = 1.0f;
		break;
	case ReverseState:
		if (m_spriteRender) {
			DeleteGO(m_spriteRender);
			m_spriteRender = nullptr;
		}
		m_player->m_moveDir *= -1.0f;
		break;
	case SlowState:
		if (m_spriteRender) {
			DeleteGO(m_spriteRender);
			m_spriteRender = nullptr;
		}
		m_player->m_moveDir /= PLAYER_MOVE_SLOW;
		break;
	case BlindState:
		if (m_spriteRender) {
			DeleteGO(m_spriteRender);
			m_spriteRender = nullptr;
		}
		// 環境光を元に戻す
		g_renderingEngine->SetAmbientByIBLTexture(m_game->m_skyCube->GetTextureFilePath(), 1.0f);
		g_renderingEngine->SetSceneMiddleGray(0.18f);
		g_renderingEngine->SetBloomThreshold(1.0f);
		//ポイントライト
		DeletePointLight();
		break;
	}
	m_saveState = Normal;	//保存したものを通常に。
}
