#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class Sutamina;
class Enemy;
class BackGround;
class GameCamera;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class FloorManager;
class Tutorial;
class Stairs;
class Title;
class GameClear;
class Gameover;
class FireGimmic;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void SetSutamina();
	void InitSky();
	void TutorialText();
	void UpdateFont();				//繝輔か繝ｳ繝医ｒ譖ｴ譁ｰ
	void CountTimer();				//繧ｿ繧､繝槭・縺ｮ譖ｴ譁ｰ
	
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	SkyCube* m_skyCube = nullptr;				//閭梧勹
	Tutorial* m_tutorial;                         //繝√Η繝ｼ繝医Μ繧｢繝ｫ
	Tutorial* m_tutorial2;                        //繝√Η繝ｼ繝医Μ繧｢繝ｫ
	Tutorial* m_tutorial3;                        //繝√Η繝ｼ繝医Μ繧｢繝ｫ
	Tutorial* m_tutorial4;                        //繝√Η繝ｼ繝医Μ繧｢繝ｫ

private:
	Player*						m_player = nullptr;
	Sutamina*                   m_setSutamina;
	Enemy*						m_enemy	= nullptr;
	SoundSource*				m_bgm = nullptr;
	SoundSource*				m_se = nullptr;
	BackGround*					m_background = nullptr;
	ModelRender					m_modelRender;
	Stairs*						m_stairs = nullptr;					//髫取ｮｵ
	LevelRender					m_levelRender;						//繝ｬ繝吶Ν
	FloorManager*				m_floorManager;						//3遞ｮ縺ｮ蠎翫ｒ邂｡逅・
	ReverseFloor*				m_reverseFloor;						//縺ゅ∋縺薙∋蠎・
	SlowFloor*					m_slowFloor;						//驤崎ｶｳ蠎・
	BlindFloor*					m_blindFloor;						//隕也阜蛻ｶ髯仙ｺ・
	
	GameCamera*					m_gamecamera = nullptr;				//繧ｫ繝｡繝ｩ
	FireGimmic*					m_fireGimmic = nullptr;				//轤弱・繧ｮ繝溘ャ繧ｯ
	FontRender					m_fontRender;

	std::vector<ReverseFloor*>	m_reverseFloorLists;		//縺ゅ∋縺薙∋蠎翫・蜑企勁逕ｨ縲・
	std::vector<SlowFloor*>		m_slowFloorLists;			//驤崎ｶｳ蠎翫・蜑企勁逕ｨ縲・
	std::vector<BlindFloor*>	m_blindFloorLists;			//隕也阜蛻ｶ髯仙ｺ翫・蜑企勁逕ｨ縲・

	Vector3						m_position;
	Vector3						m_pos;
	int		m_skycubeType	= enSkyCubeType_NightToon;
	float	m_timer			= 120.0f;
	
};

