#include "stdafx.h"
#include "FloorManager.h"
#include"ReverseFloor.h"
#include"SlowFloor.h"
#include"BlindFloor.h"
#include"Player.h"

namespace {
	const float PLAYER_MOVE_SLOW = 0.5;		//プレイヤーの速度を変更。
}

FloorManager::FloorManager()
{
}

FloorManager::~FloorManager()
{
	for (auto pointLight : m_pointLightList)
	{
		//ポイントライトを削除する。
		delete pointLight;
	}
}

bool FloorManager::Start()
{
	m_player = FindGO<Player>("player");
	return true;
}

void FloorManager::Update()
{
	FindFloor();	//3種類の床をすべて見つける
	AddStatus();	//状態ごとの効果反映

	////プレイヤーが床の影響を受けている場合////
	if (m_saveState != Normal) {
		CalcStatusTime();
	}
}


void FloorManager::Render(RenderContext& rc)
{
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
	if (m_floorTimer == 10.0f) {
		switch (m_floorState) {
		case ReverseState:
			m_player->m_moveDir *= -1.0f;
			break;

		case SlowState:
			m_player->m_dash *= PLAYER_MOVE_SLOW;
			break;

		case BlindState:

			//////////////ステージを暗くする///////////////////////////

			// 環境光の計算のためのIBLテクスチャをセットする。
			g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);

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


void FloorManager::SetPointLight()
{
	//ライトの初期設定
	Vector3 pointLightPosition = m_player->m_position;
	pointLightPosition.y += 200;
	m_pointLight.SetPosition(pointLightPosition);
	m_pointLight.Update();
	m_setLight = false;

	//明るさの設定
	m_pointLight.Init();
	m_pointLight.SetPosition(m_player->m_position);
	m_pointLight.SetColor(Vector3(5.0f, 5.0f, 5.0f));
	m_pointLight.SetAffectPowParam(0.7f);
	m_pointLight.SetRange(300.0f);
}


void FloorManager::CalcStatusTime()
{
	m_floorTimer -= g_gameTime->GetFrameDeltaTime();	//効果時間のカウントダウン10秒
	if (m_floorTimer <= 0) {							//時間が０になった場合
		RevertState();									//床の効果を消す
		m_saveState = Normal;							//状態を通常に
		m_floorTimer = 10.0f;							//効果時間をリセット
	}
}

/// <summary>
/// プレイヤーが床から受けた効果を戻す
/// </summary>
void FloorManager::RevertState()
{
	switch (m_saveState) {
	case Normal:
		m_player->m_moveDir = 1.0f;
		break;
	case ReverseState:
		m_player->m_moveDir = -1.0f;
		break;
	case SlowState:
		m_player->m_dash /= PLAYER_MOVE_SLOW;
		break;
	case BlindState:
		// 環境光を元に戻す
		g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f);
		g_renderingEngine->SetSceneMiddleGray(0.18f);
		g_renderingEngine->SetBloomThreshold(1.0f);
		break;
	}
	m_saveState = Normal;	//保存したものを通常に。
}
