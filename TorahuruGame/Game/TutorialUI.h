#pragma once

class Game;
class Player;
class Tutorial;
class ReverseFloor;      // 縺ゅ∋縺薙∋蠎翫・
class SlowFloor;         // 驤崎ｶｳ蠎翫・
class BlindFloor;        // 驤崎ｶｳ蠎翫・

class TutorialUI:public IGameObject
{
public:
	TutorialUI();
	~TutorialUI();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	// 繝｡繝ｳ繝仙､画焚縲・
	Player* m_player = nullptr;           // 繝励Ξ繧､繝､繝ｼ縲・
	Game* m_game;

public:

};

