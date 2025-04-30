#include "stdafx.h"
#include "FloorManager.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "Player.h"
#include "Game.h"

namespace {
	const float PLAYER_MOVE_SLOW = 0.5;		//プレイヤーの移動スピードが半減
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
	
	//床の効果を発動していないとき、床を見つける
	if (m_floorTimer >= 7.0f) {
		FindFloor();		
	}

	AddStatus();			//デバフをかける

	////デバフがかかっている場合///
	if (m_saveState != Normal) {
		AddStatusTimer();       //効果時間を減らす
		CalcStatusTime();		//状態を戻す
	}

	////視界制限時、ポイントライトの位置をプレイヤーの上に設定///
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
	//ステージ内のあべこべ床をすべて見つける
	const auto& reverseFloors = FindGOs<ReverseFloor>("ReverseFloor");

	for (auto reverseFloor : reverseFloors) {
		//ステージ内のあべこべ床を踏んだ場合、状態変更
		if (reverseFloor->m_onReverseFloor == true) {
			m_floorState = ReverseState;
		}
	}

	///////////////////////////////////////////////////
	//ステージ内の視界制限床をすべて見つける
	const auto& slowFloors = FindGOs<SlowFloor>("SlowFloor");

	for (auto slowFloor : slowFloors) {
		//ステージ内の鈍足床を踏んだ場合、状態変更
		if (slowFloor->m_onSlowFloor == true) {
			m_floorState = SlowState;
		}
	}

	//////////////////////////////////////////////////
	//ステージ内の視界制限床をすべて見つける
	const auto& blindFloors = FindGOs<BlindFloor>("BlindFloor");

	for (auto blindFloor : blindFloors) {
		//フロア内の視界制限床を踏んだ場合、状態を変更
		if (blindFloor->m_onBlindFloor == true) {
			m_floorState = BlindState;
		}
	}
}


void FloorManager::AddStatus()	/////デバフをかける/////
{
	if (m_floorTimer == 7.0f) {		//もしデバフを受けていない場合
		if (!m_isAddStatus && m_floorState != Normal) {
			switch (m_floorState) {
			case ReverseState:
				if (m_spriteRender) {
					DeleteGO(m_spriteRender);
				}

				//画像の表示
				m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
				m_spriteRender->Init("Assets/sprite/reverse.DDS", 100.0f, 100.0f);
				m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));

				//進行方向を反転
				m_player->m_moveDir *= -1.0f;

				AddStatusTimer();

				break;

			case SlowState:
				if (m_spriteRender) {
					DeleteGO(m_spriteRender);
				}

				m_floorTimer -= g_gameTime->GetFrameDeltaTime();

				//画像の表示
				m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
				m_spriteRender->Init("Assets/sprite/slow.DDS", 100.0f, 100.0f);
				m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));

				//プレイヤーの速度を半減
				m_player->m_moveDir *= PLAYER_MOVE_SLOW;

				AddStatusTimer();

				break;

			case BlindState:
				if (m_spriteRender) {
					DeleteGO(m_spriteRender);
				}

				m_floorTimer -= g_gameTime->GetFrameDeltaTime();

				//画像の表示

				m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
				m_spriteRender->Init("Assets/sprite/blind.DDS", 100.0f, 100.0f);
				m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));

				AddStatusTimer();

				//////////////環境光の設定//////////////////////////

				// テクスチャの明るさを変更
				g_renderingEngine->SetAmbientByIBLTexture(m_game->m_skyCube->GetTextureFilePath(), 0.01f);

				// 明るさの明度率
				g_renderingEngine->SetSceneMiddleGray(0.01f);

				// ブルームの設定
				g_renderingEngine->SetBloomThreshold(10.0f);

				//////////////スポットライト/////////////////////////////
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
	//効果時間の設定
	int effectTimer_minute = 0.0f;
	int effectTimer_sec = m_floorTimer;

	m_fontRender = NewGO<FontRender>(0, "fontrender");

	//文字の設定
	wchar_t reverse_text[256];
	swprintf_s(reverse_text, 256, L"%02d:%02d", effectTimer_minute, effectTimer_sec);
	m_fontRender->SetText(reverse_text);							//表示
	m_fontRender->SetPosition(Vector3(700.0f, 390.0f, 0.0f));		//場所
	m_fontRender->SetScale(1.5f);									//大きさ
	m_fontRender->SetColor({ 1.0f,1.0f,1.0f,1.0f });				//色
	
}


void FloorManager::SetPointLight()
{
	m_pointL = NewGO<PointLight>(0,"pointLight");
	
	m_pointL->Init();
	m_pointL->SetPosition(pointLightPosition);
	m_pointL->SetAffectPowParam(0.7f);				//影響率
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
	m_floorTimer -= g_gameTime->GetFrameDeltaTime();	//効果時間を減らす
	if (m_floorTimer <= 0) {							//０になった場合
		RevertState();									//効果をリセット
		m_floorTimer = 7.0f;							//時間をリセット
		DeleteGO(m_spriteRender);                       //画像を消去
		DeleteGO(m_fontRender);							//文字を消去
		m_spriteRender = nullptr;
		m_fontRender = nullptr;
	}
}

/// <summary>
/// 効果をリセット
/// </summary>
void FloorManager::RevertState()
{
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
		// 環境光
		g_renderingEngine->SetAmbientByIBLTexture(m_game->m_skyCube->GetTextureFilePath(), 1.0f);
		g_renderingEngine->SetSceneMiddleGray(0.18f);
		g_renderingEngine->SetBloomThreshold(1.0f);
		//ポイントライトの削除
		DeletePointLight();
		break;
	}
	m_saveState = Normal;	// 状態をリセット
}
