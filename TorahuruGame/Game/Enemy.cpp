#include "stdafx.h"
#include "Enemy.h"
#include "EnemyAnimation.h"
#include "Game.h"
#include "Player.h"
using namespace std;

namespace {

	const float SEARCH_LENGTH = 500.0f;	//プレイヤーを発見する距離。

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

	//キャラコンの初期化
	m_charCon.Init(
		40.0f,
		40.0f,
		m_position
	);

	//見つける
	m_player = FindGO<Player>("player");
}

void Enemy::Update()
{
	SearchPlayer();		//常にプレイヤーを探す
	PlayAnimation();	//プレイヤーのアニメーション
	m_modelRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

}

/// <summary>
/// 移動速度を消し、その場でplayerが来るのを待つ
/// </summary>
void Enemy::Stand()
{

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
		//エネミーからプレイヤーに向かうベクトルを正規化する
		diff.Normalize();
		//エネミーの正面のベクトルと、エネミーからプレイヤーに向かう
		//ベクトルの内積(cosθ)を求める
		float cos = m_forward.Dot(diff);
		//内積(cosθ)から角度(θ)を求める
		float angle = acosf(cos);
		//角度(θ)が180°より小さければ
		if (angle <= Math::DegToRad(120.0f))
		{
			//プレイヤーを見つけた場合、追跡開始
			m_enemyState = enEnemyState_Chase;
		}
		else if (m_firstPosition.x == m_position.x &&
				 m_firstPosition.y == m_position.y &&
				 m_firstPosition.z == m_position.z   ) {	//エネミーの位置が最初期の場合は待機
			m_enemyState == enEnemyState_Idle;
		}
		else {
			//プレイヤーを見つけられなかった
			m_enemyState = enEnemyState_Walk;
		}
	}
}

/// <summary>
/// 移動
/// </summary>
void Enemy::Move()
{
	
}

/// <summary>
/// プレイヤーを追跡
/// </summary>
void Enemy::Chase()
{
	
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
