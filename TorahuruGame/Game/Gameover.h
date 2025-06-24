#pragma once
class Game;
class Player;
class Title;
class GameManager;

class Gameover:public IGameObject
{
public:
	Gameover();
	~Gameover();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Player*			m_player;
	GameManager* m_gameManager;
	SpriteRender	m_spriteRender;

private:
	bool				m_isReturnTitle = false;
};

