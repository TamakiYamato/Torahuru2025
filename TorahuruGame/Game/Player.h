#pragma once
#include "PlayerState.h"

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
	void StaminaCalc();						// スタミナ計算(増減)。
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
	void UpdateModelByState();	//ステートによってモデルのアップデートを変更

	ModelRender m_normalModel;					//通常のモデル		
	ModelRender m_reverseModel;					//暗転床踏んだ時のモデル
	ModelRender m_slowModel;					//減速床を踏んだ時のモデル

	FloorManager* m_floorManager = nullptr;

	//プレイヤーの見た目を変更するリクエストフラグ
	bool m_requestChangeModel = false;

	AnimationClip m_animationClips[enAnimationClip_Num];
	//キャラコン
	CharacterController	m_charCon;
	//プレイヤーの進行方向を決定する。
	Vector3	stickL;
	Vector3	m_position;
	//移動速度
	Vector3	m_moveSpeed;
	Vector3 m_dash;
	float m_hp = 0;
	// スタミナの最大値。
	float m_max_stamina = 100;
	// 現在のスタミナ。
	float m_stamina = m_max_stamina;
	// 走り判定。
	bool m_dashFlag = false;

	Quaternion rotation;
	float m_moveDir = 1.0f;

	// ステートリスト
	IPlayerState* m_playerStateList[enPlayerState_Max];
	// 現在の状態
	int m_currentPlayerState;
	// 次に使いたい状態(リクエスト)
	int m_requestPlayerState;
private:
	ModelRender* m_modelRender = nullptr;
};