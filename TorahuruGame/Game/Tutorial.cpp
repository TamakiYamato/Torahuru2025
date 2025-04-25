#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "Tutorial.h"

namespace

{
	// 画像の位置。
	//Vector3 TEXT_POSITION = Vector3(-500.0f, 500.0f, 0.0f);
	Vector3 TEXT_POSITION = Vector3(500.0f, 500.0f, 0.0f);
	// 画像の大きさ。
	Vector3 TEXT_SCALE = Vector3(0.5f, 0.5f, 0.5f);
	Vector3 SCALE = Vector3{ 5.0f,5.0f,5.0f };
	Vector4 TEXT_COLOR = Vector4::White;
}

Tutorial::Tutorial()
{

}

Tutorial::~Tutorial()
{

}

bool Tutorial::Start()
{
	// ボックスを読み込む。
	m_modelRender.Init("Assets/Tutorial/TutorialObject.tkm");
	// 画像を読み込む。
	// あべこべ床。
	m_spriteRender.Init("Assets/Tutorial/reverseTutorial1.DDS", 600.0f, 250.0f);
	// 位置。
	//m_spriteRender.SetPosition((m_position));
	//m_spriteRender.SetPosition((TEXT_POSITION));

	// 大きさ。
	m_modelRender.SetScale(Vector3(SCALE));
	//m_fontRender.SetText(L"あべこべ床");
	//m_fontRender.SetPosition((TEXT_POSITION));
	//m_fontRender.SetColor((TEXT_COLOR));
	return true;
}

void Tutorial::HintText()
{
	
}

void Tutorial::Update()
{
	// ポジション。
	m_modelRender.SetPosition(m_position);
	// 更新処理。
	m_modelRender.Update();
	m_spriteRender.Update();

	
}

void Tutorial::Render(RenderContext& rc)
{
	// モデルレンダー
	m_modelRender.Draw(rc);
	// スプライトレンダー。
	m_spriteRender.Draw(rc);
	// フォントレンダー。
	m_fontRender.Draw(rc);
}

