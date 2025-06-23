#include "stdafx.h"
#include "PuzzleCube.h"
#include"SecondFloor.h"
#include "Player.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include <array>

namespace {
	// 絵合わせブロックの位置。
	Vector3 CUBE1_POSITION = Vector3(1790.0f, 40.0f, -2270.0f);
	Vector3 CUBE2_POSITION = Vector3(-500.0f, 30.0f, -3100.0f);
	Vector3 CUBE3_POSITION = Vector3(-1200.0f, 30.0f,-2580.0f);
	// 絵合わせの土台の位置。
	Vector3 CUBE4_POSITION = Vector3(1790.0f, 10.0f, -2270.0f);
	Vector3 CUBE5_POSITION = Vector3(-500.0f, 0.0f, -3100.0f);
	Vector3 CUBE6_POSITION = Vector3(-1200.0f, 0.0f, -2580.0f);
	// 絵合わせの大きさ。
	Vector3 CUBE_SCALE = Vector3(3.0f, 3.0f, 3.0f);
	// UIの位置。
	//Vector3 CUBE_UI_POSITION = Vector3(800.0f, 200.0f, 0.0f);
	Vector3 CUBE_UI_POSITION = Vector3(400.0f, -10.0f, 0.0f);
	// UIの大きさ。
	//Vector3 CUBE_UI_SCALE = Vector3(1.0f, 1.0f, 0.2f);
	Vector3 CUBE_UI_SCALE = Vector3(0.5f, 0.5f, 0.2f);
	// UIの色。
	Vector4 CUBE_UI_COLOR = Vector4(1.0f, 1.0f, 1.0f, 0.8f);
	// ボタンUIの位置。
	//Vector3 BUTTON_UI_POSITION = Vector3{480.0f, 265.0f, 0.0f};
	// スケールが1.0の時のポジション。
	//Vector3 BUTTON_UI_POSITION = Vector3{ 230.0f, 30.0f, 0.0f };
	Vector3 BUTTON_UI_POSITION = Vector3{ 260.0f, 26.0f, 0.0f };
	// ボタンUIの大きさ。
	//float BUTTON_UI_SCALE = 1.0f;
	float BUTTON_UI_SCALE = 0.8f;
	// ボタンUIの色。
	Vector4 BUTTON_UI_COLOR = Vector4(g_vec4White);
}

PuzzleCube::PuzzleCube()
{
}

PuzzleCube::~PuzzleCube()
{
}

void PuzzleCube::SetUI()
{
	// テキスト
	m_spriteRender.Init("Assets/modelData/stage3/gimmick/PuzzleCube/puzzleCubeUI.dds", 1920.0f, 1080.0f);
	m_spriteRender.SetPosition(Vector3(CUBE_UI_POSITION));
	m_spriteRender.SetScale(Vector3(CUBE_UI_SCALE));
	m_spriteRender.SetMulColor(Vector4(CUBE_UI_COLOR));
	Update();
}

void PuzzleCube::SetText() 
{
	// テキストを表示する。
	m_fontRender.SetText(L"Yボタンで回転させる。");
	m_fontRender.SetPosition(BUTTON_UI_POSITION);
	m_fontRender.SetScale(BUTTON_UI_SCALE);
	m_fontRender.SetColor(BUTTON_UI_COLOR);
	Update();
	// Startのコード汚いから直す。
}

bool PuzzleCube::Start()
{
	// ブロック。
	std::array<ModelRender*, 3> modelRenders = { &m_modelRender, &m_modelRender2, &m_modelRender3 };
	for (auto& render : modelRenders) {
		// ファイルを読み込む。
		render->Init("Assets/modelData/stage3/gimmick/PuzzleCube.tkm");
		// 大きさを変更する。
		render->SetScale(CUBE_SCALE);
		//render->Update();
	}
	// 土台。
	std::array<ModelRender*, 3> modelRenders2 = { &m_modelRender4, &m_modelRender5, &m_modelRender6 };
	for (auto& render2 : modelRenders2) {
		// ファイルを読み込む。
		render2->Init("Assets/modelData/stage3/gimmick/PuzzleCubeFoundation.tkm");
		// 大きさを変更する。
		render2->SetScale(CUBE_SCALE);
	}
	// 効果音。
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/puzzleCube.wav");

	// ブロックの位置。
	m_modelRender.SetPosition(Vector3(CUBE1_POSITION));
	m_modelRender2.SetPosition(Vector3(CUBE2_POSITION));
	m_modelRender3.SetPosition(Vector3(CUBE3_POSITION));
	// Updateをかけることで、生成されたコリジョンもポジションが変更される。
	// Updateをかけることでワールド行列(ポジションとか)を再計算するする。
	m_modelRender.Update();
	m_modelRender2.Update();
	m_modelRender3.Update();
	// 土台の位置。

	m_modelRender4.SetPosition(Vector3(CUBE4_POSITION));
	m_modelRender5.SetPosition(Vector3(CUBE5_POSITION));
	m_modelRender6.SetPosition(Vector3(CUBE6_POSITION));

	m_player = FindGO<Player>("player");

	m_modelRender4.Update();
	m_modelRender5.Update();
	m_modelRender6.Update();

	// 初期状態でコリジョンを生成
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_physicsStaticObject2.CreateFromModel(m_modelRender2.GetModel(), m_modelRender2.GetModel().GetWorldMatrix());
	m_physicsStaticObject3.CreateFromModel(m_modelRender3.GetModel(), m_modelRender3.GetModel().GetWorldMatrix());

	return true;
}

void PuzzleCube::SetRotation()
{
	// モデルに回転を反映（必要に応じて変換）
	m_rotation.SetRotationDegY(m_rotationY);
	m_rotation2.SetRotationDegY(m_rotation2Y);
	m_rotation3.SetRotationDegY(m_rotation3Y);

	SetClear();
}

void PuzzleCube::Rotation()
{
	// 距離計算。
	float distToCube1 = (m_player->m_position - CUBE1_POSITION).Length();
	float distToCube2 = (m_player->m_position - CUBE2_POSITION).Length();
	float distToCube3 = (m_player->m_position - CUBE3_POSITION).Length();

	// 絵合わせギミックのUIを表示。
	if (distToCube1 < 150.0f || distToCube2 < 150.0f || distToCube3 < 150.0f) {
		m_uiFlag = true;
	}
	// 
	else {
		m_uiFlag = false;
	}
	// ブロックの回転（近いキューブのみ）
	if (distToCube1 <= 150.0f && g_pad[0]->IsTrigger(enButtonY)) {
		m_rotationFlag = true;

		m_rotationY += 90.0f;
		if (m_rotationY > 360) {
			m_rotationY = 0;
		}
	}
	if (distToCube2 <= 150.0f && g_pad[0]->IsTrigger(enButtonY)) {
		m_rotationFlag = true;

		m_rotation2Y += 90.0f;
		if (m_rotation2Y > 360) {
			m_rotation2Y = 0;
		}
	}
	if (distToCube3 <= 150.0f && g_pad[0]->IsTrigger(enButtonY)) {
		m_rotationFlag = true;

		m_rotation3Y += 90.0f;
		if (m_rotation3Y > 360) {
			m_rotation3Y = 0;
		}
	}
	// もしギミックの回転処理が行われたら。
	if (m_rotationFlag == true) {
		// 連続して回転させると、音が重なるので、それを防ぐ。
		//効果音を再生。
		SoundSource* se = NewGO<SoundSource>(4);
		se->Init(4);
		//効果音はループさせないのでfalse。
		se->Play(false);
		//音量。
		se->SetVolume(4.0f);
		m_rotationFlag = false;
	}
}

void PuzzleCube::Update()
{
	m_spriteRender.Update();
	m_fontRender.Update();
	// 距離計算、回転処理。
	Rotation();
	// モデルに回転を反映
	SetRotation();
	m_modelRender.SetRotation(m_rotation);
	m_modelRender2.SetRotation(m_rotation2);
	m_modelRender3.SetRotation(m_rotation3);

	if (SetClear()) {
		m_clear = true;
	}

	// 絵合わせギミックの更新。
	m_modelRender.Update();
	m_modelRender2.Update();
	m_modelRender3.Update();
}

bool PuzzleCube::SetClear() const
{
	// クリア判定。
	if (m_rotationY == 90 && m_rotation2Y == 90 && m_rotation3Y == 90) {
		// クリア判定にする。
		return true;
	}

	return false;
}

void PuzzleCube::Render(RenderContext& rc)
{
	// 絵合わせギミックの描画。
	std::array<ModelRender*, 6> modelRenders3 = { &m_modelRender, &m_modelRender2, &m_modelRender3, &m_modelRender4, &m_modelRender5, &m_modelRender6 };
	for (auto& render3 : modelRenders3) {
		// ファイルを読み込む。
		// 大きさを変更する。
		render3->Draw(rc);
	}
	if (m_uiFlag == true) {
		SetUI();
		SetText();
		m_spriteRender.Draw(rc);
		m_fontRender.Draw(rc);
	}
}
