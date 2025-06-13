#include "stdafx.h"
#include "EnemyAnimation.h"
#include"SecondFloor.h"
using namespace std;

namespace {


	const string ANIMATION_FAILPATH = "Assets/animData/enemy/";

	const string ANIMATION_EXTENTION = ".tka";

}

EnemyAnimation::EnemyAnimation()
{
	// 待機
	SetAnimation(enAnimationClip_Idle, "enemyIdle", true);
	// 歩き
	SetAnimation(enAnimationClip_Walk, "enemyWalking", true);
	// 走る
	SetAnimation(enAnimationClip_Run, "enemyRun", true);
}

EnemyAnimation::~EnemyAnimation()
{

}

bool EnemyAnimation::Start()
{
	return true;
}

void EnemyAnimation::Update()
{
	m_modelRender.Update();
}

void EnemyAnimation::SetAnimation(const EnAnimationClip animationClip, const string animationFileName, const bool loopFlag)
{
	string FileName = ANIMATION_FAILPATH + animationFileName + ANIMATION_EXTENTION;
	
	m_enemyAnimationClips[animationClip].Load(FileName.c_str());
	m_enemyAnimationClips[animationClip].SetLoopFlag(loopFlag);
}