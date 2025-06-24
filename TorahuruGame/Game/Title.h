#pragma once
class Player;
class Tips;
class Loading;
class Game;
class GameManager;

class Title :public IGameObject

{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Buttontext();

	bool		m_sceneTransformFlag = false; // Scene切り替えフラグ
private:
	SpriteRender m_spriteRender;
	SpriteRender m_startButtonRender;
	SoundSource* m_bgm = nullptr;
	SoundSource* se;
	SpriteRender m_pressButton;

	Loading* m_Loading = nullptr;
	GameManager* m_gameManager = nullptr;
	Tips* m_tips = nullptr;
	bool		m_isWaitLoadOut = false;
	float		m_alpha = 0.0f;
	
};



