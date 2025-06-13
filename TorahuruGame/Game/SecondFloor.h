#pragma once
class BackGround;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class FloorManager;
class FirstFloor;
class FireGimmic;
class Stairs;
class GameClear;
class Player;
class Game;
class RotationFloor;
class BackGroundTwo;
class Scene;
class Loading;
class Enemy;
class EnemyAnimation;
class Pyramid;
class ThirdFloor;

class SecondFloor : public IGameObject
{
public:
	SecondFloor();
	~SecondFloor();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	
	void GoToNeoStage();
	void SetPosition();



	ThirdFloor* m_thirdFloor = nullptr;	//3階
private:
	LevelRender	m_levelRender;						//レベル
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;
	FirstFloor * m_firstFloor = nullptr;	//1階
	Pyramid* m_pyramid = nullptr;
	
private:
	float m_loadingTimer = 0.0f;
	bool m_isLoadingDeleted = false;
	Loading* m_loading = nullptr;				//ローディング画面
	EnemyAnimation* m_enemyAnimation = nullptr;	//敵のアニメーション



};