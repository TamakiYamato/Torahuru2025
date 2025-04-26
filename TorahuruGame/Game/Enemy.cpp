#include "stdafx.h"
#include "Enemy.h"
#include "EnemyAnimation.h"
#include "Game.h"
#include "Player.h"
using namespace std;

namespace {

	const float SEARCH_LENGTH = 500.0f;	//繝励Ξ繧､繝､繝ｼ繧堤匱隕九☆繧玖ｷ晞屬縲・

}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}


bool Enemy::Start()
{
	// 繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ繧定ｪｭ縺ｿ霎ｼ繧縲・
	m_modelRender.Init("Assets/modelData/enemy/enemy.tkm", m_enemyAnim->m_enemyAnim, m_enemyAnim->enAnimationClip_Num);//m_enemyAnim=菴慕ｨｮ鬘槭≠繧九°
	return true;

	//蛻晄悄險ｭ螳・
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);

	//繧ｭ繝｣繝ｩ繧ｳ繝ｳ縺ｮ蛻晄悄蛹・
	m_charCon.Init(
		40.0f,
		40.0f,
		m_position
	);

	//隕九▽縺代ｋ
	m_player = FindGO<Player>("player");
}

void Enemy::Update()
{
	SearchPlayer();		//蟶ｸ縺ｫ繝励Ξ繧､繝､繝ｼ繧呈爾縺・
	PlayAnimation();	//繝励Ξ繧､繝､繝ｼ縺ｮ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ
	m_modelRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

}

/// <summary>
/// 遘ｻ蜍暮溷ｺｦ繧呈ｶ医＠縲√◎縺ｮ蝣ｴ縺ｧplayer縺梧擂繧九・繧貞ｾ・▽
/// </summary>
void Enemy::Stand()
{

}

/// <summary>
/// 繝励Ξ繧､繝､繧呈爾縺吶・
/// </summary>
void Enemy::SearchPlayer()
{
	Vector3 diff = m_player->GetPosition() - m_position;

	//繝励Ξ繧､繝､繝ｼ縺ｫ縺ゅｋ遞句ｺｦ霑代°縺｣縺溘ｉ
	if (diff.LengthSq() <= SEARCH_LENGTH * SEARCH_LENGTH)
	{
		//繧ｨ繝阪Α繝ｼ縺九ｉ繝励Ξ繧､繝､繝ｼ縺ｫ蜷代°縺・・繧ｯ繝医Ν繧呈ｭ｣隕丞喧縺吶ｋ
		diff.Normalize();
		//繧ｨ繝阪Α繝ｼ縺ｮ豁｣髱｢縺ｮ繝吶け繝医Ν縺ｨ縲√お繝阪Α繝ｼ縺九ｉ繝励Ξ繧､繝､繝ｼ縺ｫ蜷代°縺・
		//繝吶け繝医Ν縺ｮ蜀・ｩ・cosﾎｸ)繧呈ｱゅａ繧・
		float cos = m_forward.Dot(diff);
		//蜀・ｩ・cosﾎｸ)縺九ｉ隗貞ｺｦ(ﾎｸ)繧呈ｱゅａ繧・
		float angle = acosf(cos);
		//隗貞ｺｦ(ﾎｸ)縺・80ﾂｰ繧医ｊ蟆上＆縺代ｌ縺ｰ
		if (angle <= Math::DegToRad(120.0f))
		{
			//繝励Ξ繧､繝､繝ｼ繧定ｦ九▽縺代◆蝣ｴ蜷医∬ｿｽ霍｡髢句ｧ・
			m_enemyState = enEnemyState_Chase;
		}
		else if (m_firstPosition.x == m_position.x &&
				 m_firstPosition.y == m_position.y &&
				 m_firstPosition.z == m_position.z   ) {	//繧ｨ繝阪Α繝ｼ縺ｮ菴咲ｽｮ縺梧怙蛻晄悄縺ｮ蝣ｴ蜷医・蠕・ｩ・
			m_enemyState == enEnemyState_Idle;
		}
		else {
			//繝励Ξ繧､繝､繝ｼ繧定ｦ九▽縺代ｉ繧後↑縺九▲縺・
			m_enemyState = enEnemyState_Walk;
		}
	}
}

/// <summary>
/// 遘ｻ蜍・
/// </summary>
void Enemy::Move()
{
	
}

/// <summary>
/// 繝励Ξ繧､繝､繝ｼ繧定ｿｽ霍｡
/// </summary>
void Enemy::Chase()
{
	
}

/// <summary>
/// 繧ｹ繝・・繝育ｮ｡逅・・
/// </summary>
void Enemy::ManageState()
{
	switch (m_enemyState) {
	case enEnemyState_Idle:
		Stand();	//firstPosition縺ｧplayer縺梧擂繧九・繧貞ｾ・▽縲・
		break;

	case enEnemyState_Walk:
		Move();		//蜈・・菴咲ｽｮ縺ｫ謌ｻ繧九・
		break;

	case enEnemyState_Chase:
		Chase();	//霑ｽ霍｡縲・
		break;
	}
}

/// <summary>
/// 繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ邂｡逅・
/// </summary>
void Enemy::PlayAnimation()
{
	switch (m_enemyState) {
	case enEnemyState_Idle:		//蠕・ｩ・
		m_modelRender.PlayAnimation(m_enemyAnim->enAnimationClip_Idle);
		break;

	case enEnemyState_Walk:		//逶｣隕・
		m_modelRender.PlayAnimation(m_enemyAnim->enAnimationClip_Walk);
		break;

	case enEnemyState_Chase:	//襍ｰ繧・
		m_modelRender.PlayAnimation(m_enemyAnim->enAnimationClip_Run);
		break;

	default:
		break;
	}
}
