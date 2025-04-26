#pragma once


enum EffectName
{
	enEffectName_Fire,
	//縺薙％縺ｫ霑ｽ蜉縺励※縺・￥
	enEffectName_Num,

};

class MakeEffect : public IGameObject
{
public:
	MakeEffect();
	~MakeEffect();
	bool Start();
	void Update();
};

