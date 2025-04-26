#include "stdafx.h"
#include "PlayerState.h"
//
//// 移動ステート。
//void PlayerMoveState::Enter()
//{
//}
//
//void PlayerMoveState::Update()
//{
//}
//
//void PlayerMoveState::Exit()
//{
//}
//
//// 待機ステート。
//void PlayerIdleState::Enter()
//{
//}
//
//void PlayerIdleState::Update()
//{
//}
//
//void PlayerIdleState::Exit()
//{
//}
//
//// 歩きステート。
//void PlayerWalkState::Enter()
//{
//}
//
//void PlayerWalkState::Update()
//{
//	// 移動処理。
//	if (fabsf(m_player->m_moveSpeed.x) >= 0.001f || fabsf(m_player->m_moveSpeed.z) >= 0.001f)
//	{
//		//ステートを2(歩き)にする。
//		m_player->m_currentState = m_player->State_Walk;
//		// 走ってない判定にする。
//		m_player->m_dashFlag = false;
//	}
//}
//
//void PlayerWalkState::Exit()
//{
//}
//
//// 走りステート。
//void PlayerRunState::Enter()
//{
//}
//
//void PlayerRunState::Update()
//{
//	// もしAボタンが押されたら。
//	if (g_pad[0]->IsPress(enButtonA))
//	{
//		// 走る。
//		m_player->m_currentState = m_player->State_Run;
//		// 走っている判定にする。
//		m_player->m_dashFlag = true;
//
//		// スタミナが0で走ってない判定のとき
//		if (m_player->m_sutamina <= 0 && m_player->m_dashFlag != false)
//		{
//			// ダッシュ状態から歩く判定になる。
//			m_player->m_currentState = m_player->State_StayRun;
//		}
//	}
//	// もしBボタンが押されたら。
//	else if (g_pad[0]->IsPress(enButtonB))
//	{
//		// しゃがむ。
//		m_player->m_currentState = m_player->State_CrouchWalk;
//	}
//}
//
//void PlayerRunState::Exit()
//{
//}
//
//// しゃがみステート。
//void PlayerCrouchState::Enter()
//{
//}
//
//void PlayerCrouchState::Update()
//{
//}
//
//void PlayerCrouchState::Exit()
//{
//}
//
//// しゃがみ歩きステート。
//void PlayerCrouchWalkState::Enter()
//{
//}
//
//void PlayerCrouchWalkState::Update()
//{
//}
//
//void PlayerCrouchWalkState::Exit()
//{
//}
