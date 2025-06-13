#pragma once
class Player;
class Loading;
class BackGround;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class FloorManager;
class FireGimmic;
class PuzzleCube;
class Stairs;
class SecondFloor;
class FirstFloor;

class ThirdFloor : public IGameObject
{
public:
	ThirdFloor();
	~ThirdFloor() ;

	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
	void SetPosition();
private:
	LevelRender	m_levelRender;						//レベル
	Player* m_player = nullptr;
	//Enemy* m_enemy = nullptr;
	BackGround* m_background = nullptr;
	FloorManager* m_floorManager;					//特殊床の管理

	
	SecondFloor* m_secondFloor = nullptr;	//1階
	float m_loadingTimer = 0.0f;
	bool m_isLoadingDeleted = false;
	Loading* m_loading = nullptr;				//ローディング画面

};

