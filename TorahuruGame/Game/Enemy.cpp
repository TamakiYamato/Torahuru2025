#include "stdafx.h"
#include "Enemy.h"
#include "EnemyAnimation.h"
#include "Game.h"
#include "Player.h"
#include "FloorManager.h"
#include"SecondFloor.h"
using namespace std;

namespace {

	const float SEARCH_LENGTH = 700.0f;			//プレイヤーを発見する距離。
	const float ENEMY_ATTACKRANGE = 100.0f;		//enemyの攻撃範囲、入ると即死。
	const float COMPLATION_RATIO = 1.0f;		//補完率。
}

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	DeleteGO(m_enemyAnim); //エネミーアニメーションの削除
}


bool Enemy::Start()
{
	m_enemyAnim = NewGO<EnemyAnimation>(0, "enemyAnimation");

	// キャラクターを読み込む。
    m_modelRender.Init("Assets/modelData/enemy/enemy.tkm", m_enemyAnim->m_enemyAnimationClips, m_enemyAnim->enAnimationClip_Num);//m_enemyAnim=何種類あるか
	
	//初期設定
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_initialPosition = m_position;	//座標の保存。
	m_initialRotation = m_currentRotation; //角度の保存。

	//キャラコンの初期化
	m_charCon.Init(
		40.0f,
		40.0f,
		m_position
	);

	//見つける
	m_player = FindGO<Player>("player");
	m_floorManager = FindGO<FloorManager>("floorManager");
	m_secondfloor = FindGO<SecondFloor>("secondfloor");


	return true;
}

void Enemy::Update()
{
	// キャラクターコントローラーの位置を更新
	if (m_enemyState != enEnemyState_Idle) {
		m_charCon.SetPosition(m_position);
	}
	SetGravity(); //重力を設定、キャラクターコントローラーを使って座標を移動させる。
	CommonStateTransitionProcess(); //ステートの遷移を管理。
	ManageState(); //ステートを常に管理、行動。
	Rotation(); //移動方向に基づいて回転を計算。
	PlayAnimation(m_enemyState); //アニメーションの更新
	m_modelRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

}


void Enemy::SetGravity()
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
	m_modelRender.SetPosition(m_position);
}

void Enemy::CommonStateTransitionProcess()
{
	if (m_enemyState == enEnemyState_Attack) return;

	Vector3 toInitialPos = m_initialPosition - m_position;
	Vector3 diff = m_player->GetPosition() - m_position;

	if (SearchPlayer()) {
		diff.Normalize();
		m_moveSpeed = diff * 150.0f;
		m_enemyState = enEnemyState_Chase;
		return;
	}

	// Idle状態で3秒経過したらWalkに遷移
	if (m_enemyState == enEnemyState_Idle && m_idleTimer >= 3.0f && toInitialPos.Length() > 150.0f) {
		toInitialPos.Normalize();
		m_moveSpeed = toInitialPos * 100.0f;
		m_savedMoveSpeed = m_moveSpeed;
		m_enemyState = enEnemyState_Walk;
		m_idleTimer = 0.0f;
		m_isReadyIdle = false;
		return;
	}

	// Walkが終わったらIdleに戻す
	if (m_enemyState == enEnemyState_Walk && toInitialPos.Length() < 100.0f) {
		m_enemyState = enEnemyState_Idle;
		m_isReadyIdle = true;
		return;
	}

	// プレイヤーが見つからず、IdleやWalkでない場合はIdleに遷移
	if (m_enemyState != enEnemyState_Idle && m_enemyState != enEnemyState_Walk) {
		m_enemyState = enEnemyState_Idle;
		m_isReadyIdle = true;
	}
}
/// <summary>
/// プレイヤを探す。
/// </summary>
bool Enemy::SearchPlayer()
{
	Vector3 diff = m_player->GetPosition() - m_position;

	//プレイヤーにある程度近かったら
	if (diff.LengthSq() <= SEARCH_LENGTH * SEARCH_LENGTH)
	{
		//エネミーからプレイヤーに向かうベクトルを正規化
		diff.Normalize();

		//エネミーの正面のベクトルと、エネミーからプレイヤーに向かう
		//ベクトルの内積(cosθ)を求める
		float cos = m_forward.Dot(diff);
		//内積(cosθ)から角度(θ)を求める
		float angle = acosf(cos);
		//角度(θ)が180°より小さければ
		if (angle <= (Math::PI / 180.0f) * 120.0f){
			return true; //プレイヤーを見つけた
		}
		else {
			return false(); //プレイヤーを見つけられなかった
		}
	}
	return false;

}

/// <summary>
/// 移動速度を消し、その場でplayerが来るのを待つ
/// </summary>
void Enemy::Stand()
{
	m_moveSpeed = Vector3::Zero;
	m_position = m_charCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//if(m_idleTimer >= 3.0f) {
	//	// 3秒経過したら元の位置に戻る
	//	m_isReadyIdle = false; //Idle状態にならないようにする
	//	m_idleTimer = 0.0f; //タイマーをリセット
	//}
}

/// <summary>
/// 最初の位置に戻る。
/// </summary>
void Enemy::ReturnToSpawn()
{	
	Vector3 toInitialPos = m_initialPosition - m_position;

	// 初期位置への方向を正規化
	toInitialPos.Normalize();

	// 移動を実行
	m_position = m_charCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	// 移動方向に基づいて回転を計算
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	m_currentRotation.SetRotationY(-angle);
	
	m_modelRender.SetRotation(m_currentRotation);
	
	// 前方ベクトルの更新
	m_forward = Vector3::AxisZ;
	m_currentRotation.Apply(m_forward);

	if(toInitialPos.Length() < 100.0f) {
		// 初期位置に到着したら移動を停止
		m_isReadyIdle = true;
	}
}

/// <summary>
/// プレイヤーを追跡。
/// </summary>
void Enemy::Chase()
{
	m_position = m_charCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	// 大きな動きがあるかチェックする。
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
		return;// 動きが小さい場合は何もしない
	}

	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//追跡時間がある程度経過したら
	if (m_chaseTimer >= 0.8f)
	{
		// プレイヤーが近くにいる場合は攻撃状態に移行
		CheckPlayerProximityAndDie();
		m_chaseTimer = 0.0f; //初期化
	}
}

void Enemy::Rotation()
{
	// 移動方向に基づいて回転を計算
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	m_currentRotation.SetRotationY(-angle);

	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
	m_modelRender.SetRotation(m_currentRotation);

	// 前方ベクトルの更新
	m_forward = Vector3::AxisZ;
	m_currentRotation.Apply(m_forward);
}

/// <summary>
/// ステート管理。
/// </summary>
void Enemy::ManageState()
{
	switch (m_enemyState) {
	case enEnemyState_Idle:
		Stand();	//firstPositionでplayerが来るのを待つ。
		break;

	case enEnemyState_Walk:
		ReturnToSpawn();		//元の位置に戻る。
		break;

	case enEnemyState_Chase:
		Chase();	//追跡。
		break;
	}
}

/// <summary>
/// アニメーションの管理
/// </summary>
void Enemy::PlayAnimation(int m_enemyState)
{
	switch (m_enemyState) {
	case enEnemyState_Idle:		//待機
		m_modelRender.PlayAnimation(m_enemyAnim->enAnimationClip_Idle);
		break;

	case enEnemyState_Walk:		//歩く
		m_modelRender.PlayAnimation(m_enemyAnim->enAnimationClip_Walk);
		break;

	case enEnemyState_Chase:	//走る
		m_modelRender.PlayAnimation(m_enemyAnim->enAnimationClip_Run);
		break;

	default:
		break;
	}
}

/// <summary>
/// プレイヤーがエネミーに一定距離近づいたら即死ステートに変更
/// </summary>
void Enemy::CheckPlayerProximityAndDie()
{
	Vector3 diff = m_player->GetPosition() - m_position;
	float distance = diff.Length();  // 正規化する前に実際の距離を計算
	if (distance <= ENEMY_ATTACKRANGE) {  // 定義済みの攻撃範囲を使用

		m_enemyState = enEnemyState_Attack;
	}
}
