// include→このクラス内で他クラスを参照する。
#include "stdafx.h"
#include "Player.h"
#include"Game.h"
#include"ReverseFloor.h"
#include"SlowFloor.h"
#include"BlindFloor.h"
#include <string>

// constを使用して定数を作成する。
// namespace→無名名前空間
// 外部からアクセスされないようにしたい定数や関数を格納する。
namespace
{
	// ファイルパスを定数定義
	//char string;

	// ファイルパスは文字列なので string を使用する。
	// const を使用し定数を定義。 const→変数が変更不可であることを示す。
	// ヒューマンエラーを防ぐ。　ヒューマンエラー→タイピング等のミスで起こるエラー。
	const std::string animationFilePath = "Assets/animData/player/";
	const int PLAYER_STICK_REVERSE = -1;	//プレイヤーの進行方向を入力した方向の逆にする

	const std::string animationExtention = ".tka";
}

Player::Player()
{
}

Player::~Player()
{
}

// constでファイルを読み取る。
void Player::SetAnimation(EnAnimationClip animationClip , std::string animationFileName, bool loopFlag)
{
	// 共通化したファイル名。
	std::string FileName = animationFilePath + animationFileName + animationExtention;
	//std::strinstr();
	// c_str()メゾットを呼び出すことで const char* に変換される。
	m_animationClips[animationClip].Load(FileName.c_str());
	m_animationClips[animationClip].SetLoopFlag(loopFlag);
}

// bool→ trueとfalseを判別する。(この2種類の値しか取れない。)
bool Player::Start()
{
	// 待機アニメーション。
	SetAnimation(enAnimClip_Idle, "playerIdle", true);
	// 歩きアニメーション。
	SetAnimation(enAnimClip_Walk, "playerWalking", true);
	// 走りアニメーション。
	SetAnimation(enAnimClip_Run, "playerRunning", true);
	// しゃがみアニメーション。
	SetAnimation(enAnimClip_Crouch, "playerCrouch", true);
	// しゃがみ歩きアニメーション。
	SetAnimation(enAnimClip_CrouchWalk, "playerCrouched walking", true);

	// キャラクターを読み込む。
	m_modelRender.Init("Assets/modelData/player/player.tkm", m_animationClips, enAnimationClip_Num);//m_animationClips=何種類あるか
	// キャラクターの更新。
	m_modelRender.Update();
	// キャラクターの向きを変える。
	rotation.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(rotation);
	//キャラクターコントローラーを初期化する
	m_charCon.Init(25.0f, 75.0f, m_position);

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
		m_dash *= 0.5f;
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
	if (m_charCon.IsOnGround())
	{
		//重力を無くす。
		m_moveSpeed.y = 0.0f;
	}
	//地面に付いていなかったら。
	else
	{
		//重力を発生させる。
		m_moveSpeed.y -= 5.0f;
	}

	////////特殊床プログラム/////////////////////////////////////////
	
	//ステージ内にあるreversefloorをすべて見つける。
	const auto& reverseFloors = FindGOs<SlowFloor>("reverseFloor");
	
	//forはすべてのreversefloorを繰り返す
	for (auto revereseFloor : reverseFloors) {
		//プレイヤーが床の上にいたとき、操作を逆にする。
		if (revereseFloor->m_onSlowFloor == true) {
			stickL.x *= PLAYER_STICK_REVERSE;
			stickL.y *= PLAYER_STICK_REVERSE;
		}
	}
	//ステージ内にあるslowfloorをすべて見つける。
	const auto& slowFloors = FindGOs<SlowFloor>("slowFloor");

	//forはすべてのslowfloorを繰り返す
	for (auto slowFloor : slowFloors) {
		//プレイヤーが床の上にいたとき、スピードが半分になる
		if (slowFloor->m_onSlowFloor == true) {
			m_dash *= 0.5f;
		}
	}

	//ステージ内にあるblindfloorをすべて見つける。
	const auto& blindFloors = FindGOs<BlindFloor>("blindFloor");

	//forはすべてのblindfloorを繰り返す
	for (auto blindFloor : blindFloors) {
		//プレイヤーが床の上にいたとき、視界を制限する。
		if (blindFloor->m_onBlindFloor == true) {
			
		}
	}
	//キャラクターコントローラーを使って座標を移動させる。
	m_position = m_charCon.Execute(m_moveSpeed, 1.0f / 60.0f);
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
	////地面に付いていなかったら。
	//if (m_charCon.IsOnGround() == false)
	//{
	//	//ステートを1(ジャンプ中)にする。
	//	m_playerState = 1;
	//	//ここでManageStateの処理を終わらせる。
	//	return;
	//}

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