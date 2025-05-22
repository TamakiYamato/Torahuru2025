#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#include "stdafx.h"
#include "Enemy.h"
#include "EnemyAnimation.h"
#include "Game.h"
#include "Player.h"
#include "FloorManager.h"
using namespace std;

namespace {

	const float SEARCH_LENGTH = 500.0f;			//プレイヤーを発見する距離。
	const float ENEMY_ATTACKRANGE = 150.0f;		//enemyの攻撃範囲、入ると即死。
	const float COMPLATION_RATIO = 1.0f;		//補完率。
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}


bool Enemy::Start()
{
	// キャラクターを読み込む。
	m_modelRender.Init("Assets/modelData/enemy/enemy.tkm", m_enemyAnim->m_enemyAnim, m_enemyAnim->enAnimationClip_Num);//m_enemyAnim=何種類あるか
	return true;

	//初期設定
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_initialPosition = m_position;		//座標の保存。
	m_initialRotation = m_rotation;		//角度の保存。

	//キャラコンの初期化
	m_charCon.Init(
		40.0f,
		40.0f,
		m_position
	);

	//見つける
	m_player = FindGO<Player>("player");
	m_floorManager = FindGO<FloorManager>("floorManager");
	m_enemyAnim = FindGO<EnemyAnimation>("enemyAnimation");
}

void Enemy::Update()
{
	if (m_enemyState != enEnemyState_Walk) {
		m_charCon.SetPosition(m_position);	//元の場所に帰っている場合、キャラコンをenemyと同じ場所へ
	}

	if (m_floorManager->m_enemyFloorTimer == 5.0f) {	//床の効果を受けていない場合
		SearchPlayer();		//常にプレイヤーを探す。
		ManageState();		//ステートを常に管理、行動。
	}
	PlayAnimation();	//プレイヤーのアニメーション。
	m_modelRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

}

/// <summary>
/// プレイヤを探す。
/// </summary>
void Enemy::SearchPlayer()
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
		//角度(θ)が120°より小さければ
		if (angle <= Math::DegToRad(150.0f))
		{
			//プレイヤーを見つけた場合、追跡開始
			m_enemyState = enEnemyState_Chase;
		}

		else if ((m_position.Length() - m_initialPosition.Length()) <= 0.1f &&					//エネミーの現在の座標とスポーン地点の座標との差が0.1かつ
				(GetAngleBetweenQuaternions(m_initialRotation,m_currentRotation)) <= 1.0f) {	//エネミーの現在の角度とスポーン地点の角度の差が0.5の場合
							
			m_enemyState == enEnemyState_Idle;	//待機
		}

		else {
			//プレイヤーを見つけられなかった
			m_enemyState = enEnemyState_Walk;
		}
	}
}

/// <summary>
/// 移動速度を消し、その場でplayerが来るのを待つ
/// </summary>
void Enemy::Stand()
{
	m_moveSpeed = Vector3::Zero;

}

/// <summary>
/// 最初の位置に戻る。
/// </summary>
void Enemy::Move()
{
	m_moveSpeed = Vector3(100.0f, 0.0f, 100.0f);
	m_moveSpeed *= m_moveDir;	//床の効果を与える
	m_charCon.SetPosition(m_initialPosition);		//enemyの戻る場所の設定
	m_position	= m_charCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());	//元の場所に戻る
	m_rotation.Slerp(COMPLATION_RATIO, m_currentRotation, m_initialRotation);		//元の角度に向く
}

/// <summary>
/// プレイヤーを追跡。
/// </summary>
void Enemy::Chase()
{
	m_moveSpeed = Vector3(200.0f, 0.0f, 200.0f);
	m_moveSpeed *= m_moveDir;	//床の効果を与える
	m_position = m_charCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
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
		Move();		//元の位置に戻る。
		break;

	case enEnemyState_Chase:
		Chase();	//追跡。
		break;
	}
}

/// <summary>
/// アニメーションの管理
/// </summary>
void Enemy::PlayAnimation()
{
	switch (m_enemyState) {
	case enEnemyState_Idle:		//待機
		m_modelRender.PlayAnimation(m_enemyAnim->enAnimationClip_Idle);
		break;

	case enEnemyState_Walk:		//監視
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
	if (diff.Length() >= 200.0f) {
		m_enemyState = enEnemyState_Attack;
	}
}

/// <summary>
/// 2つのクォータニオン間の角度差（度）を求める
/// </summary>
float Enemy::GetAngleBetweenQuaternions(const Quaternion& q1, const Quaternion& q2)
{
	// クォータニオンの内積を計算
	float dot = q1.Dot(q2);

	// acosの安全な範囲にクランプ
	dot = Clamp(dot, -1.0f, 1.0f);

	// クォータニオンの角度差は acos(dot) * 2
	float angleRad = std::acos(dot) * 2.0f;

	// ラジアン　→ 度に変換
	return Math::RadToDeg(angleRad);
}
