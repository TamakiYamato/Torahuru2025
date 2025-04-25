#pragma once
class Player;
class Game;

class Sutamina : public IGameObject
{
public:
	Sutamina();
	~Sutamina();

	bool Start();
	void Update();
	void SutaminaCalk();
	void Render(RenderContext& rc);

private:
	// メンバ変数/クラスで定義された変数(属性みたいな感じ)。
	SpriteRender m_spriteRender;
	SpriteRender m_spriteRender2;
	Player* m_player;
};

