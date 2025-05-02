#pragma once
class Player;
class Loading;
class Game;
class Title :public IGameObject

{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_spriteRender;
	SoundSource* m_bgm = nullptr;
	SoundSource* se;

	Loading		* m_Loading;
	bool		m_isWaitLoadOut = false;
	float		m_alpha = 0.0f;
	SpriteRender m_pressButton;
};



