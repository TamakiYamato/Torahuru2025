#include "stdafx.h"
#include "PlayerState.h"
#include "Player.h"
#include "FireGimmic.h"

// 待機ステート。
void PlayerIdleState::Enter()
{
	// TODO: tamaki Idle状態のアニメーションを再生。
}

void PlayerIdleState::Update()
{
	// 待機中も移動床で移動するので移動処理を呼び出す。
	m_player->Move(m_move=1.0f);

	m_player->SetGravity();

	//待機アニメーションを再生する。
	m_player->m_modelRender->PlayAnimation(m_player->enAnimClip_Idle);

	// 何するの？→Idleから別の状態に切り替わるコードが欲しい。
	Vector3 LStickPower(0.0f, 0.0f, 0.0f);
	LStickPower.x = g_pad[0]->GetLStickXF();
	LStickPower.y = g_pad[0]->GetLStickYF();


	// スティック入力があったら。
	if (LStickPower.Length() >= 0.01f) {
		// 状態を歩きに切り替える。
		m_player->m_requestPlayerState = enPlayerState_Walk;
	}
	// パッドの入力がある、かつAボタンが押されたら。
	else if (LStickPower.Length() >= 0.01f && g_pad[0]->IsPress(enButtonA) && m_player->m_stamina > 0.0f) {
		// 状態を走りに切り替える。
		m_player->m_requestPlayerState = enPlayerState_Run;
	}
	// スティックの入力がある、かつBボタンが押したら。
	else if (LStickPower.Length() >= 0.01f && g_pad[0]->IsPress(enButtonB)) {
		// ステートをしゃがみ歩きに切り替える。
		m_player->m_requestPlayerState = enPlayerState_CrouchWalk;
	}
	// パッドの入力がない、かつBボタンが押されたら。
	else if (LStickPower.Length() <= 0.01f && g_pad[0]->IsPress(enButtonB)) {
		// 状態をしゃがみに切り替える。
		m_player->m_requestPlayerState = enPlayerState_Crouch;
	}
}

void PlayerIdleState::Exit()
{
}

// 歩きステート。
void PlayerWalkState::Enter()
{
}

void PlayerWalkState::Update()
{
	// 関数化した移動処理を呼び出す。
	m_player->Move(m_move = m_walk);

	//歩きアニメーションを再生する。
	m_player->m_modelRender->PlayAnimation(m_player->enAnimClip_Walk);

	// 状態解除。
	// 何するの？→Walkから別の状態に切り替わるコードが欲しい。
	Vector3 LStickPower(0.0f, 0.0f, 0.0f);
	LStickPower.x = g_pad[0]->GetLStickXF();
	LStickPower.y = g_pad[0]->GetLStickYF();

	// スティック入力がなかったら。
	if (LStickPower.Length() <= 0.01f) {
		// ステートを待機状態に切り替える。
		m_player->m_requestPlayerState = enPlayerState_Idle;
	}
	// スティックの入力がある、かつBボタンが押したら。
	else if (LStickPower.Length() >= 0.01f && g_pad[0]->IsPress(enButtonB)) {
		// ステートをしゃがみ歩きに切り替える。
		m_player->m_requestPlayerState = enPlayerState_CrouchWalk;
	}
	// スティックの入力がある、かつAボタンが押したら。
	else if (LStickPower.Length() >= 0.01f && g_pad[0]->IsPress(enButtonA) && m_player->m_stamina > 0.0f) {
		// ステートを走りに切り替える。
		m_player->m_requestPlayerState = enPlayerState_Run;
	}
}

void PlayerWalkState::Exit()
{

}
// 走りステート。
void PlayerRunState::Enter()
{

}

void PlayerRunState::Update()
{
	// 関数化した移動処理を呼び出す。
	m_player->Move(m_move = m_run);

	//走りアニメーションを再生する。
	m_player->m_modelRender->PlayAnimation(m_player->enAnimClip_Run);

	// 状態解除。
	// 何するの？→Runから別の状態に切り替わるコードが欲しい。
	Vector3 LStickPower(0.0f, 0.0f, 0.0f);
	LStickPower.x = g_pad[0]->GetLStickXF();
	LStickPower.y = g_pad[0]->GetLStickYF();


	// パッドの入力が無かったら。
	if (LStickPower.Length() <= 0.01f) {
		// ステートを待機状態に切り替える。
		m_player->m_requestPlayerState = enPlayerState_Idle;
	}
	// スタミナが無くなったら。
	else if (m_player->m_stamina <= 0.0f) {
		// 状態を歩きに切り替える。
		m_player->m_requestPlayerState = enPlayerState_Walk;
	}
	else if (!g_pad[0]->IsPress(enButtonA)) {
		// 状態を歩きに切り替える。
		m_player->m_requestPlayerState = enPlayerState_Walk;
	}
}

void PlayerRunState::Exit()
{
}

// しゃがみステート。
void PlayerCrouchState::Enter()
{
}

void PlayerCrouchState::Update()
{
	// 関数化した移動処理を呼び出す。
	m_player->Move(m_move = m_crouch);

	// しゃがみアニメーションを再生する。
	m_player->m_modelRender->PlayAnimation(m_player->enAnimClip_Crouch);

	// 状態解除。
	// 何するの？→Crouchから別の状態に切り替わるコードが欲しい。
	Vector3 LStickPower(0.0f, 0.0f, 0.0f);
	LStickPower.x = g_pad[0]->GetLStickXF();
	LStickPower.y = g_pad[0]->GetLStickYF();

	// Bボタンを離したら。
	if (!g_pad[0]->IsPress(enButtonB)) {
		// ステートを待機状態に切り替える。
		m_player->m_requestPlayerState = enPlayerState_Idle;
	}
	// パッドの入力がある、かつBボタンが押されたら。
	else if (LStickPower.Length() >= 0.01f && g_pad[0]->IsPress(enButtonB)) {
		// 状態をしゃがみ歩きに切り替える。
		m_player->m_requestPlayerState = enPlayerState_CrouchWalk;
	}
}

void PlayerCrouchState::Exit()
{
}

// しゃがみ歩きステート。
void PlayerCrouchWalkState::Enter()
{
}

void PlayerCrouchWalkState::Update()
{
	// 関数化した移動処理を呼び出す。
	m_player->Move(m_move = m_crouchWalk);

	// しゃがみ歩きアニメーションを再生する。
	m_player->m_modelRender->PlayAnimation(m_player->enAnimClip_CrouchWalk);

	// 状態解除。
	// NOTE:tamaki 何するの？→Crouchから別の状態に切り替わるコードが欲しい。
	Vector3 LStickPower(0.0f, 0.0f, 0.0f);
	LStickPower.x = g_pad[0]->GetLStickXF();
	LStickPower.y = g_pad[0]->GetLStickYF();

	// パッドの入力が無かったら。
	if (LStickPower.Length() <= 0.01f) {
		// ステートを待機状態に切り替える。
		m_player->m_requestPlayerState = enPlayerState_Idle;
	}
	// TODO: tamaki JキーとKキーを同時押しした状態で移動すると、ダッシュ時の移動速度でしゃがみ歩きするので修正する。
	// パッドの入力がある、かつBボタンが押されていなかったら。
	else if (LStickPower.Length() >= 0.01f && !g_pad[0]->IsPress(enButtonB)) {
		// 状態を歩きに切り替える
		m_player->m_requestPlayerState = enPlayerState_Walk;
	}
	// Bボタンを離したら。
	else if (LStickPower.Length() <= 0.01f && g_pad[0]->IsPress(enButtonB)) {
		// 状態をしゃがみに切り替える。
		m_player->m_requestPlayerState = enPlayerState_Crouch;
	}
}

void PlayerCrouchWalkState::Exit()
{
}

void PlayerDownState::Enter()
{
	
}

void PlayerDownState::Update()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("fireCollision");

	for (CollisionObject* collision : collisions) {
		if (collision->IsHit(m_charCon) == true) {
			m_fireTime -= g_gameTime->GetFrameDeltaTime();
			// ダウンアニメーションを再生する。
			m_player->m_modelRender->PlayAnimation(m_player->enAnimClip_Down);
			// ステートを立ち上がりに切り替える。
			m_player->m_requestPlayerState = enPlayerState_GetUp;
		}
	}
};

void PlayerDownState::Exit()
{
}

void PlayerGetUpState::Enter()
{
}

void PlayerGetUpState::Update()
{
	if (m_player->m_requestPlayerState == enPlayerState_GetUp)
	{
		m_player->m_modelRender->PlayAnimation(m_player->enAnimClip_GetUp);
	}
}

void PlayerGetUpState::Exit()
{
}
