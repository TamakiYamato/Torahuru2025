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
class Loading;
class TutorialUI;
class GameCamera;
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

	BlindFloor* m_blindFloor = nullptr;
	ReverseFloor* m_reverseFloor = nullptr;
	std::vector<ReverseFloor*> m_reverseFloorList;				    //あべこべ床
	std::vector<SlowFloor*>    m_slowFloorList;//ここ二フロアを府登録s瑠う
	std::vector<BlindFloor*>   m_blindFloorList;
	std::vector<FireGimmic*>m_fireGimmicList;
	std::vector<Pyramid*>m_stairsGimmicList;
	std::vector<TutorialUI*>m_tutorialUIList;
	TutorialUI* m_tutorialUI;
	FloorManager* m_floorManager;					//特殊床の管理
	SpriteRender m_pressButton;
	SpriteRender m_spriteRender;//
	GameCamera   *m_gamecamera;
	SecondFloor* m_secondFloor;
	BackGroundTwo* m_backgroundTwo = nullptr;
	CollisionObject* m_collisitonObject = nullptr;



	ThirdFloor* m_thirdFloor = nullptr;	//3階
private:
	LevelRender	m_levelRender;						//レベル
	Game* m_game = nullptr;
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