#include "stdafx.h"
#include "FireGimmic.h"

#include "Game.h"
#include "Player.h"
#include "collision/CollisionObject.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundSource.h"
#include "sound/SoundEngine.h"

namespace {
	Vector3 COLLISION_SIZE = Vector3(20.0f, 150.0f, 20.0f);
	Vector3 COLLISION_POSITION = Vector3(0.0f, 0.0f, 100.0f);

	const float LENGTH = 500.0f;			//効果音を再生する距離
	const float SE_VOLUME = 0.7f;
}

FireGimmic::FireGimmic()
{
}

FireGimmic::~FireGimmic()
{
	DeleteGO(m_fire);
	DeleteGO(m_se);
}

bool FireGimmic::Start()
{
	m_modelRender.Init("Assets/modelData/background/fire_gimmic.tkm");
	m_modelRender.Update();

	EffectEngine::GetInstance()->ResistEffect(1,
		u"Assets/effect/FireGimmic.efkefc");

	//g_soundEngine->ResistWaveFileBank(13, "Assets/sound/fire_sound_fukidasu.wav");

	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	m_firstPosition = m_position;

	m_fire = NewGO<EffectEmitter>(0);
	m_fire->Init(1);
	m_fire->SetScale(Vector3::One * 30.0f);
	m_fire->SetIsOutDelete(false);

	/*m_se = NewGO<SoundSource>(0);
	m_se->Init(13);
	m_se->SetVolume(SE_VOLUME);*/

	return true;
}

void FireGimmic::Update()
{
	Move();
	PlayEffect();
	Collision();
	PlaySE();
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

}

void FireGimmic::Move()
{
	if (m_moveFlag == false)
	{
		return;
	}

	Vector3 moveSpeed = Vector3::Zero;

	if (m_MovingFloorState == enMovingState_MovingRight)
	{
		if (m_firstPosition.z - m_limit >= m_position.z)
		{
			m_MovingFloorState = enMovingState_MovingLeft;
		}
	}
	else if (m_MovingFloorState == enMovingState_MovingLeft)
	{
		if (m_firstPosition.z + m_limit <= m_position.z)
		{
			m_MovingFloorState = enMovingState_MovingRight;
		}
	}

	if (m_MovingFloorState == enMovingState_MovingRight)
	{
		moveSpeed.z = -m_speed;
	}
	else if (m_MovingFloorState == enMovingState_MovingLeft)
	{
		moveSpeed.z = m_speed;
	}

	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();

	//エフェクト再生中も移動させるため
	m_fire->SetPosition(m_position);
}

void FireGimmic::PlayEffect()
{
	if (m_player->isPlayerDead())
	{
		if (m_fire->IsPlay())
		{
			m_fire->Stop();
		}
		return;
	}

	m_effectIntervalTimer += g_gameTime->GetFrameDeltaTime();
	if (m_effectIntervalTimer <= m_effectInterval)
	{
		return;
	}

	m_fire->SetPosition(m_position);
	m_fire->Play();

	m_effectIntervalTimer = 0.0f;
}

void FireGimmic::Collision()
{
	if (m_fire->IsPlay() == true)
	{
		auto collisionObject = NewGO<CollisionObject>(0, "collisionObject");
		collisionObject->CreateBox(
			m_position + COLLISION_POSITION,
			Quaternion::Identity,
			COLLISION_SIZE
		);
		collisionObject->SetPosition(m_position + COLLISION_POSITION);
		collisionObject->SetName("fire_gimmic");
	}
}

void FireGimmic::PlaySE()
{
	if (m_player->isPlayerDead())
	{
		m_se->Stop();
		return;
	}

	Vector3 dir = m_player->GetPosition() - m_position;
	float length = dir.Length();

	//プレイヤーとの距離がLENGTH以下なら
	if (length <= LENGTH)
	{
		//エフェクトが再生中ではないなら
		if (!m_fire->IsPlay())
		{
			//再生中の時
			if (m_se->IsPlaying())
			{
				//停止
				m_se->Stop();
			}
			return;
		}
		//再生する
		m_se->Play(true);
	}
	else if (m_se->IsPlaying())
	{
		m_se->Stop();
	}
}

void FireGimmic::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}