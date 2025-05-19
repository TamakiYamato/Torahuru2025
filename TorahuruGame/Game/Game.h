#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class Stamina;
class Enemy;
class BackGround;
class FirstFloor;
class GameCamera;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class FloorManager;
class TutorialUI;
class Stairs;
class Title;
class GameClear;
class Gameover;
class Loading;
class FireGimmic;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void SetLoading();
	void SetGameClear();
	void SetSutamina();
	void InitSky();
	void LightSetting();
	
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	SkyCube* m_skyCube = nullptr;				  //

private:
	FirstFloor*					m_firstFloor=nullptr;
	FloorManager*				m_floorManager=nullptr;
	Player*						m_player = nullptr;
	Stamina*                   m_setStamina;
	Enemy*						m_enemy	= nullptr;
	SoundSource*				m_bgm = nullptr;
	SoundSource*				m_se = nullptr;
	ModelRender					m_modelRender;
	Stairs*						m_stairs = nullptr;					//階段
	GameCamera*					m_gamecamera = nullptr;				//ゲームカメラ
	TutorialUI*					m_tutorialUI;
	FontRender					m_fontRender;
	Loading*					m_Load;

	std::vector<ReverseFloor*>	m_reverseFloorLists;		//すべてのあべこべ床
	std::vector<SlowFloor*>		m_slowFloorLists;			//すべての鈍足床
	std::vector<BlindFloor*>	m_blindFloorLists;			//すべての視界制限床

	Vector3						m_position;
	Vector3						m_pos;

	bool						m_isWaitLoadOut;
	int		m_skycubeType	= enSkyCubeType_NightToon;
	float	m_timer			= 120.0f;
	
};

