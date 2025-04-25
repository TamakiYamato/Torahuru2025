#pragma once

class Game;
class Player;
class Tutorial;
class ReverseFloor;      // あべこべ床。
class SlowFloor;         // 鈍足床。
class BlindFloor;        // 鈍足床。

class TutorialUI:public IGameObject
{
public:
	TutorialUI();
	~TutorialUI();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	// メンバ変数。
	Player* m_player = nullptr;           // プレイヤー。
	Game* m_game;

public:

};

