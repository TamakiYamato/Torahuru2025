#pragma once
class Player;
class Tips;
class Loading;
class Game;
//class GameManager;
class Title :public IGameObject

{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Buttontext();

private:
	SpriteRender m_spriteRender;
	SpriteRender m_startButtonRender;
	SoundSource* m_bgm = nullptr;
	SoundSource* se;

	Loading		* m_Loading;
	Tips* m_tips;
	bool		m_isWaitLoadOut = false;
	float		m_alpha = 0.0f;
	SpriteRender m_pressButton;
};



