#include "stdafx.h"
#include "PuzzleCube.h"

PuzzleCube::PuzzleCube()
{
}

PuzzleCube::~PuzzleCube()
{
}

bool PuzzleCube::Start()
{
	// 絵合わせギミックの読み込み。
	m_modelRender.Init("Assets/modelData/Stage1.tkm");
	// TODO: tamaki レベルできるようになるまでポジションをここで定義する。
	// フォントをセット。
	m_fontRender.SetText(L"揃った！！");
	// フォントの色。
	m_fontRender.SetColor(g_vec4Red);

	return true;
}
