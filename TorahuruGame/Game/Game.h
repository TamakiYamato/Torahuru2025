#pragma once

#include "Level3DRender/LevelRender.h"
class Sumaho;
class Player;
class BackGround;
class GameCamera;

class GameClear;
class Title;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	float m_timer = 0.0f;
	FontRender				m_fontRender;
	Vector3 m_position;
private:
	Player* m_player = nullptr;
	
	GameClear* m_gameClear = nullptr;
	SoundSource* m_bgm = nullptr;
	SoundSource* m_se = nullptr;
	BackGround* m_background = nullptr;
	ModelRender m_modelRender;
	GameCamera* m_gamecamera = nullptr;
	Sumaho* m_sumaho = nullptr;
	SkyCube* m_SkyCube = nullptr; //背景
	int m_skycubeType = enSkyCubeType_NightToon;
	void InitSky();
	Vector3 m_pos;
	//フォントを更新
	void UpdateFont();


	//タイマーの更新
	void CountTimer();
};

