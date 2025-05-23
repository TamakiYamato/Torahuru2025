#include "stdafx.h"
#include "EnemyAnimation.h"
using namespace std;

namespace {
	// 
	const string ANIMATION_FAILPATH = "Assets/animData//";
	const string ANIMATION_EXTENTION = ".tka";

}

bool EnemyAnimation::Start()
{
	// 待機
	SetAnimation(enAnimationClip_Idle, "playerIdle", true);
	// 歩き
	SetAnimation(enAnimationClip_Walk, "playerWalking", true);
	// 走る
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

// 
void EnemyAnimation::SetAnimation(const EnAnimationClip animationClip, const string animationFileName, const bool loopFlag)
{
	// 
	string FileName = ANIMATION_FAILPATH + animationFileName + ANIMATION_EXTENTION;
	//
	// 
	m_enemyAnim[animationClip].Load(FileName.c_str());
	m_enemyAnim[animationClip].SetLoopFlag(loopFlag);
}