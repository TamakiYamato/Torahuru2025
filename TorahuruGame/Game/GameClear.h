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
	void Render(RenderContext& rc);				//ゲームクリアを持ってくるため

	Player*				m_player;
	SpriteRender		m_spriteRender;
	Stairs*				m_stairs = nullptr;		//ここだと階段のインスタンスを保持する
};

