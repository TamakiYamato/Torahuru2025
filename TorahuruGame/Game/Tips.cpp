#include "stdafx.h"
#include "Tips.h"

namespace {
	Vector3 FONT_POSITION = Vector3{ 0.0f,0.0f,0.0f };
}

Tips::Tips()
{
}

Tips::~Tips()
{
}

bool Tips::Start()
{
	// 2重配列。
	// 配列１
	tipsList = {
		//配列２
		// このTipsの分の配列が tipsListの配列に入っている。
		// ポインタのbegin→Tipsの T
		// ポインタのend→ 一番最後の文字(この場合は1)。

		L"Tips : テスト1", // 0番目の配列
		L"Tips : テスト2", // 1番目の配列
		L"Tips : テスト3", // 2番目の配列
		L"Tips : テスト4", // 3番目の配列
		L"Tips : テスト5", // 4番目の配列
	};
	
	//ここにtipsListの配列のポインタが帰ってくる。
	std::wstring wstr(tipsList[m_currentTipsIndex].begin(), tipsList[m_currentTipsIndex].end());
	// 配列のポインタをセット。
	m_fontRender.SetText(wstr.c_str());

	return true;
}

void Tips::Update()
{
	SetTime();
}

void Tips::SetTime()
{
	//Tipsの表示時間をリセット。
	m_tipTimer = 0.0f;
	//Tipsのインデックスを更新。
	// = (m_currentTipsIndex + 1) % tipsList.size();
	m_currentTipsIndex++;
	//表示するTipsを更新。
	std::wstring wstr(tipsList[m_currentTipsIndex].begin(), tipsList[m_currentTipsIndex].end());
	m_fontRender.SetText(wstr.c_str());
}

void Tips::Render(RenderContext&rc)
{

}