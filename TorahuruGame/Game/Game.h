#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class Specialfloor;
class kaidan;
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
	FontRender				m_fontRender;
	Vector3                 m_position;
	SpriteRender m_spriteRender;
private:
	Player* m_player = nullptr;
	SoundSource* m_bgm = nullptr;
	SoundSource* m_se = nullptr;
	BackGround* m_background = nullptr;
	ModelRender m_modelRender;
	LevelRender m_levelRender;//���x��
	GameCamera* m_gamecamera = nullptr;
	kaidan* m_kaidan = nullptr;//�K�i
	SkyCube* m_SkyCube = nullptr; //�w�i
	int m_skycubeType = enSkyCubeType_NightToon;
	void InitSky();
	Vector3 m_pos;
	//�t�H���g���X�V
	void UpdateFont();
	//�^�C�}�[�̍X�V
	void CountTimer();
};

