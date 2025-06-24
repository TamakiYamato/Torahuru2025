#include "stdafx.h"
#include "Loading.h"
#include"FirstFloor.h"
#include"SecondFloor.h"
#include "GameManager.h"
namespace
{
	// 大きさ。
	const Vector3	SCALE = Vector3(1.2f, 1.0f, 1.0f);
	// 位置。
	const Vector3	POSITIOIN = Vector3(-140.0f, 10.0, 0.0f);
}

Loading::Loading()
{
}

Loading::~Loading()
{
}

bool Loading::Start()
{
	// 画像を読み込む。
	m_spriteRender.Init("Assets/modelData/Title/Loading.DDS", 1920, 1080.);
	// 大きさ。
	m_spriteRender.SetScale(SCALE);
	// 位置。
	m_spriteRender.SetPosition(POSITIOIN);
	// 更新。
	m_spriteRender.Update();

	StartLoadOut();
	return true;
}

void Loading::Update()
{
	// ステート処理。
	switch (m_state) {
		// ゲームスタート時。
	case enState_LoadIn:
		// α値を徐々に減らす。→徐々に明るくする。
		// GetFrameDeltaTimeを使用する事で、一定のスピードで処理が可能。
		m_currentAlpha -= 1.0f * g_gameTime->GetFrameDeltaTime();

		if (m_currentAlpha <= 0.0f) { // α値が0.0の時→透明状態→ゲームプレイ。

			m_currentAlpha = 0.0f;
			m_state = enState_Idle; // ステートを変更。
			m_waitingTime = 3.0f;
			
			m_gameManager->DeleteLoading(); // Loadingオブジェクトを削除

		}
		break;
		// シーン切り替え時。 暗転後にシーン変更。
	case enState_LoadOut:
		// α値を徐々に増やす。→徐々に暗くする。
		m_currentAlpha += 1.0f * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha >= 1.0f) {
			// α値が1.0の時→真っ暗→シーン切り替え。
			m_currentAlpha = 1.0f;
			// ステートを変更。
			m_state = enState_Idle;

			m_isstate = true;
			// シーンを切り替える。
			TransitionToNextScene();
			// Timeを3秒にする
			m_waitingTime = 3.0f;
		}
		break;
		// ステートを変更し処理を終了させる。
	case enState_Idle:

		m_isstate = false;

		m_waitingTime -= g_gameTime->GetFrameDeltaTime();

		break;
	}

	m_spriteRender.Update();
}

void Loading::Render(RenderContext& rc)
{
	// α値が0より大きいなら。
	if (m_currentAlpha > 0.0f) {
		// 現在のm_currentAlphaをスプライトの乗算カラーのαに設定。
		m_spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
		m_spriteRender.Draw(rc);
	}
}

void Loading::TransitionToNextScene()
{
	if (m_gameManager == nullptr) {
		m_gameManager = FindGO<GameManager>("gameManager");
	}

	switch (m_gameManager->GetNextScene()) { // シーンを切り替える。
	case enGameScene_Game:
		m_gameManager->CreateFirstFloor();	//フロア1を生成
		m_gameManager->CreateGame(); // Gameオブジェクトを作成
		break;

	case enGameScene_Stage2:
		m_gameManager->CreateSecondFloor(); // Gameオブジェクトを作成
		m_gameManager->DeleteFirstFloor(); //フロア1の削除
		break;
	default:
		break;
	}	
	// 画面の明るさを徐々に上げる。
	StartLoading();
}


