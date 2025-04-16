#pragma once
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
	void SetPointLight();			//スポットライトの初期設定と明るさ変更
	void AddStatus();				//効果の反映
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
	PointLight					m_pointLight;						//ポイントライト。
	std::vector<PointLight*>	m_pointLightList;					//ポイントライト。
	SkyCube*					m_skyCube;							//スカイキューブ。
	Player*						m_player;							//プレイヤー。

	int						m_floorState	= Normal;			//特殊床を踏んだかどうかのステータス。
	int						m_saveState		= Normal;			//プレイヤーの状態を保存。
	float					m_floorTimer	= 5.0f;			//特殊床の効果時間。
	bool					m_setLight		= true;				//ライトの初期設定の有無。

private:
};

