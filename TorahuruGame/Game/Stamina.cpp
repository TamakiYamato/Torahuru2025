#include "stdafx.h"
#include "Stamina.h"
#include "Player.h"

namespace
{
	// TODO: tamaki ここの部分を定数に変更する。
	// スタミナバーの位置。
	const Vector3 STAMINA_POSITION = Vector3(0.0f, -400.0f, 0.0f);
	const Vector3 STAMINA_POSITION2 = Vector3(-240.0f, -400.0f, 0.0f);
	// スタミナバーの大きさ。
	const Vector3 STAMINA_SCALE = Vector3(1.0f, 1.0f, 1.0f);
	const Vector3 STAMINA_SCALE2 = Vector3(0.96f, 0.85f, 0.85f);
	// ピボット。(右端原点)
	const Vector2 SET_PIVOT = Vector2(0.0f, 0.5f);
	//Vector3 SCALE = Vector3{ 0.425f,0.48f,0.5f };
	const Vector3 SCALE = Vector3{ 0.8f,0.5f,0.5f };

	// ファイルパス
	const std::string staminaFilePath = "Assets/PlayerUI/";
	const std::string staminaExt = ".DDS";

	/*const std::string animationFilePath = "Assets/animData/player/";
	const std::string animationExtention = ".tka";*/
}

Stamina::Stamina()
{
}

Stamina::~Stamina()
{
}

// TODO: tamaki ここの部分の関数を完成させる。
void Stamina::SetFilePath(std::string staminaFileName)
{
	// 共通したファイル名
	std::string FileName = staminaFilePath + staminaFileName + staminaExt;
	//
	/*m_spriteRender(FileName.c_str());*/

	//// 共通化したファイル名。
	//std::string FileName = animationFilePath + animationFileName + animationExtention;
	////std::strinstr();
	//// c_str()メゾットを呼び出すことで const char* に変換される。
	//m_animationClips[animationClip].Load(FileName.c_str());
	//m_animationClips[animationClip].SetLoopFlag(loopFlag);
}

void Stamina::InitFilePath()
{
	// TODO: tamaki ここのファイルパスの部分を共通化するために定数にする。
	// TODO: tamaki Init関数を作り、ここの部分の処理を移す。
	// 画像を読み込む。
	// スタミナバー(枠組み)の画像。
	m_spriteRender.Init("Assets/PlayerUI/sutaminaBar.DDS", 500.0f, 100.0f);
	// スタミナバー(減らす部分)の画像。
	m_spriteRender2.Init("Assets/PlayerUI/sutamina.DDS", 500.0f, 100.0f);
	// スタミナバー(枠組)の位置。
	m_spriteRender.SetPosition(Vector3(STAMINA_POSITION));
	// スタミナバー(減らす部分)の位置。
	m_spriteRender2.SetPosition(Vector3(STAMINA_POSITION2));
	// スタミナバー(枠組み)の大きさ。
	m_spriteRender.SetScale(Vector3(STAMINA_SCALE));
	// スタミナバー(減らす部分)の大きさ。
	m_spriteRender2.SetScale(Vector3(STAMINA_SCALE2));
	// ピボットの位置。
	m_spriteRender2.SetPivot(Vector2(SET_PIVOT));
}

bool Stamina::Start()
{
	
	InitFilePath();

	// playerを探す。→探さないとnullptr判定になる。
	m_player = FindGO<Player>("player");
	
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
}

void Stamina::Render(RenderContext& rc)
{
	// 画像を描画。
	m_spriteRender.Draw(rc);
	m_spriteRender2.Draw(rc);
}