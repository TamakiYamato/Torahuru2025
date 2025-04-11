#include "stdafx.h"
#include "MakeEffect.h"

MakeEffect::MakeEffect()
{
}

MakeEffect::~MakeEffect()
{
}

bool MakeEffect::Start()
{
	//ここにエフェクトのファイルパスを入れる
	EffectEngine::GetInstance()->ResistEffect(enEffectName_Fire, u"Assets/effect/FireEffect.efk");
	return true;
}

void MakeEffect::Update()
{
}
