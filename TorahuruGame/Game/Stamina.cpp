#include "stdafx.h"
#include "Stamina.h"
#include "Player.h"

namespace
{
	// スタミナバーの位置。
	Vector3 STAMINA_POSITION = Vector3(80.0f, -400.0f, 0.0f);
	Vector3 STAMINA_POSITION2 = Vector3(-160.0f, -400.0f, 0.0f);
	// ダッシュボタンのマークの位置。
	Vector3 STAMINABUTTON_POSITION = Vector3(-240.0f, -405.0f, 0.0f);

	// スタミナバーの大きさ。
	Vector3 STAMINA_SCALE = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 STAMINA_SCALE2 = Vector3(0.96f, 0.85f, 0.85f);
	// ダッシュボタンのマークの位置。
	Vector3 STAMINABUTTON_SCALE = Vector3(0.8f, 3.0f, 1.0f);

	// ピボット。(右端原点)
	Vector2 SET_PIVOT = Vector2(0.0f, 0.5f);
	//
	//Vector3 SCALE = Vector3{ 0.425f,0.48f,0.5f };
	Vector3 SCALE = Vector3{ 0.8f,0.5f,0.5f };
}

Stamina::Stamina()
{

}

Stamina::~Stamina()
{

}

bool Stamina::Start()
{
	// 画像を読み込む。
	// スタミナバー(枠組み)の画像。
	m_spriteRender.Init("Assets/PlayerUI/staminaBar.DDS", 500.0f, 100.0f);
	// スタミナバー(減らす部分)の画像。
	m_spriteRender2.Init("Assets/PlayerUI/stamina.DDS", 500.0f, 100.0f);
	// ダッシュボタンのマーク。
	m_spriteRender3.Init("Assets/PlayerUI/staminaButton.DDS", 500.0f, 100.0f);

	// playerを探す。→探さないとnullptr判定になる。
	m_player = FindGO<Player>("player");

	// スタミナバー(枠組)の位置。
	m_spriteRender.SetPosition(Vector3(STAMINA_POSITION));
	// スタミナバー(減らす部分)の位置。
	m_spriteRender2.SetPosition(Vector3(STAMINA_POSITION2));
	// ダッシュボタンのマークの位置。
	m_spriteRender3.SetPosition(Vector3(STAMINABUTTON_POSITION));

	// スタミナバー(枠組み)の大きさ。
	m_spriteRender.SetScale(Vector3(STAMINA_SCALE));
	// スタミナバー(減らす部分)の大きさ。
	m_spriteRender2.SetScale(Vector3(STAMINA_SCALE2));
	// ダッシュボタンのマークの大きさ。
	m_spriteRender3.SetScale(Vector3(STAMINABUTTON_SCALE));

	// ピボットの位置。
	m_spriteRender2.SetPivot(Vector2(SET_PIVOT));

	return true;
}

void Stamina::StaminaCalc()
{
		// プレイヤーの最大スタミナの値。
		float MaxVitality = m_player->m_max_stamina;
		// プレイヤーの現在のスタミナの値。
		float newVitality = m_player->m_stamina;
		// 割合を計算→scaleのX値に掛け算→バーが縮小する。
		float wari = (float)newVitality / (float)MaxVitality;
		Vector3 scal = { STAMINA_SCALE2 };
		// 割合の計算結果を代入。
		// 割合の応じて横幅だけ縮める。
		scal.x *= wari;
		m_spriteRender2.SetScale(scal);
}

void Stamina::Update()
{
	// スタミナ計算と更新。
	StaminaCalc();
	// スプライトを更新。
	m_spriteRender.Update();
	m_spriteRender2.Update();
	m_spriteRender3.Update();
}

void Stamina::Render(RenderContext& rc)
{
	// 画像を描画。
	m_spriteRender.Draw(rc);
	m_spriteRender2.Draw(rc);
	m_spriteRender3.Draw(rc);
}