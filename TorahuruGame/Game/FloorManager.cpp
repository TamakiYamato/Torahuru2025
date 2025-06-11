#include "stdafx.h"
#include "FloorManager.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "Player.h"
#include "Enemy.h"
#include "TutorialUI.h"
#include "Game.h"

namespace {
	const float PLAYER_MOVE_SLOW = 0.5;		//プレイヤーの移動スピードが半減
	const float ENEMY_MOVE_SLOW = 0.7;		//エネミーの移動スピードを3割減
}

bool FloorManager::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");	
	m_enemy = FindGO<Enemy>("enemy");
	m_tutorialUI = FindGO<TutorialUI>("tutorialUI");
	

	return true;
}

void FloorManager::Update()
{
	//床の効果を発動していないとき、床を見つける
	if (m_playerFloorTimer >= 7.0f or m_enemyFloorTimer >= 5.0f) {
		FindFloor();		
	}

	AddStatus();			//デバフをかける

	////デバフがかかっている場合///
	if (m_playerSaveState != Normal) {
		AddStatusTimer();       //画像と効果時間の表示
		PlayerCalcStatusTime();		//効果時間を減らす
	}

	////視界制限時、ポイントライトの位置をプレイヤーの上に設定///
	if (m_playerSaveState == BlindState) {
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
		if (reverseFloor->m_onPlayerReverseFloor == true && m_playerSaveState == Normal)
		{
			//プレイヤーの状態異常ステートの変更
			m_playerFloorState = ReverseState;

			//UIがこの床の説明の時、ステートを切り替える
			if (m_tutorialUI->m_textState == m_tutorialUI->reverse) {
				m_tutorialUI->onGimmicPassed = true;
			}
		}

		if (reverseFloor->m_onEnemyReverseFloor == true && m_enemySaveState == Normal) {
			m_enemyFloorState = ReverseState;
		}
	}

	///////////////////////////////////////////////////
	//ステージ内の視界制限床をすべて見つける
	const auto& slowFloors = FindGOs<SlowFloor>("SlowFloor");

	for (auto slowFloor : slowFloors) {
		//ステージ内の鈍足床を踏んだ場合、状態変更
		if (slowFloor->m_onPlayerSlowFloor == true && m_playerSaveState == Normal)
		{
			//プレイヤーの状態異常ステートの変更
			m_playerFloorState = SlowState;

			//UIがこの床の説明の時、ステートを切り替える
			if (m_tutorialUI->m_textState = m_tutorialUI->slow) {
				m_tutorialUI->onGimmicPassed = true;
			}
		}
		if (slowFloor->m_onEnemySlowFloor == true && m_enemySaveState == Normal) {
			m_enemyFloorState = SlowState;
		}
	}

	//////////////////////////////////////////////////
	//ステージ内の視界制限床をすべて見つける
	const auto& blindFloors = FindGOs<BlindFloor>("BlindFloor");

	for (auto blindFloor : blindFloors) {
		//フロア内の視界制限床を踏んだ場合、状態を変更
		if (blindFloor->m_onPlayerBlindFloor == true && m_playerSaveState == Normal) 
		{			
			//プレイヤーの状態異常ステートの変更
			m_playerFloorState = BlindState;

			//UIがこの床の説明の時、ステートを切り替える
			if (m_tutorialUI->m_textState = m_tutorialUI->blind) {
				m_tutorialUI->onGimmicPassed = true;
			}
		}
		if (blindFloor->m_onEnemyBlindFloor == true && m_enemySaveState == Normal) {
			m_enemyFloorState = BlindState;
		}
	}
}


void FloorManager::AddStatus()	/////デバフをかける/////
{
	///////////////プレイヤー///////////////
	if (m_playerFloorTimer == 7.0f) {		//もしデバフを受けていない場合
		if (!m_isPlayerAddStatus && m_playerFloorState != Normal) {
			if (m_player->m_isHitFireCollision != true) {
				switch (m_playerFloorState) {

				case ReverseState:
					//前の画像の消去
					if (m_spriteRender) {
						DeleteGO(m_spriteRender);
					}


					//画像の表示
					m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
					m_spriteRender->Init("Assets/sprite/reverse.DDS", 100.0f, 100.0f);
					m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));
					m_spriteRender->Update();

					//進行方向を反転
					m_player->m_moveDir *= -1.0f;

					AddStatusTimer();

					m_floorState = ReverseState;	//床の状態を変更

					break;

				case SlowState:
					//前の画像の消去
					if (m_spriteRender) {
						DeleteGO(m_spriteRender);
					}
					//画像の表示
					m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
					m_spriteRender->Init("Assets/sprite/slow.DDS", 100.0f, 100.0f);
					m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));

					//プレイヤーの速度を半減
					m_player->m_moveDir *= PLAYER_MOVE_SLOW;

					AddStatusTimer();

					m_floorState = SlowState;	//床の状態を変更

					break;

				case BlindState:
					//前の画像の消去
					if (m_spriteRender) {
						DeleteGO(m_spriteRender);
					}

					//画像の表示
					m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
					m_spriteRender->Init("Assets/sprite/blind.DDS", 100.0f, 100.0f);
					m_spriteRender->Update();
					m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));

					AddStatusTimer();

					m_floorState = BlindState;	//床の状態を変更

					//////////////環境光の設定//////////////////////////

					// テクスチャの明るさを変更
					g_renderingEngine->SetAmbient(Vector3(0.01f, 0.01f, 0.01f));

					g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
					g_renderingEngine->SetDirectionLight(1, g_vec3Zero, g_vec3Zero);
					LightCount = 1;
					// Gameクラスでやっているカメラライトをオフにする

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
				m_player->m_requestChangeModel = true;	//プレイヤーが床を踏んでいる状態にする
				m_player->UpdateModelByState();
				m_playerSaveState = m_playerFloorState;
				m_playerFloorState = Normal;
			}
		}
	}

	//////////////エネミー////////////////////////
	if (m_enemyFloorTimer == 5.0f) {
		if (!m_isEnemyAddStatus && m_enemyFloorState != Normal) {
			switch (m_enemyFloorState) {
			case ReverseState:
				//効果
				m_enemy->m_moveDir *= -1.0f;	//進行方向をplayerの反対側に
				break;
			case SlowState:
				//効果
				m_enemy->m_moveDir *= ENEMY_MOVE_SLOW;	//移動速度3割減
				break;
			case BlindState:
				//効果
				m_enemy->Stand();	//移動速度を0に
				m_enemy->m_enemyState = m_enemy->enEnemyState_Idle;
				break;
			default:
				break;
			}
			m_enemySaveState = m_enemyFloorState;
			m_enemyFloorState = Normal;
		}
	}
}

/// <summary>
/// 効果時間と画像の表示
/// </summary>
void FloorManager::AddStatusTimer()
{
	//効果時間の設定
	int effectTimer_minute = 0.0f;
	int effectTimer_sec = m_playerFloorTimer;

	m_fontRender = NewGO<FontRender>(0, "fontrender");

	//文字の設定
	wchar_t reverse_text[256];
	swprintf_s(reverse_text, 256, L"%02d:%02d", effectTimer_minute, effectTimer_sec);
	m_fontRender->SetText(reverse_text);							//表示
	m_fontRender->SetPosition(Vector3(700.0f, 390.0f, 0.0f));		//場所
	m_fontRender->SetScale(1.5f);									//大きさ
	m_fontRender->SetColor({ 1.0f,1.0f,1.0f,1.0f });				//色
	
}

/// <summary>
/// ポイントライトのセット
/// </summary>
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

/// <summary>
/// ポイントライトの削除
/// </summary>
void FloorManager::DeletePointLight()
{
	DeleteGO(m_pointL);
}

/// <summary>
/// 効果時間の減少
/// </summary>
void FloorManager::PlayerCalcStatusTime()
{
	if (m_playerSaveState != Normal) {
		m_playerFloorTimer -= g_gameTime->GetFrameDeltaTime();	//効果時間を減らす
		if (m_playerFloorTimer <= 0) {							//０になった場合
			PlayerRevertState();										//効果をリセット
			m_playerFloorTimer = 7.0f;							//時間をリセット
			DeleteGO(m_spriteRender);							//画像を消去
			DeleteGO(m_fontRender);								//文字を消去
			m_spriteRender = nullptr;
			m_fontRender = nullptr;
			m_player->m_requestChangeModel = true;				//プレイヤーが床を踏んでいないけどモデルを戻すため
			m_floorState = Normal;								//床の状態を戻す
		}
	}
	
}

void FloorManager::EnemyCalcStatusTime()
{
	if (m_enemySaveState != Normal) {
		m_enemyFloorTimer -= g_gameTime->GetFrameDeltaTime();	//効果時間の減少
		if (m_enemyFloorTimer <= 0) {							//０になった場合
			PlayerRevertState();										//効果をリセット
			m_enemyFloorTimer = 5.0f;							//時間をリセット
		}
	}
}

/// <summary>
/// 効果をリセット
/// </summary>
void FloorManager::PlayerRevertState()
{
	if (m_playerSaveState != Normal) {	//プレイヤーの効果を戻す
		switch (m_playerSaveState) {
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
			g_renderingEngine->SetAmbient(Vector3(0.5f, 0.5f, 0.5f));
			g_renderingEngine->SetSceneMiddleGray(0.18f);
			g_renderingEngine->SetBloomThreshold(1.0f);
			//ポイントライトの削除
			DeletePointLight();
			break;
		}
		m_playerSaveState = Normal;	// 状態をリセット
	}
}

void FloorManager::EnemyRevertState()
{
	if (m_enemySaveState != Normal) {
		switch (m_enemySaveState) {
		case ReverseState:
			m_enemy->m_moveDir *= -1.0f;
			break;
		case SlowState:
			m_enemy->m_moveDir /= ENEMY_MOVE_SLOW;
			break;
		case BlindState:
			//enemy.hにて床の効果を受けていない場合、状態が自動で変更するため変更点なし
			break;
		}
		m_enemySaveState = Normal;
	}
}
