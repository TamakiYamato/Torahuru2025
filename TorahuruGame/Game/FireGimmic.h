#pragma once

class Game;
class Player;
class FireGimmic :public IGameObject
{
public:
	FireGimmic();
	~FireGimmic();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}


	// エフェクトの再生間隔を設定する
	void SetEffectInterval(const float& time)
	{
		m_effectInterval = time;
	}

	// スピードと移動制限を設定する
	void SetSppedLimit(const float& speed, const float& limit)
	{
		m_speed = speed;
		m_limit = limit;
	}


	// 移動するフラグを設定する
	void SetMoveFlag(const bool& flag)
	{
		m_moveFlag = flag;
	}

private:
	void Move();												//移動
	void PlayEffect();											//エフェクトの再生
	void Collision();											//エフェクト再生中のみコリジョンを作成
	void PlaySE();												//効果音を再生する											//マップ移動の処理
	ModelRender				m_modelRender;
	Vector3					m_position = Vector3::Zero;
	Vector3					m_firstPosition = Vector3::Zero;
	EffectEmitter* m_fire = nullptr;					//炎のギミックエフェクト
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	SoundSource* m_se;								//炎SE
	SpriteRender			m_mapSprite;						//マップの画像

	enum enMovingState																//動きのステート
	{
		enMovingState_MovingRight,													//右に移動
		enMovingState_MovingLeft													//左に移動
	};
	enMovingState			m_MovingFloorState = enMovingState_MovingRight;	//ステートの変数

	bool					m_moveFlag = false;					//trueだったら動く

	float					m_effectIntervalTimer = 0.0f;		//エフェクトの間隔制御のタイマー
	float					m_effectInterval = 5.0f;			//エフェクトを停止させる間隔

	float	m_limit = 100.0f;
	float	m_speed = 20.0f;
};
