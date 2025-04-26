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
	// 繝｡繝ｳ繝仙､画焚/繧ｯ繝ｩ繧ｹ縺ｧ螳夂ｾｩ縺輔ｌ縺溷､画焚(螻樊ｧ縺ｿ縺溘＞縺ｪ諢溘§)縲・
	SpriteRender m_spriteRender;
	SpriteRender m_spriteRender2;
	Player* m_player;
};

