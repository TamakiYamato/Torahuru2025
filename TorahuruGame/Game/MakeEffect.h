#pragma once


enum EffectName
{
	enEffectName_Fire,
	//ここに追加していく
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

