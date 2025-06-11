#pragma once
class Player;
class Game;

class Stamina : public IGameObject
{
public:
	Stamina();
	~Stamina();

	bool Start();
	void Update();
	void StaminaCalc();
	void Render(RenderContext& rc);

private:
	// メンバ変数。
	SpriteRender m_spriteRender;
	SpriteRender m_spriteRender2;
	SpriteRender m_spriteRender3;
	SpriteRender m_spriteRender4;
	SpriteRender m_spriteRender5;
	Player* m_player;
};

