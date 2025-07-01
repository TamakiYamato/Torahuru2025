#pragma once
class Game;
class Player;
class TutorialUI;
class ReverseFloor;
class SlowFloor;
class BlindFloor;


class FloorManager : public IGameObject
{
private:

	TutorialUI* m_tutorialUI;//チュートリアルUI
	ReverseFloor* m_reverseFloor;//あべこべ床
	SlowFloor* m_slowFloor;	//鈍足床
	BlindFloor* m_blindFloor; //視界制限床
	SpriteRender* m_spriteRender; //画像
	FontRender* m_fontRender; //文字
	PointLight* m_pointL; //ポイントライト
	Player* m_player; //プレイヤー
	Game* m_game = nullptr;	//ゲーム
	
	Vector3 m_pointLightPosition; //ポイントライトの位置

	bool m_isPlayerAddStatus = false;

	
	~FloorManager() {};

	/// <summary>
	/// start
	/// </summary>
	/// <returns></returns>
	bool Start();

	/// <summary>
	/// アップデート
	/// </summary>
	void Update();

	/// <summary>
	/// 効果が付与されたときに出す画像
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);

	/// <summary>
	/// ステージ内にある床をすべて見つける
	/// ステート変更
	/// </summary>
	void FindFloor();

	/// <summary>
	/// ポイントライトのセット
	/// </summary>
	void SetPointLight();//ポイントライトの設定

	/// <summary>
	/// ポイントライトの削除
	/// </summary>
	void DeletePointLight();

	/// <summary>
	/// デバフをかける
	/// </summary>
	void AddStatus();

	/// <summary>
	/// 効果時間と画像の表示
	/// </summary>
	void AddStatusTimer();

	/// <summary>
	/// 効果時間の減少
	/// </summary>
	void PlayerCalcStatusTime();

	/// <summary>
	/// 効果をリセット
	/// </summary>
	void PlayerRevertState();

public:	
	FloorManager() {};

	/// <summary>
	/// 床の状態
	/// </summary>
	enum FloorState {
		Normal,				//通常状態
		ReverseState,		//あべこべ状態
		SlowState,			//鈍足状態
		BlindState,			//視界制限状態
		FireTriggerState,	//火炎放射器オンオフ切り替え
	};
	FloorState m_floorState = Normal;//床の状態

	int	m_playerFloorState = FloorState::Normal; //プレイヤーが受けたデバフ
	int	m_playerSaveState  = FloorState :: Normal; //プレイヤーが受けたデバフを保存する
	int	m_lightCount = 0;// 
	float m_playerFloorTimer= 7.0f;	//プレイヤー効果時間
		  

};

