#pragma once
#include "PlayerState.h"

//class Enemy;
class GameClear;
class Staier;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class Player : public IGameObject
{
public:
	// フレンドクラスを使用し、PlayerStateクラスでPlayerクラスのメンバ変数を使用できるようにする。
	friend class PlayerIdleState;
	friend class PlayerWalkState;
	friend class PlayerRunState;
	friend class PlayerCrouchState;
	friend class PlayerCrouchWalkState;

	Player();
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	// test
	void Move(float dash);					// 移動処理。
	void Rotation();
	void StaminaCalk();						// スタミナ計算(増減)。
	void DashStaminaCalk();				// スタミナ計算(減算)。

	// 座標を取得
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	// プレイヤーが死亡している？
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

	AnimationClip				m_animationClips[enAnimationClip_Num];
	CharacterController			m_charCon;							//キャラコン
	
	Vector3						stickL;								//プレイヤーの進行方向を決定する。
	Vector3						m_position;
	Vector3						m_moveSpeed;						//移動速度
	Vector3						m_dash;
	float		     	        m_hp = 0;
	float                       m_max_stamina = 100;               // スタミナの最大値。
	float                       m_stamina = m_max_stamina;    	// 現在のスタミナ。
	bool                        m_dashFlag = false;                 // 走り判定。
	
	Quaternion					rotation;
	float				    	m_moveDir = 1.0f;

	IPlayerState* m_playerStateList[enPlayerState_Max];	// ステートリスト
	int m_currentPlayerState;					// 現在の状態
	int m_requestPlayerState;					// 次に使いたい状態(リクエスト)	 
private:
	ModelRender					m_modelRender;
};