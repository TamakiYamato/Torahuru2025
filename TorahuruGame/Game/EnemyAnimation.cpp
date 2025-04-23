#include "stdafx.h"
#include "EnemyAnimation.h"
using namespace std;

namespace {
	// ファイルパスは文字列なので string を使用する。
	const string ANIMATION_FAILPATH = "Assets/animData//";
	const string ANIMATION_EXTENTION = ".tka";

}

EnemyAnimation::EnemyAnimation()
{
}

EnemyAnimation::~EnemyAnimation()
{
}

bool EnemyAnimation::Start()
{
	// 待機アニメーション。
	SetAnimation(enAnimationClip_Idle, "playerIdle", true);
	// 歩きアニメーション。
	SetAnimation(enAnimationClip_Walk, "playerWalking", true);
	// 走るアニメーション。
	SetAnimation(enAnimationClip_Run, "playerRun", true);

	return true;
}

void EnemyAnimation::Update()
{
	m_modelRender.Update();

}

void EnemyAnimation::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

}

// constでファイルを読み取る。
void EnemyAnimation::SetAnimation(const EnAnimationClip animationClip, const string animationFileName, const bool loopFlag)
{
	// 共通化したファイル名。
	string FileName = ANIMATION_FAILPATH + animationFileName + ANIMATION_EXTENTION;
	//std::strinstr();
	// c_str()メゾットを呼び出すことで const char* に変換される。
	m_enemyAnim[animationClip].Load(FileName.c_str());
	m_enemyAnim[animationClip].SetLoopFlag(loopFlag);
}