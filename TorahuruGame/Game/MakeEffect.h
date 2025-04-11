#pragma once

enum EffectName
{
	enEffectName_Fire,
	//‚±‚±‚É’Ç‰Á‚µ‚Ä‚¢‚­
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

