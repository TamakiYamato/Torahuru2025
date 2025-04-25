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
	void FindFloor();				//すべて床を見つける
	void SetPointLight();			//ポイントライトの初期設定と明るさ変更
	void DeletePointLight();		//ポイントライトのdelele
	void AddStatus();				//効果の反映
	void AddStatusTimer();			//効果時間
	void CalcStatusTime();			//効果時間の計測、状態の変更
	void RevertState();				//受けた効果を戻す

	/// <summary>
	/// 特殊床のステータス
	/// </summary>
	enum FloorState {
		Normal,			//効果なし。
		ReverseState,	//あべこべ床。
		SlowState,		//鈍足床。
		BlindState,		//視界制限床。
	};


	ReverseFloor*				m_reverseFloor;						//あべこべ床。
	SlowFloor*					m_slowFloor;						//鈍足床。
	BlindFloor*					m_blindFloor;						//視界制限床。
	SpriteRender*				m_spriteRender;
	FontRender*					m_fontRender;
	PointLight*					m_pointL;							//ポイントライト。
	Player*						m_player;							//プレイヤー。
	Game*						m_game = nullptr;					//ゲーム。

	Vector3					pointLightPosition;
	int						m_floorState	= Normal;			//特殊床を踏んだかどうかのステータス。
	int						m_saveState		= Normal;			//プレイヤーの状態を保存、値を２回以上計算されるのを防ぐ。
	float					m_floorTimer	= 7.0f;				//特殊床の効果時間。

private:
	bool					m_isAddStatus = false;
};

