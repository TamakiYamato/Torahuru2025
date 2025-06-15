#include "stdafx.h"
#include "PuzzleCube.h"
#include"ThirdFloor.h"
#include "Player.h"
#include "GameClear.h"

namespace {
	Vector3 CUBE1_POSITION = Vector3(1790.0f, 40.0f, -2270.0f);
	Vector3 CUBE2_POSITION = Vector3(-500.0f, 30.0f, -3100.0f);
	Vector3 CUBE3_POSITION = Vector3(-1200.0f, 30.0f, -2470.0f);
}

PuzzleCube::PuzzleCube()
{
}

PuzzleCube::~PuzzleCube()
{

}

bool PuzzleCube::Start()
{
	// 絵合わせギミックの読み込み。
	// ブロック。
	m_modelRender.Init("Assets/modelData/Stage3/gimmick/PuzzleCube.tkm");
	m_modelRender2.Init("Assets/modelData/Stage3/gimmick/PuzzleCube.tkm");
	m_modelRender3.Init("Assets/modelData/Stage3/gimmick/PuzzleCube.tkm");
	// 土台。
	m_modelRender4.Init("Assets/modelData/Stage3/gimmick/PuzzleCubeFoundation.tkm");
	m_modelRender5.Init("Assets/modelData/Stage3/gimmick/PuzzleCubeFoundation.tkm");
	m_modelRender6.Init("Assets/modelData/Stage3/gimmick/PuzzleCubeFoundation.tkm");


	// TODO: tamaki レベルできるようになるまでポジションをここで定義する。
	// ブロックの位置。
	m_modelRender.SetPosition(Vector3(CUBE1_POSITION));
	m_modelRender2.SetPosition(Vector3(CUBE2_POSITION));
	m_modelRender3.SetPosition(Vector3(CUBE3_POSITION));
	// 大きさ。
	m_modelRender.SetScale({ 3.0f,3.0f,3.0f });
	m_modelRender2.SetScale({ 3.0f,3.0f,3.0f });
	m_modelRender3.SetScale({ 3.0f,3.0f,3.0f });

	// 土台の位置。
	m_modelRender4.SetPosition(Vector3(1790.0f, 10.0f, -2270.0f));
	m_modelRender5.SetPosition(Vector3(-500.0f, 0.0f, -3100.0f));
	m_modelRender6.SetPosition(Vector3(-1200.0f, 0.0f, -2470.0f));
	// 大きさ。
	m_modelRender4.SetScale({ 3.0f,3.0f,3.0f });
	m_modelRender5.SetScale({ 3.0f,3.0f,3.0f });
	m_modelRender6.SetScale({ 3.0f,3.0f,3.0f });

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
	m_modelRender.Draw(rc);
	m_modelRender2.Draw(rc);
	m_modelRender3.Draw(rc);
	m_modelRender4.Draw(rc);
	m_modelRender5.Draw(rc);
	m_modelRender6.Draw(rc);
}
