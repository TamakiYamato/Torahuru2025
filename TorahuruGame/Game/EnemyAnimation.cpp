#include "stdafx.h"
#include "EnemyAnimation.h"
using namespace std;

namespace {
	// 繝輔ぃ繧､繝ｫ繝代せ縺ｯ譁・ｭ怜・縺ｪ縺ｮ縺ｧ string 繧剃ｽｿ逕ｨ縺吶ｋ縲・
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
	// 蠕・ｩ溘い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縲・
	SetAnimation(enAnimationClip_Idle, "playerIdle", true);
	// 豁ｩ縺阪い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縲・
	SetAnimation(enAnimationClip_Walk, "playerWalking", true);
	// 襍ｰ繧九い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縲・
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

// const縺ｧ繝輔ぃ繧､繝ｫ繧定ｪｭ縺ｿ蜿悶ｋ縲・
void EnemyAnimation::SetAnimation(const EnAnimationClip animationClip, const string animationFileName, const bool loopFlag)
{
	// 蜈ｱ騾壼喧縺励◆繝輔ぃ繧､繝ｫ蜷阪・
	string FileName = ANIMATION_FAILPATH + animationFileName + ANIMATION_EXTENTION;
	//std::strinstr();
	// c_str()繝｡繧ｾ繝・ヨ繧貞他縺ｳ蜃ｺ縺吶％縺ｨ縺ｧ const char* 縺ｫ螟画鋤縺輔ｌ繧九・
	m_enemyAnim[animationClip].Load(FileName.c_str());
	m_enemyAnim[animationClip].SetLoopFlag(loopFlag);
}