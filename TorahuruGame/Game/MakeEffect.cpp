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
	//縺薙％縺ｫ繧ｨ繝輔ぉ繧ｯ繝医・繝輔ぃ繧､繝ｫ繝代せ繧貞・繧後ｋ
	EffectEngine::GetInstance()->ResistEffect(enEffectName_Fire, u"Assets/effect/FireEffect.efk");
	return true;
}


void MakeEffect::Update()
{
}
