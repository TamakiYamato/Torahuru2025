#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class Specialfloor;
class Stairs;
class Title;
class GameClear;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	float                   m_timer = 120.0f;

	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
	FontRender				m_fontRender;
	Vector3                 m_position;
private:
	Player* m_player = nullptr;
	SoundSource* m_bgm = nullptr;
	SoundSource* m_se = nullptr;
	BackGround* m_background = nullptr;
	ModelRender m_modelRender;
	Stairs* m_stairs = nullptr;//階段
	//LevelRender m_levelRender;//レベル
	GameCamera* m_gamecamera = nullptr;
	SkyCube* m_SkyCube = nullptr; //背景
	int m_skycubeType = enSkyCubeType_NightToon;
	void InitSky();
	Vector3 m_pos;
	//フォントを更新
	void UpdateFont();
	//タイマーの更新
	void CountTimer();
};

