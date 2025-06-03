#pragma once
class BackGround;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class FloorManager;
class FireGimmic;
class Stairs;
class GameClear;
class Player;
class SecondFloor;
class TutorialUI;
class GameCamera;
class Stamina;
class TutorialUI;
class Scene;
class TutorialUI;
class Loading;
class Title;
class Game;
class FirstFloor : public IGameObject
{
public:
	FirstFloor();
	~FirstFloor();
	
	bool Start();
	void Update();
	void SetLoading();//Loading
	void GoToNextStage();
	void Render(RenderContext& rc);
	void SetPosition();


	ModelRender m_modelRender;
	LevelRender	m_levelRender;						//レベル
	FirstFloor* m_firstFloor = nullptr;
	SecondFloor* m_secondFloor ;
	BackGround* m_background = nullptr;
	GameCamera* m_gamecamera;
	FloorManager* m_floorManager;					//特殊床の管理
	TutorialUI* m_tutorialUI;
	Stamina* m_stamina;
	FontRender m_fontRender;
	std::vector<ReverseFloor*> m_reverseFloorList;				    //あべこべ床
	std::vector<SlowFloor*>    m_slowFloorList;//ここ二フロアを府登録s瑠う
	std::vector<BlindFloor*>   m_blindFloorList;
	std::vector<FireGimmic*>m_fireGimmicList;
	std::vector<Stairs*>m_stairsGimmicList;
	std::vector<TutorialUI*>m_tutorialUIList;
	SlowFloor* m_slowFloor;						    //鈍足床
	BlindFloor* m_blindFloor;						//視界制限床
	FireGimmic* m_fireGimmic = nullptr;				//火炎放射器
	Stairs* m_stairs=nullptr;
	Player* m_player=nullptr;
	Loading* m_loading = nullptr; // ローディング画面のポインタ

	SpriteRender m_pressButton;
	SpriteRender m_spriteRender;

	bool m_isStageChanging = false;
	bool m_isWaitLoadOut = false;
	bool m_isLoadingStarted = false;

	float m_fadeAlpha = 0.0f;
	float		m_alpha = 0.0f;
	float m_stageChangeTimer = 0.0f;
};
