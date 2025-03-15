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
	m_animationClips[enAnimClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimClip_Jump].SetLoopFlag(false);
	// キャラクターを読み込む。
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);//三種類のアニメーション:m_animationClips=何種類あるか
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
	Anim();
	//ステート管理。
	ManageState();
	//アニメーションの再生。
	PlayAnimation();
	m_modelRender.Update();//モデル更新


}

void Player::Move() {

	// xzの移動速度を0.0fにする。
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と120.0fを
	// 乗算。
	right *= stickL.x * 1000.0f;
	forward *= stickL.y * 1000.0f;


	//移動速度にスティックの入力量を加算する。
	moveSpeed += right + forward;

	//地面に付いていたら。
	if (characterController.IsOnGround())
	{
		//重力を無くす。
		moveSpeed.y = 0.0f;
		//Aボタンが押されたら。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ジャンプさせる。
			moveSpeed.y = 300.0f;
		}
	}
	//地面に付いていなかったら。
	else
	{
		//重力を発生させる。
		moveSpeed.y -= 2.5f;
	}
	//キャラクターコントローラーを使って座標を移動させる。
	m_position = characterController.Execute(moveSpeed, 1.0f / 60.0f);
	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		rotation.SetRotationYFromDirectionXZ(moveSpeed);
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
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//ステートを2(歩き)にする。
		m_playerState = 2;
	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//ステートを0(待機)にする。
		m_playerState = 0;
	}
}

//アニメーションの再生。
void Player::PlayAnimation()
{
	//switch文。
	switch (m_playerState) {
		//プレイヤーステートが0(待機)だったら。
	case 0:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimClip_Idle);
		break;
		//プレイヤーステートが1(ジャンプ中)だったら。
	case 1:
		//ジャンプアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimClip_Jump);
		break;
		//プレイヤーステートが2(歩き)だったら。
	case 2:
		//歩きアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimClip_Run);
		break;
	}
}

void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}
