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
	bool Start() ;
	void Update() ;
	void Render(RenderContext& rc);//ƒQ[ƒ€ƒNƒŠƒA‚ğ‚Á‚Ä‚­‚é‚½‚ß
	Player* m_player;
	SpriteRender m_spriteRender;
};

