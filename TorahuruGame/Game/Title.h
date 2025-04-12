#pragma once
class Player;
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

	float	m_alpha = 0.0f;
	bool	m_isWaitFadeOut = false;
};



