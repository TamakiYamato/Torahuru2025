#pragma once

class Player;
class IPlayerState
{
public:
	// 純粋仮想関数:実装先で絶対使わなければならない関数。
	virtual void Enter() = 0;       // 状態が切り替わった際に1度だけ呼ばれる。→アニメーション
	virtual void Update() = 0;      // 更新。→パッドの入力等。
	virtual void Exit() = 0;        // 状態が切り替わる際に１度だけ呼ばれる。→ 状態の後処理。例) newした際の削除。
};

class PlayerMoveState : public IPlayerState 
{
public:
	void Enter()  override;
	void Update() override;
	void Exit()   override;

	// メンバ変数。
	Player*					m_requestSutate;
};

