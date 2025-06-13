#include "stdafx.h"
#include "PuzzleCube.h"
#include"ThirdFloor.h"
PuzzleCube::PuzzleCube()
{
}

PuzzleCube::~PuzzleCube()
{
}

bool PuzzleCube::Start()
{
	// 絵合わせギミックの読み込み。
	m_modelRender.Init("Assets/modelData/Stage3/gimmick/PuzzleCube.tkm");
	m_modelRender.Init("Assets/modelData/Stage3/gimmick/PuzzleCubeFoundation.tkm");
	// TODO: tamaki レベルできるようになるまでポジションをここで定義する。
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	// フォントをセット。
	m_fontRender.SetText(L"揃った！！");
	// フォントの色。
	m_fontRender.SetColor(g_vec4Red);

	return true;
}

void PuzzleCube::Update()
{
	m_modelRender.SetPosition(m_position);
	// 絵合わせギミックの更新。
	m_modelRender.Update();
	// フォントの更新。
	m_fontRender.Update();
}

void PuzzleCube::Render(RenderContext& rc)
{
	// 絵合わせギミックの描画。
	m_modelRender.Draw(rc);
	// フォントの描画。
	m_fontRender.Draw(rc);
}
