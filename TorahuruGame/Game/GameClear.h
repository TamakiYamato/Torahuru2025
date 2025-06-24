#pragma once
class Game;
class Player;
class Stairs;
class Title;
class GameManager;
class GameClear :public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start() ;
	void Update() ;
	void Render(RenderContext& rc);

	Player*				m_player;
	GameManager*		m_gameManager;
	SpriteRender		m_spriteRender;
	Stairs*				m_stairs = nullptr;

private:
	//タイトルに戻るかのフラグ
	bool				m_isReturnTitle = false;
};

