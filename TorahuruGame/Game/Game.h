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
	Player*						m_player = nullptr;
	Sutamina*                   m_setSutamina;
	Enemy*						m_enemy	= nullptr;
	SoundSource*				m_bgm = nullptr;
	SoundSource*				m_se = nullptr;
	BackGround*					m_background = nullptr;
	ModelRender					m_modelRender;
	Stairs*						m_stairs = nullptr;					//階段
	LevelRender					m_levelRender;						//レベル
	FloorManager*				m_floorManager;						//特殊床の管理
	ReverseFloor*				m_reverseFloor;						//あべこべ床
	SlowFloor*					m_slowFloor;						//鈍足床
	BlindFloor*					m_blindFloor;						//視界制限床
	
	GameCamera*					m_gamecamera = nullptr;				//ゲームカメラ
	FireGimmic*					m_fireGimmic = nullptr;				//火炎放射器
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

