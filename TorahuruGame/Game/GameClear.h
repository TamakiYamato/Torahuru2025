#pragma once
class Game;
class Player;
class Stairs;
class Title;
class GameClear :public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);//override’Ç‰Á‚µ‚½
	Player* m_player;
	SpriteRender m_spriteRender;
};

