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
	void UpdateFont();				//郢晁ｼ斐°郢晢ｽｳ郢晏現・定ｭ厄ｽｴ隴・ｽｰ
	void CountTimer();				//郢ｧ・ｿ郢ｧ・､郢晄ｧｭ繝ｻ邵ｺ・ｮ隴厄ｽｴ隴・ｽｰ
	
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	SkyCube* m_skyCube = nullptr;				//髢ｭ譴ｧ蜍ｹ
	Tutorial* m_tutorial;                         //郢昶・ﾎ礼ｹ晢ｽｼ郢晏現ﾎ懃ｹｧ・｢郢晢ｽｫ
	Tutorial* m_tutorial2;                        //郢昶・ﾎ礼ｹ晢ｽｼ郢晏現ﾎ懃ｹｧ・｢郢晢ｽｫ
	Tutorial* m_tutorial3;                        //郢昶・ﾎ礼ｹ晢ｽｼ郢晏現ﾎ懃ｹｧ・｢郢晢ｽｫ
	Tutorial* m_tutorial4;                        //郢昶・ﾎ礼ｹ晢ｽｼ郢晏現ﾎ懃ｹｧ・｢郢晢ｽｫ

private:
	Player*						m_player = nullptr;
	Sutamina*                   m_setSutamina;
	Enemy*						m_enemy	= nullptr;
	SoundSource*				m_bgm = nullptr;
	SoundSource*				m_se = nullptr;
	BackGround*					m_background = nullptr;
	ModelRender					m_modelRender;
	Stairs*						m_stairs = nullptr;					//鬮ｫ蜿厄ｽｮ・ｵ
	LevelRender					m_levelRender;						//郢晢ｽｬ郢晏生ﾎ・
	FloorManager*				m_floorManager;						//3驕橸ｽｮ邵ｺ・ｮ陟守ｿｫ・帝ｂ・｡騾・・
	ReverseFloor*				m_reverseFloor;						//邵ｺ繧・・邵ｺ阮吮・陟弱・
	SlowFloor*					m_slowFloor;						//鬩､蟠趣ｽｶ・ｳ陟弱・
	BlindFloor*					m_blindFloor;						//髫穂ｹ滄・陋ｻ・ｶ鬮ｯ莉呻ｽｺ繝ｻ
	
	GameCamera*					m_gamecamera = nullptr;				//郢ｧ・ｫ郢晢ｽ｡郢晢ｽｩ
	FireGimmic*					m_fireGimmic = nullptr;				//霓､蠑ｱ繝ｻ郢ｧ・ｮ郢晄ｺ倥Ε郢ｧ・ｯ
	FontRender					m_fontRender;

	std::vector<ReverseFloor*>	m_reverseFloorLists;		//邵ｺ繧・・邵ｺ阮吮・陟守ｿｫ繝ｻ陷台ｼ∝求騾包ｽｨ邵ｲ繝ｻ
	std::vector<SlowFloor*>		m_slowFloorLists;			//鬩､蟠趣ｽｶ・ｳ陟守ｿｫ繝ｻ陷台ｼ∝求騾包ｽｨ邵ｲ繝ｻ
	std::vector<BlindFloor*>	m_blindFloorLists;			//髫穂ｹ滄・陋ｻ・ｶ鬮ｯ莉呻ｽｺ鄙ｫ繝ｻ陷台ｼ∝求騾包ｽｨ邵ｲ繝ｻ

	Vector3						m_position;
	Vector3						m_pos;
	int		m_skycubeType	= enSkyCubeType_NightToon;
	float	m_timer			= 120.0f;
	
};

