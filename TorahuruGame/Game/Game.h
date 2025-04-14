#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
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

	void InitSky();
	void UpdateFont();				//フォントを更新
	void CountTimer();				//タイマーの更新
	void Intensity();				//スカイキューブのテクスチャの光の強さの変更
	
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}


private:
	Player*						m_player = nullptr;
	SoundSource*				m_bgm = nullptr;
	SoundSource*				m_se = nullptr;
	BackGround*					m_background = nullptr;
	ModelRender					m_modelRender;
	Stairs*						m_stairs = nullptr;					//階段
	LevelRender					m_levelRender;						//レベル
	ReverseFloor*				m_reverseFloor;						//あべこべ床
	SlowFloor*					m_slowFloor;						//鈍足床
	BlindFloor*					m_blindFloor;						//視界制限床
	GameCamera*					m_gamecamera = nullptr;				//カメラ
	SkyCube*					m_skyCube = nullptr;				//背景
	FireGimmic*					m_fireGimmic = nullptr;				//炎のギミック
	FontRender					m_fontRender;

	std::vector<PointLight*>	m_pointLightList;					//ポイントライト。
	Vector3						m_position;
	Vector3						m_pos;
	int m_skycubeType = enSkyCubeType_NightToon;
	float m_timer = 120.0f;
	
};

