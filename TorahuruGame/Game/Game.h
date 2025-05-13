#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class Sutamina;
class Enemy;
class BackGround;
class FirstFloor;
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
	void SetFirstFloor();
	void SetLoading();
	void SetGameClear();
	void SetSutamina();
	void InitSky();
	void LightSetting();
	void TutorialText();
	void UpdateFont();				//
	void CountTimer();				//
	
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	SkyCube* m_skyCube = nullptr;				  //
	Tutorial* m_tutorial;						  //
	Tutorial* m_tutorial2;                        //
	Tutorial* m_tutorial3;                        //
	Tutorial* m_tutorial4;                        //

private:
	FirstFloor*					m_firstFloor;
	Player*						m_player = nullptr;
	Sutamina*                   m_setSutamina;
	Enemy*						m_enemy	= nullptr;
	SoundSource*				m_bgm = nullptr;
	SoundSource*				m_se = nullptr;
	
	ModelRender					m_modelRender;
	Stairs*						m_stairs = nullptr;					//階段
	
	
	
	GameCamera*					m_gamecamera = nullptr;				//ゲームカメラ

	FontRender					m_fontRender;
	Loading*					m_Load;
	bool						m_isWaitLoadOut;

	std::vector<ReverseFloor*>	m_reverseFloorLists;		//すべてのあべこべ床
	std::vector<SlowFloor*>		m_slowFloorLists;			//すべての鈍足床
	std::vector<BlindFloor*>	m_blindFloorLists;			//すべての視界制限床

	Vector3						m_position;
	Vector3						m_pos;
	int		m_skycubeType	= enSkyCubeType_NightToon;
	float	m_timer			= 120.0f;
	
};

