#pragma once
class Game;
class Player;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class FloorManager : public IGameObject
{
public:
	FloorManager();
	~FloorManager();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void FindFloor();				//ステージ内の床を見つける
	void SetPointLight();			//ポイントライトの設定
	void DeletePointLight();		//ポイントライトを削除する
	void AddStatus();				//デバフを与える
	void AddStatusTimer();			//効果時間の表示
	void CalcStatusTime();			//効果時間の減少
	void RevertState();				//デバフを消す

	/// <summary>
	/// 床の効果
	/// </summary>
	enum FloorState {
		Normal,			//通常状態
		ReverseState,	//あべこべ状態
		SlowState,		//鈍足状態
		BlindState,		//視界制限状態
	};


	ReverseFloor*				m_reverseFloor;					//あべこべ床
	SlowFloor*					m_slowFloor;					//鈍足床
	BlindFloor*					m_blindFloor;					//視界制限床
	SpriteRender*				m_spriteRender;					//画像
	FontRender*					m_fontRender;					//文字
	PointLight*					m_pointL;						//ポイントライト
	Player*						m_player;						//プレイヤー
	Game*						m_game = nullptr;				//ゲーム

	Vector3					pointLightPosition;
	int						m_floorState = FloorState::Normal;				//プレイヤーが受けたデバフ
	int						m_saveState  = FloorState :: Normal;			//プレイヤーが受けたデバフを保存する
	int						LightCount = 0;				
	float					m_floorTimer	= 7.0f;							//効果時間

private:
	bool					m_isAddStatus = false;
};

