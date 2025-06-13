#include "stdafx.h"
#include "Loading.h"
#include"FirstFloor.h"
#include"SecondFloor.h"

namespace
{
	// 大きさ。
	const Vector3	SCALE = Vector3(2.16f, 2.16f, 1.0f);
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
	//// 大きさ。
	//m_spriteRender.SetScale(SCALE);
	//// 位置。
	//m_spriteRender.SetPosition(POSITIOIN);
	// 更新。
	m_spriteRender.Update();
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
		if (m_currentAlpha <= 0.0f) {
			// α値が0.0の時→透明状態→ゲームプレイ。

			m_currentAlpha = 0.0f;
			// ステートを変更。
			m_state = enState_Idle;

			m_waitingTime = 3.0f;
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
			m_waitingTime = 3.0f;
		}
		break;
		// ステートを変更し処理を終了させる。
	case enState_Idle:

		m_isstate = false;

		m_waitingTime -= g_gameTime->GetFrameDeltaTime();

		break;
	}
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