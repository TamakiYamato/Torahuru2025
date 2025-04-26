#pragma once
#include "Player.h"
//
//enum enPlayerState
//{
//	enPlayerState_Idle,
//	enPlayerState_Walk,
//	enPlayerState_Run,
//	enPlayerState_Crouch,
//	enPlayerState_CrouchWalk,
//	enPlayerState_Max
//};
//
//class Player;
//class IPlayerState
//{
//public:
//	// 純粋仮想関数:実装先で絶対使わなければならない関数。
//	virtual void Enter()	= 0;       // 状態が切り替わった際に1度だけ呼ばれる。→アニメーション
//	virtual void Update()	= 0;      // 更新。→パッドの入力等。
//	virtual void Exit()		= 0;        // 状態が切り替わる際に１度だけ呼ばれる。→ 状態の後処理。例) newした際の削除。
//    Player*  m_player		= 0;
//};
//
//// 待機ステート。
//class PlayerIdleState : public IPlayerState
//{
//	void Enter()	override;
//	void Update()	override;
//	void Exit()		override;
//};
//
//// 歩きステート。
//class PlayerWalkState : public IPlayerState
//{
//	void Enter()	override;
//	void Update()	override;
//	void Exit()		override;
//};
//
//// 走りステート。
//class PlayerRunState : public IPlayerState
//{
//	void Enter()	override;
//	void Update()	override;
//	void Exit()		override;
//};
//
//// しゃがみステート。
//class PlayerCrouchState : public IPlayerState
//{
//	void Enter()	override;
//	void Update()	override;
//	void Exit()		override;
//};
//
//// しゃがみ歩きステート。
//class PlayerCrouchWalkState : public IPlayerState
//{
//	void Enter()	override;
//	void Update()	override;
//	void Exit()		override;
//};
//
//// 移動ステート。
//class PlayerMoveState : public IPlayerState 
//{
//public:
//	void Enter()	override;
//	void Update()	override;
//	void Exit()		override;
//};
//
