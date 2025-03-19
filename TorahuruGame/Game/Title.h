#pragma once
class Player;
class Game;
class GameClear;
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
	float m_alpha = 0.0f;
	SoundSource* m_bgm = nullptr;
	SoundSource* se;
	bool m_isWaitFadeOut = false;
};



