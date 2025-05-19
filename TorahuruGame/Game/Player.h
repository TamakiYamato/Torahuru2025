#pragma once

//class Enemy;
class GameClear;
class Staier;
class FloorManager;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Anim() {};
	void Rotation();
	void ManageState();						//ステート管理。
	void SutaminaCalk();
	void PlayAnimation();					//アニメーションの再生。

	// 座標を取得
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// プレイヤーが死亡している？
	const bool isPlayerDead() const
	{
		return m_hp <= 0;
	}

	//キャラコンの取得
	CharacterController& GetCharacterController()
	{
		return m_charCon;
	}

	enum PlayerState {
		State_Idle,					// 待機。
		State_Walk,					// 歩く。
		State_Run,					// 走る。
		State_Crouch,				// しゃがむ。
		State_Crouching,			// しゃがみこむ。
		State_CrouchStanding,		// 立ち上がる。
		State_CrouchWalk,			// しゃがみ歩き。
		State_StayRun		     	// しゃがみ歩き。
	};

	enum EnAnimationClip {
		enAnimClip_Idle,			// 待機。
		enAnimClip_Walk,			// 歩く
		enAnimClip_Run,				// 走る。
		enAnimClip_Crouch,			// しゃがむ。
		enAnimClip_Crouching,		// しゃがみこむ。
		enAnimClip_CrouchStanding,	// 立ち上がる。
		enAnimClip_CrouchWalk,		// しゃがみ歩き。
		enAnimClip_Jump,			// ジャンプ
		enAnimationClip_Num
	};


	//アニメーションを共通化する。
	void SetAnimation(EnAnimationClip animationClip, std::string animationFileName, bool loopFlag);
	void UpdateModelByState();	//ステートによってモデルのアップデートを変更

	ModelRender m_reverseModel;					//暗転床踏んだ時のモデル
	ModelRender m_slowModel;					//減速床を踏んだ時のモデル

	AnimationClip				m_animationClips[enAnimationClip_Num];
	CharacterController			m_charCon;							//キャラコン
	ModelRender					m_modelRender;
	FloorManager*				m_floorManager;	
	Vector3						stickL;								//プレイヤーの進行方向を決定する。
	Vector3						m_position;
	Vector3						m_moveSpeed;						//移動速度
	Vector3						m_dash;
	float		     	        m_hp = 0;
	float                       m_max_sutamina = 100;               // スタミナの最大値。
	float                       m_sutamina = m_max_sutamina;    	// 現在のスタミナ。
	bool                        m_dashFlag = false;                 // 走り判定。
	PlayerState					m_playerState = State_Idle;
	Quaternion					rotation;
	float				    	m_moveDir = 1.0f;
private:
};