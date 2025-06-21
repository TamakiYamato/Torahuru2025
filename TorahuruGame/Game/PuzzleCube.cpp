#include "stdafx.h"
#include "PuzzleCube.h"
#include"SecondFloor.h"
#include "Player.h"
#include "GameClear.h"
#include <array>

namespace {
	// 絵合わせブロックの位置。
	Vector3 CUBE1_POSITION = Vector3(1790.0f, 40.0f, -2270.0f);
	Vector3 CUBE2_POSITION = Vector3(-500.0f, 30.0f, -3100.0f);
	Vector3 CUBE3_POSITION = Vector3(-1200.0f, 30.0f,-2440.0f);
	// 絵合わせの土台の位置。
	Vector3 CUBE4_POSITION = Vector3(1790.0f, 10.0f, -2270.0f);
	Vector3 CUBE5_POSITION = Vector3(-500.0f, 0.0f, -3100.0f);
	Vector3 CUBE6_POSITION = Vector3(-1200.0f, 0.0f, -2440.0f);
	// 絵合わせの大きさ。
	Vector3 CUBE_SCALE = Vector3(3.0f, 3.0f, 3.0f);
}

PuzzleCube::PuzzleCube()
{

}

PuzzleCube::~PuzzleCube()
{

}

bool PuzzleCube::Start()
{
	// ブロック。
	std::array<ModelRender*, 3> modelRenders = { &m_modelRender, &m_modelRender2, &m_modelRender3 };
	for (auto& render : modelRenders) {
		// ファイルを読み込む。
		render->Init("Assets/modelData/Stage2/gimmick/PuzzleCube.tkm");
		// 大きさを変更する。
		render->SetScale(CUBE_SCALE);
	}
	// 土台。
	std::array<ModelRender*, 3> modelRenders2 = { &m_modelRender4, &m_modelRender5, &m_modelRender6 };
	for (auto& render2 : modelRenders2) {
		// ファイルを読み込む。
		render2->Init("Assets/modelData/Stage2/gimmick/PuzzleCubeFoundation.tkm");
		// 大きさを変更する。
		render2->SetScale(CUBE_SCALE);
	}

	// ブロックの位置。
	m_modelRender.SetPosition(Vector3(CUBE1_POSITION));
	m_modelRender2.SetPosition(Vector3(CUBE2_POSITION));
	m_modelRender3.SetPosition(Vector3(CUBE3_POSITION));

	// 土台の位置。
	m_modelRender4.SetPosition(Vector3(CUBE4_POSITION));
	m_modelRender5.SetPosition(Vector3(CUBE5_POSITION));
	m_modelRender6.SetPosition(Vector3(CUBE6_POSITION));

	m_player = FindGO<Player>("player");

	m_modelRender4.Update();
	m_modelRender5.Update();
	m_modelRender6.Update();

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

}

void PuzzleCube::Update()
{
	// 距離計算。
	float distToCube1 = ( m_player->m_position - CUBE1_POSITION ).Length();
	float distToCube2 = ( m_player->m_position - CUBE2_POSITION ).Length();
	float distToCube3 = ( m_player->m_position - CUBE3_POSITION ).Length();

	// ブロックの回転（近いキューブのみ）
	if (distToCube1 <= 100.0f && g_pad[0]->IsTrigger(enButtonLeft)) {
		m_rotationY += 90.0f;
		if (m_rotationY > 360) {
			m_rotationY = 0;
		}
	}
	if (distToCube2 <= 100.0f && g_pad[0]->IsTrigger(enButtonUp)) {
		m_rotation2Y += 90.0f;
		if (m_rotation2Y > 360){
			m_rotation2Y = 0;
		}
	}
	if (distToCube3 <= 100.0f && g_pad[0]->IsTrigger(enButtonRight)) {
		m_rotation3Y += 90.0f;
		if (m_rotation3Y > 360) {
			m_rotation3Y = 0;
		}
	}

	// モデルに回転を反映
	SetRotation();
	m_modelRender.SetRotation(m_rotation);
	m_modelRender2.SetRotation(m_rotation2);
	m_modelRender3.SetRotation(m_rotation3);

	if (SetClear()) {
		m_clear = true;
	}

	SetRotation();
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
}
