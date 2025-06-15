#pragma once

#include "Level3DRender/LevelRender.h"
#include "sound/SoundSource.h"

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
class PuzzleCube;
class SecondFloor;
class RotationFloor;
class FireTriggerFloor;
//class StageManager;
//
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
	void SetPuzzleCube();
	void InitSky();
	void LightSetting();
	void TimerUI();
	void PlayBGM();
	
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	SkyCube* m_skyCube = nullptr;				  

	bool						m_isGameClearRequested = false;
	int m_dedicationItemCount = 0;

private:
	FloorManager*				m_floorManager=nullptr;
	FirstFloor*					m_firstFloor = nullptr;			//1階
	Player*						m_player;
	Stamina*                    m_setStamina;
	Enemy*						m_enemy	= nullptr;
	SoundSource*				m_bgm = nullptr;
	SoundSource*				m_se = nullptr;
	ModelRender					m_modelRender;
	Stairs*						m_stairs = nullptr;					//階段
	GameCamera*					m_gamecamera = nullptr;				//ゲームカメラ
	FireTriggerFloor*           m_fireTriggerFloor;
	PuzzleCube*	  			    m_puzzleCube = nullptr;				//パズルキューブ
	TutorialUI*					m_tutorialUI;
	FontRender					m_fontRender;
	SpriteRender				m_spriteRender;
	Loading*					m_Load;
	Title*						m_title;
	//StageManager* m_stageManager = nullptr;				//ステージマネージャー		
	std::vector<ReverseFloor*>	m_reverseFloorLists;		//すべてのあべこべ床
	std::vector<SlowFloor*>		m_slowFloorLists;			//すべての鈍足床
	std::vector<BlindFloor*>	m_blindFloorLists;			//すべての視界制限床

	Vector3						m_position;
	Vector3						m_pos;

	bool						m_isWaitLoadOut;
	
	int	m_skycubeType	= enSkyCubeType_NightToon;
	float	m_timer			= 600.0f;
	
};

