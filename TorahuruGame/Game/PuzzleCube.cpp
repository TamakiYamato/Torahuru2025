#include "stdafx.h"
#include "PuzzleCube.h"
#include"SecondFloor.h"
#include "Player.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include <array>

namespace {
	///// 絵合わせブロックの位置。/////
	Vector3 CUBE1_POSITION = Vector3(1790.0f, 40.0f, -2270.0f);
	Vector3 CUBE2_POSITION = Vector3(-500.0f, 30.0f, -3100.0f);
	Vector3 CUBE3_POSITION = Vector3(-1200.0f, 30.0f,-2580.0f);

	///// 絵合わせの土台の位置。/////
	Vector3 PEDESTAL1_POSITION = Vector3(1790.0f, 10.0f, -2270.0f);
	Vector3 PEDESTAL2_POSITION = Vector3(-500.0f, 0.0f, -3100.0f);
	Vector3 PEDESTAL3_POSITION = Vector3(-1200.0f, 0.0f, -2580.0f);

	///// 絵合わせの大きさ。/////
	Vector3 CUBE_SCALE = Vector3(3.0f, 3.0f, 3.0f);

	///// 絵合わせのコリジョンの大きさ。/////
	Vector3 CUBE_COLLISION = Vector3(100.0f,100.0f,100.0f);

	///// UIの位置。/////
	Vector3 CUBE_UI_POSITION = Vector3(400.0f, -10.0f, 0.0f);

	///// UIの大きさ。/////
	Vector3 CUBE_UI_SCALE = Vector3(0.5f, 0.5f, 0.2f);

	////// UIの色。/////
	Vector4 CUBE_UI_COLOR = Vector4(1.0f, 1.0f, 1.0f, 0.8f);

	////// ボタンUIの位置。/////
	Vector3 BUTTON_UI_POSITION = Vector3{ 260.0f, 26.0f, 0.0f };

	///// ボタンUIの大きさ。/////
	float BUTTON_UI_SCALE = 0.8f;

	///// ボタンUIの色。/////
	Vector4 BUTTON_UI_COLOR = Vector4(g_vec4White);
}

// UI。
void PuzzleCube::SetUI()
{
	// テキスト
	m_spriteRender.Init("Assets/modelData/stage3/gimmick/PuzzleCube/puzzleCubeUI.dds", 1920.0f, 1080.0f);
	m_spriteRender.SetPosition(Vector3(CUBE_UI_POSITION));
	m_spriteRender.SetScale(Vector3(CUBE_UI_SCALE));
	m_spriteRender.SetMulColor(Vector4(CUBE_UI_COLOR));
	m_spriteRender.Update();
	SetText();
}
// 回転時のテキスト。
void PuzzleCube::SetText() 
{
	// テキストを表示する。
	m_fontRender.SetText(L"Yボタンで回転させる。");
	m_fontRender.SetPosition(BUTTON_UI_POSITION);
	m_fontRender.SetScale(BUTTON_UI_SCALE);
	m_fontRender.SetColor(BUTTON_UI_COLOR);
}

// 絵合わせギミックのポジション。
void PuzzleCube::SetPuzzleCubePosition()
{
	////// 配列用に再定義。//////
	// 絵合わせギミックのブロックのモデルレンダラーの配列。
	ModelRender* m_cubeRenders[] = { &m_cubeRender, &m_cubeRender2, &m_cubeRender3 };
	// 絵合わせギミックのブロックの配列。
	const Vector3 m_cubePositions[] = { CUBE1_POSITION, CUBE2_POSITION, CUBE3_POSITION };

	// ブロックの位置。
	for (int i = 0; i < _countof(m_cubeRenders); i++) {
		m_cubeRenders[i]->SetPosition(Vector3(m_cubePositions[i]));
	}

	// 絵合わせギミックの土台のモデルレンダラーの配列。
	ModelRender* m_pedestalRenders[] = { &m_pedestalRender, &m_pedestalRender2, &m_pedestalRender3 };
	// 絵合わせギミックの土台の配列。
	const Vector3 m_pedestalPositions[] = { PEDESTAL1_POSITION, PEDESTAL2_POSITION, PEDESTAL3_POSITION };

	// 土台の位置。
	for (int i = 0; i < _countof(m_pedestalRenders); i++) {
		m_pedestalRenders[i]->SetPosition(Vector3(m_pedestalPositions[i]));
	}
}

bool PuzzleCube::Start()
{
	// 絵合わせのポジション。
	SetPuzzleCubePosition();
	
	//////モデルレンダーの共通化。//////
	std::array<ModelRender*, 3> cubeRenders = { &m_cubeRender, &m_cubeRender2, &m_cubeRender3 };
	for (auto& render : cubeRenders) {
		// ファイルを読み込む。
		render->Init("Assets/modelData/stage2/gimmick/PuzzleCube.tkm");
		// 大きさを変更する。
		render->SetScale(CUBE_SCALE);
		render->Update();
	}
	// 土台。
	std::array<ModelRender*, 3> pedestalRenders = { &m_pedestalRender, &m_pedestalRender2, &m_pedestalRender3 };
	for (auto& render2 : pedestalRenders) {
		// ファイルを読み込む。
		render2->Init("Assets/modelData/stage2/gimmick/PuzzleCubePedestal.tkm");
		// 大きさを変更する。
		render2->SetScale(CUBE_SCALE);
		render2->Update();
	}
	// 効果音。
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/puzzleCube.wav");

	m_player = FindGO<Player>("player");

	// 初期状態でコリジョンを生成。
	m_physicsStaticObject.CreateFromModel(m_cubeRender.GetModel(), m_cubeRender.GetModel().GetWorldMatrix());
	m_physicsStaticObject2.CreateFromModel(m_cubeRender2.GetModel(), m_cubeRender2.GetModel().GetWorldMatrix());
	m_physicsStaticObject3.CreateFromModel(m_cubeRender3.GetModel(), m_cubeRender3.GetModel().GetWorldMatrix());

	return true;
}

void PuzzleCube::CubeSetRotation()
{
	// モデルに回転を反映（必要に応じて変換）
	m_rotation.SetRotationDegY(m_rotationY);
	m_rotation2.SetRotationDegY(m_rotation2Y);
	m_rotation3.SetRotationDegY(m_rotation3Y);

	ToggleClear();
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
	else {
		m_uiFlag = false;
	}
	// ブロックの回転（近いキューブのみ）
	if (distToCube1 <= 150.0f && g_pad[0]->IsTrigger(enButtonY)) {
		m_rotationFlag = true;

		m_rotationY += 90.0f;
		if (m_rotationY >= 360) {
			m_rotationY = 0.0f;
		}
	}
	if (distToCube2 <= 150.0f && g_pad[0]->IsTrigger(enButtonY)) {
		m_rotationFlag = true;

		m_rotation2Y += 90.0f;
		if (m_rotation2Y >= 360) {
			m_rotation2Y = 0.0f;
		}
	}
	if (distToCube3 <= 150.0f && g_pad[0]->IsTrigger(enButtonY)) {
		m_rotationFlag = true;

		m_rotation3Y += 90.0f;
		if (m_rotation3Y >= 360) {
			m_rotation3Y = 0.0f;
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
	// チュートリアルUI。
	m_spriteRender.Update();
	m_fontRender.Update();
	// 距離計算、回転処理。
	Rotation();
	// モデルに回転を反映
	CubeSetRotation();
	m_cubeRender.SetRotation(m_rotation);
	m_cubeRender2.SetRotation(m_rotation2);
	m_cubeRender3.SetRotation(m_rotation3);

	// 絵合わせギミックの更新。
	m_cubeRender.Update();
	m_cubeRender2.Update();
	m_cubeRender3.Update();

	ToggleClear();

	if (m_uiFlag) {
		SetUI();
	}
}

void PuzzleCube::ToggleClear()
{
	// クリア判定。
	if (m_rotationY == 90 && m_rotation2Y == 90 && m_rotation3Y == 90) {
		// クリア判定にする。
		m_clear = true;
	}
}

void PuzzleCube::Render(RenderContext& rc)
{
	// 絵合わせギミックの描画。
	std::array<ModelRender*, 6> modelRenders3 = { &m_cubeRender, &m_cubeRender2, &m_cubeRender3, &m_pedestalRender, &m_pedestalRender2, &m_pedestalRender3 };
	for (auto& render3 : modelRenders3) {
		// ファイルを読み込む。
		// 大きさを変更する。
		render3->Draw(rc);
	}
	if (m_uiFlag) {
		m_spriteRender.Draw(rc);
		m_fontRender.Draw(rc);
	}
}
