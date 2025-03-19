#include "stdafx.h"
#include "Player.h"
#include"Game.h"

Player::Player() {

}

Player::~Player()
{

}

bool Player:: Start()
{
	// 待機アニメーション
	m_animationClips[enAnimClip_Idle].Load("Assets/animData/player/playerIdle.tka");
	m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	// 歩きアニメーション。
	m_animationClips[enAnimClip_Walk].Load("Assets/animData/player/playerWalking.tka");
	m_animationClips[enAnimClip_Walk].SetLoopFlag(true);
	// 走りアニメーション。
	m_animationClips[enAnimClip_Run].Load("Assets/animData/player/playerRunning.tka");
	m_animationClips[enAnimClip_Run].SetLoopFlag(true);
	// しゃがみアニメーション。
	m_animationClips[enAnimClip_Crouch].Load("Assets/animData/player/playerCrouch.tka");
	m_animationClips[enAnimClip_Crouch].SetLoopFlag(true);
	// しゃがみ歩きアニメーション。
	m_animationClips[enAnimClip_CrouchWalk].Load("Assets/animData/player/playerCrouched walking.tka");
	m_animationClips[enAnimClip_CrouchWalk].SetLoopFlag(true);
	// しゃがみこみアニメーション。
	m_animationClips[enAnimClip_Crouching].Load("Assets/animData/player/playerCrouching.tka");
	m_animationClips[enAnimClip_Crouching].SetLoopFlag(false);
	// 立ち上がりアニメーション。
	m_animationClips[enAnimClip_CrouchStanding].Load("Assets/animData/player/playerCrouch Standing.tka");
	m_animationClips[enAnimClip_CrouchStanding].SetLoopFlag(false);

	/*m_animationClips[enAnimClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimClip_Jump].SetLoopFlag(false);*/
	// キャラクターを読み込む。
	//m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);//三種類のアニメーション:m_animationClips=何種類あるか
	m_modelRender.Init("Assets/modelData/player/player.tkm", m_animationClips, enAnimationClip_Num);
	// キャラクターの更新。
	m_modelRender.Update();
	// キャラクターの向きを変える。
	rotation.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(rotation);
	//キャラクターコントローラーを初期化する
	characterController.Init(25.0f, 75.0f, m_position);

	return true;
}

void Player::Update() {
	Move();//キャラクターの移動
	Rotation();//キャラクターの回転
	//Anim();
	//ステート管理。
	ManageState();
	//アニメーションの再生。
	PlayAnimation();
	m_modelRender.Update();//モデル更新
}

void Player::Move() {
	// 乗算用
	float m_dash = 1.0f;
	// もしAボタンが押されたら。
	if (g_pad[0]->IsPress(enButtonA))
	{
		// 移動速度を上げる。
		m_dash *= 2.0f;
	}
	// もしBボタンが押されたら。
	if (g_pad[0]->IsPress(enButtonB))
	{
		m_dash /= 2.0f;
	}

	// xzの移動速度を0.0fにする。
	// 0.0fで初期化することで前回の移動速度の影響を
	// 受けずに新しい入力に基づいた移動が可能。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	//プレイヤーの進行方向を決定する。
	Vector3 stickL;
	//スティックの水平方向。
	stickL.x = g_pad[0]->GetLStickXF();
	//スティックの垂直方向。
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	//プレイヤーがどの方向に移動するかを決める。
	//カメラの前方向のベクトルを取得。
	Vector3 forward = g_camera3D->GetForward();
	//カメラの右方向のベクトルを取得。
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない。
	//こうすることでプレイヤーは地面上でのみ移動する。
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と120.0fを
	// 乗算。
	//移動速度を決める。
	right *= stickL.x * 180.0f * m_dash;
	forward *= stickL.y * 180.0f * m_dash;

	//移動速度にスティックの入力量を加算する。
	// m_run→ダッシュ時用の変数。
	m_moveSpeed += right + forward;

	//地面に付いていたら。
	if (characterController.IsOnGround())
	{
		//重力を無くす。
		m_moveSpeed.y = 0.0f;
		//Aボタンが押されたら。
		//if (g_pad[0]->IsTrigger(enButtonA))
		//{
		//	//ジャンプさせる。
		//	moveSpeed.y = 250.0f;
		//}
	}
	//地面に付いていなかったら。
	else
	{
		//重力を発生させる。
		m_moveSpeed.y -= 5.0f;
	}
	//キャラクターコントローラーを使って座標を移動させる。
	m_position = characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える。
		m_modelRender.SetRotation(rotation);
	}
}

//ステート管理。
void Player::ManageState()
{
	//地面に付いていなかったら。
	if (characterController.IsOnGround() == false)
	{
		//ステートを1(ジャンプ中)にする。
		m_playerState = 1;
		//ここでManageStateの処理を終わらせる。
		return;
	}

	//地面に付いていたら。
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//ステートを2(歩き)にする。
		m_playerState = State_Walk;

		// もしAボタンが押されたら。
		if (g_pad[0]->IsPress(enButtonA))
		{
			// 走る。
			m_playerState = State_Run;
		}
		// もしBボタンが押されたら。
		else if (g_pad[0]->IsPress(enButtonB))
		{
			// しゃがむ。
			m_playerState = State_CrouchWalk;
		}
	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//ステートを0(待機)にする。
		m_playerState = State_Idle;

		// もしBボタンが押されたら。
	    if (g_pad[0]->IsPress(enButtonB))
	    {
		    // しゃがむ。
		    m_playerState = State_Crouch;
	    }
	}
}

//アニメーションの再生。
void Player::PlayAnimation()
{
	//switch文。
	switch (m_playerState) {
		// ステートがIdleだったら。
	case State_Idle:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimClip_Idle);
		break;
		// ステートがWalkだったら。
	case State_Walk:
		//歩きアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimClip_Walk);
		break;
		// ステートがRunだったら。
	case State_Run:
		// 走りアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimClip_Run);
		break;
		// ステートがCrouchだったら。
	case State_Crouch:
		// しゃがみアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimClip_Crouch);
		break;
		// ステートがCrouchWalkだったら。
	case State_CrouchWalk:
		// しゃがみ歩きアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimClip_CrouchWalk);
		break;
		// ステートがCrouchingだったら。
	case State_Crouching:
		// しゃがみこみアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimClip_Crouching);
		break;
		// ステートがCrouchStandingだったら。
	case State_CrouchStanding:
		// 立ち上がりアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimClip_CrouchStanding);
		break;
	}
}

void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}