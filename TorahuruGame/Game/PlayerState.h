#pragma once

class Player;

enum enPlayerState
{
	enPlayerState_Idle,
	enPlayerState_Walk,
	enPlayerState_Run,
	enPlayerState_Crouch,
	enPlayerState_CrouchWalk,
	enPlayerState_Max,
	enPlayerState_None = enPlayerState_Max,
};

class Player;
// 親クラス。
class IPlayerState
{
public:
	//コンストラクタ。
	IPlayerState(Player* player)
	{
		// 各ステートで使用できるようにプレイヤーのポインタを入れる。
		m_player = player;
	}

	// 純粋仮想関数:実装先で絶対使わなければならない関数。
	virtual void Enter() = 0;       // 状態が切り替わった際に1度だけ呼ばれる。→アニメーション
	virtual void Update() = 0;      // 更新。→パッドの入力等。
	virtual void Exit() = 0;        // 状態が切り替わる際に１度だけ呼ばれる。→ 状態の後処理。例) newした際の削除。
	// メモ書きして	。
protected:
	Player* m_player = nullptr;
	// 乗算用。
	// デフォルトの移動速度。
	float m_move = 1.0f;
	// 歩き時に乗算する数値。
	float m_walk = 1.0f;
	// ダッシュ時に乗算する数値。
	float m_run = 2.0f;
	// しゃがみ時に乗算する数値。
	float m_crouch = 0.0f;
	// しゃがみ歩き時に乗算する数値。
	float m_crouchWalk = 0.5f;
};

// 待機ステート。
class PlayerIdleState : public IPlayerState
{
public:
	//friend class PlayerMoveState;

	PlayerIdleState(Player* player)
		// 親クラスのコンストラクタを呼び出す。
		:IPlayerState(player)
	{

	}

	void Enter() override;
	void Update() override;
	void Exit()	override;
};

// 歩きステート。
class PlayerWalkState : public IPlayerState
{
public:
	PlayerWalkState(Player* player)
		:IPlayerState(player)
	{

	}

	void Enter() override;
	void Update() override;
	void Exit() override;
};

// 走りステート。
class PlayerRunState : public IPlayerState
{
public:
	PlayerRunState(Player* player)
		:IPlayerState(player)
	{

	}

	void Enter() override;
	void Update() override;
	void Exit() override;
};

// しゃがみステート。
class PlayerCrouchState : public IPlayerState
{
public:
	PlayerCrouchState(Player* player)
		:IPlayerState(player)
	{

	}

	void Enter() override;
	void Update() override;
	void Exit() override;
};

// しゃがみ歩きステート。
class PlayerCrouchWalkState : public IPlayerState
{
public:
	PlayerCrouchWalkState(Player* player)
		:IPlayerState(player)
	{

	}

	void Enter() override;
	void Update() override;
	void Exit() override;
};

