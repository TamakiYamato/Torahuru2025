// include→このクラス内で他クラスを参照する。
#include "stdafx.h"
#include "Player.h"
#include"Game.h"
#include"FloorManager.h"
#include"ReverseFloor.h"
#include"SlowFloor.h"
#include"BlindFloor.h"
#include"SecondFloor.h"

#include <string>

// 移動速度を上昇させ、デバッグしやすくする。
#define DEBUG
// constを使用して定数を作成する。
// namespace→無名名前空間
// 外部からアクセスされないようにしたい定数や関数を格納する。
namespace
{
	// ファイルパスを定数定義
	// ファイルパスは文字列なので string を使用する。
	// const を使用し定数を定義。 const→変数が変更不可であることを示す。
	// ヒューマンエラーを防ぐ。　ヒューマンエラー→タイピング等のミスで起こるエラー。
	const std::string animationFilePath = "Assets/animData/";
	const std::string animationExtention = ".tka";
}

Player::Player()
{
}

Player::~Player()
{
	// 状態をdelete。
	/*for (int i = 0; i < enPlayerState_Max; ++i) {
		delete m_playerStateList[i];
		m_playerStateList[i] = nullptr;
	}*/
}

// constでファイルを読み取る。
void Player::SetAnimation(EnAnimationClip animationClip, std::string animationFileName, bool loopFlag)
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
	SetAnimation(enAnimClip_Idle, "player/playerIdle", true);
	// 歩きアニメーション。
	SetAnimation(enAnimClip_Walk, "player/playerWalking", true);
	// 走りアニメーション。
	SetAnimation(enAnimClip_Run, "player/playerRunning", true);
	// しゃがみアニメーション。
	SetAnimation(enAnimClip_Crouch, "player/playerCrouch", true);
	// しゃがみ歩きアニメーション。
	SetAnimation(enAnimClip_CrouchWalk, "player/playerCrouched walking", true);
	//倒れ込むアニメーション
	SetAnimation(enAnimClip_Down, "playerDamage/Fire/playerFireDown", true);
	// 起き上がるアニメーション。
	SetAnimation(enAnimClip_GetUp, "playerDamage/Fire/playerFireGetup", true);

	// キャラクターを読み込む。
	m_modelRender = new ModelRender();	//モデル切り替える際にモデルを元に戻すためにnewする。
	m_normalModel.Init("Assets/modelData/player/player.tkm", m_animationClips, enAnimationClip_Num);//m_animationClips=何種類あるか
	m_reverseModel.Init("Assets/modelData/playerDamage/Reverse/playerReverse.tkm", m_animationClips, enAnimationClip_Num);
	m_slowModel.Init("Assets/modelData/playerDamage/Slow/playerSlow.tkm", m_animationClips, enAnimationClip_Num);
	m_fireModel.Init("Assets/modelData/playerDamage/Fire/playerFire.tkm", m_animationClips, enAnimationClip_Num);

	// 現在のモデルを設定
	m_modelRender = &m_normalModel;	//m_modelRenderはポインタ型なので、&をつける。
	/*ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/player/player.tkm";
	modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	modelInitData.m_vsSkinEntryPointFunc = "VSMainSkin";
	modelInitData.m_psEntryPointFunc = "PSMainHardShadow";
	modelInitData.animationClips = m_animationClips;
	modelInitData.numAnimationClips = enAnimationClip_Num;
	m_modelRender->InitForwardRendering(modelInitData);*/
	// キャラクターの更新。
	m_modelRender->Update();
	// キャラクターの向きを変える。
	rotation.SetRotationDegY(180.0f);
	m_modelRender->SetRotation(rotation);
	//キャラクターコントローラーを初期化する
	m_charCon.Init(25.0f, 75.0f, m_position);

	// 状態の生成。
	// 注意：newしたインスタンスはdeleteが必要。
	// 今回はデストラクタでdeleteします。
	m_playerStateList[enPlayerState_Idle] = new PlayerIdleState(this);
	m_playerStateList[enPlayerState_Walk] = new PlayerWalkState(this);
	m_playerStateList[enPlayerState_Run] = new PlayerRunState(this);
	m_playerStateList[enPlayerState_Crouch] = new PlayerCrouchState(this);
	m_playerStateList[enPlayerState_CrouchWalk] = new PlayerCrouchWalkState(this);

	// 初期状態を設定。
	m_currentPlayerState = enPlayerState_Idle;
	m_requestPlayerState = enPlayerState_None;

	return true;
}

void Player::Update() {

	if (m_floorManager == nullptr)
	{
		m_floorManager = FindGO<FloorManager>("floorManager");
	}

#if 1
	if (m_requestPlayerState != enPlayerState_None) {
		if (m_currentPlayerState != m_requestPlayerState) {
			// 現在の状態を終了する。
			m_playerStateList[m_currentPlayerState]->Exit();
			// 現在の状態を次の状態に切り替える。
			m_currentPlayerState = m_requestPlayerState;
			// 切り替えた状態を開始。
			m_playerStateList[m_currentPlayerState]->Enter();
		}
	}
	// ステート処理が上手く実行されてない場合、お知らせしてくれる。
	K2_ASSERT(m_currentPlayerState != enPlayerState_None, "状態が正しく設定されていません。");
	m_playerStateList[m_currentPlayerState]->Update();
#endif
	FireState();			//火炎放射器に当たった時のモデル更新。
	AddFireEffect();	//火炎放射器に当たった時のモデル更新。
	UpdateModelByState();	//ステートによってモデルのアップデートを変更
	Rotation();				//キャラクターの回転
	StaminaCalc();
	m_modelRender->SetPosition(m_position);
	m_modelRender->Update();	//モデル更新。
	//m_reverseModel.Update();//暗転床踏んだ時のモデル更新。
	//m_slowModel.Update();	//減速床を踏んだ時のモデル更新。
}

void Player::Move(float m_move = 1.0f)
{
	// xzの移動速度を0.0fにする。
	// 0.0fで初期化することで前回の移動速度の影響を
	// 受けずに新しい入力に基づいた移動が可能。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
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

	//左スティックの入力量と180.0fを
	// 乗算。
	//移動速度を決める。
#if 1
	right *= stickL.x * 180.0f * m_move * m_moveDir;
	forward *= stickL.y * 180.0f * m_move * m_moveDir;
#endif

#if debug
	right *= stickL.x * 500.0f * m_move * m_moveDir;
	forward *= stickL.y * 500.0f * m_move * m_moveDir;
#endif

	//移動速度にスティックの入力量を加算する。
	// m_run→ダッシュ時用の変数。
	m_moveSpeed += right + forward;

	//地面に付いていたら。
	if (m_charCon.IsOnGround())
	{
		//重力を無くす。
		m_moveSpeed.y = 0.0f;
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ジャンプさせる。
			return;
		}
	}
	//地面に付いていなかったら。
	else
	{
		//重力を発生させる。
		m_moveSpeed.y -= 10.0f;
	}

	//キャラクターコントローラーを使って座標を移動させる。
	m_moveSpeed += m_addForce;
	m_position = m_charCon.Execute(m_moveSpeed, 1.0f / 60.0f);
	//絵描きさんに座標を教える。
	m_modelRender->SetPosition(m_position);
	m_addForce = Vector3::Zero;	//移動後に加えた力をリセットする。
}

void Player::SetGravity()
{
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
		m_moveSpeed.y -= 10.0f;
	}
	//キャラクターコントローラーを使って座標を移動させる。
	m_position = m_charCon.Execute(m_moveSpeed, 1.0f / 60.0f);
	//絵描きさんに座標を教える。
	m_modelRender->SetPosition(m_position);
}

//void Player::SetPosition(const Vector3& position) {
//	m_position = position;
//	m_charCon.SetPosition(m_position);
//	m_modelRender->SetPosition(m_position);
//	m_modelRender->Update();	//モデル更新。
//}

void Player::Rotation()
{
	// NOTE: 早期リターンとは？→条件が満たされない場合に、早期に関数から抜け出す手法。
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}
	//キャラクターの方向を変える。
	rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	//絵描きさんに回転を教える。
	m_modelRender->SetRotation(rotation);
}


void Player::DashStaminaCalk()
{
	// スタミナを減らす。
		//g_gameTime->GetFrameDeltaTime(); → フレームレートに関係なく一定のスピードで処理を進められる。
		// 60FPSが1フレームにかかる時間 → 1秒 ÷ 60 = 約0.06秒。
		// これを好きな数で乗算→FPSに左右されずに減らせる。
	m_stamina -= 20.0f * g_gameTime->GetFrameDeltaTime();// 1秒で減る。
	// スタミナが0以下になったら。
	if (m_stamina <= 0)
	{
		// スタミナを0にする。
		m_stamina = 0;
	}
}

void Player::FireState()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("fireCollision");


	for (CollisionObject* collision : collisions) {
		if (collision->IsHit(m_charCon) == true) {
			// プレイヤーが火炎放射器に当たったら。
			m_isHitFireCollision = true;
			return;
		}
		// プレイヤーが火炎放射器に当たっていない時。
		else{
			m_isHitFireCollision = false;	//火炎放射器に当たっていない時、フラグをfalseにする。
		}
	}
}

void Player::AddFireEffect()
{
	if(m_isHitFireCollision == true)
	{
		m_modelRender = &m_fireModel;				//火炎放射器に当たった時のモデルに切り替える。
		//m_moveDir = 0.0f;
	}
	else
	{
		m_modelRender = &m_normalModel;				//火炎放射器に当たっていない時、通常モデルに戻す。
		m_floorManager->m_playerFloorState = m_floorManager->Normal;	//プレイヤーの床の状態を通常に戻す。
		//m_moveDir = 1.0f;							//移動方向を元に戻す。
	}
}

void Player::StaminaCalc()
{
	// プレイヤーがダッシュしてたら。
	if (m_currentPlayerState == State_Run)
	{
		DashStaminaCalk();
	}
	// 走っていないとき。
	else if (m_dashFlag != true)
	{
		// スタミナを回復する。
		m_stamina += 20.0f * g_gameTime->GetFrameDeltaTime();
		// スタミナが100以上になったら。
		if (m_stamina >= 100)
		{
			//スタミナを100にする。
			m_stamina = m_max_stamina;
		}
		// Aボタンが押されたら。→押し続けている間、スタミナを回復しない。
		else if (g_pad[0]->IsPress(enButtonA))
		{
			DashStaminaCalk();
		}
	}
}

void Player::Render(RenderContext& rc) {
	if (m_modelRender) {
		m_modelRender->Draw(rc);
	}
}

void Player::UpdateModelByState()
{
	//ギミックの床を踏んだ時フラグがtrueになる。
	if (m_requestChangeModel == true)
	{
		// 踏んだ床によってモデルを変える
		switch (m_floorManager->m_floorState)
		{
			case m_floorManager->Normal:	//通常床を踏んだ時
			m_modelRender = &m_normalModel;	//通常モデルに切り替える
			break;
		case m_floorManager->ReverseState:	//操作反転床を踏んだ時
			m_modelRender = &m_reverseModel;	//反転モデルに切り替える
			break;
		case m_floorManager->SlowState:		//減速床を踏んだ時
			m_modelRender = &m_slowModel;		//減速モデルに切り替える
			break;
		}
		
	}

	m_requestChangeModel = false;	//プレイヤーが床を踏んでいない状態にする

}

void Player::SetPosition(const Vector3& position) {
	m_position = position;
	m_charCon.SetPosition(m_position);
	m_modelRender->SetPosition(m_position);
	m_modelRender->Update();	//モデル更新。
 }

//void Player::Render(RenderContext& rc) {
//		m_modelRender->Draw(rc);
//	////ギミックの床を踏んだ時
//	//if (m_floorManager != nullptr)
//	//{
//	//	// 踏んだ床によってモデルを変える
//	//	switch (m_floorManager->m_floorState) {
//	//	case m_floorManager->ReverseState:	//操作反転床を踏んだ時
//	//		m_reverseModel.Draw(rc);
//	//		break;
//	//	case m_floorManager->SlowState:		//減速床を踏んだ時
//	//		m_slowModel.Draw(rc);
//	//		break;
//	//	}
//	//}
//}

