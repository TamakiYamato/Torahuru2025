#pragma once
#include "PlayerState.h"

//class Enemy;
class PlayerState;
class GameClear;
class Staier;
class FloorManager;
class FireGimmic;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class SecondFloor;
class Player : public IGameObject
{
public:
	// フレンドクラスを使用し、PlayerStateクラスでPlayerクラスのメンバ変数を使用できるようにする。
	friend class PlayerIdleState;
	friend class PlayerWalkState;
	friend class PlayerRunState;
	friend class PlayerCrouchState;
	friend class PlayerCrouchWalkState;
	friend class PlayerDownState;
	friend class PlayerGetUpState;

	Player();
	~Player();
	bool Start();
	void Update();
	//void SetPosition(const Vector3& position);
	void Render(RenderContext& rc);
	// test
	void Move(float dash);					// 移動処理。
	void Rotation();
	void StaminaCalc();						// スタミナ計算(増減)。

	void DashStaminaCalk();					// スタミナ計算(減算)。
  void SetPosition(const Vector3& position);
  void SetGravity();
	void FireState();
	void AddFireEffect();					// 火炎放射に当たった時のモデル更新
	void InvincibleState();					// 無敵状態の更新。
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
		enAnimClip_Down,			// ダウン
		enAnimClip_GetUp,			// 起き上がる
		enAnimationClip_Num
	};

	/// <summary>
	/// 力を加算する
	/// </summary>
	/// <param name="force">プレイヤーに加える力(cm/秒)</param>
	void AddForce(const Vector3& force)
	{
		m_addForce += force;
	}

	//アニメーションを共通化する。
	void SetAnimation(EnAnimationClip animationClip, std::string animationFileName, bool loopFlag);
	void UpdateModelByState();	//ステートによってモデルのアップデートを変更

	ModelRender m_normalModel;					//通常のモデル		
	ModelRender m_reverseModel;					//暗転床踏んだ時のモデル
	ModelRender m_slowModel;					//減速床を踏んだ時のモデル
	ModelRender m_fireModel;					//火炎放射が当たった時のモデル

	FloorManager* m_floorManager = nullptr;
	IPlayerState* m_playerStateList[enPlayerState_Max]; // ステートリスト
	AnimationClip m_animationClips[enAnimationClip_Num];
	CharacterController	m_charCon; //キャラコン
	

	Vector3	stickL; //プレイヤーの進行方向を決定する。
	Vector3	m_position;
	Vector3 m_positiontwo;//追加したよ:SecondFloorのpositionを生成します
	Vector3	m_moveSpeed; //移動速度
	Vector3 m_dash;
	Quaternion m_rotation;

	float m_moveDir = 1.0f;
	float m_hp = 0;
	float m_max_stamina = 100; // スタミナの最大値。
	float m_stamina = m_max_stamina; // 現在のスタミナ。
	// スタミナの有無フラグ。
	// 初期状態はスタミナがあるのでfalse。
	bool m_staminaFlag = false;
	bool m_dashFlag = false; // 走り判定。
	bool m_playerTouchFlag = false; //プレイヤーがfloor2についたかどうかのフラグ
	bool m_requestChangeModel = false; 
	bool m_isHitFireCollision = false; //火炎放射に当たったかの確認
	bool m_isInvincible = false; // 無敵状態のフラグ。
	bool m_isTest = false; //無敵

	int m_currentPlayerState; // 現在の状態
	int m_requestPlayerState; // 次に使いたい状態(リクエスト)
	int m_InvincibleTime = 0.0f; // 無敵時間の更新用の時間。
	
private:
	ModelRender* m_modelRender = nullptr;
	FireGimmic* m_fireGimmic = nullptr;	//火炎放射器
	Vector3 m_addForce;
};