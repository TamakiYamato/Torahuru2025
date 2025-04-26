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
	void Render(RenderContext& rc);				//繧ｲ繝ｼ繝繧ｯ繝ｪ繧｢繧呈戟縺｣縺ｦ縺上ｋ縺溘ａ

	Player*				m_player;
	SpriteRender		m_spriteRender;
	Stairs*				m_stairs = nullptr;		//縺薙％縺縺ｨ髫取ｮｵ縺ｮ繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ繧剃ｿ晄戟縺吶ｋ
};

