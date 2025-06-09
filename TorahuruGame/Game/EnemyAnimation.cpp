#include "stdafx.h"
#include "EnemyAnimation.h"
using namespace std;

namespace {
	// 
	const string ANIMATION_FILEPATH = "Assets/animData/enemy/";
	const string ANIMATION_EXTENTION = ".tka";

}

bool EnemyAnimation::Start()
{
	// 待機
	SetAnimation(enAnimationClip_Idle, "enemyIdle", true);
	// 歩き
	SetAnimation(enAnimationClip_Walk, "enemyWalking", true);
	// 走る
	SetAnimation(enAnimationClip_Run, "enemyRun", true);

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
	string FileName = ANIMATION_FILEPATH + animationFileName + ANIMATION_EXTENTION;
	//
	// 
	m_enemyAnim[animationClip].Load(FileName.c_str());
	m_enemyAnim[animationClip].SetLoopFlag(loopFlag);
}