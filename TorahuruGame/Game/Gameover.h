#pragma once
class Game;
class Player;
class Title;
class GameClear;

class Gameover:public IGameObject
{
public:
	Gameover();
	~Gameover();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	Player* m_player;//ƒvƒŒƒCƒ„[
	SpriteRender m_spriteRender;
	float m_timer = 120.0f;
};

