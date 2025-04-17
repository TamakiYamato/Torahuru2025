#include "stdafx.h"
#include "FireGimmic.h"

#include "Game.h"
#include "Player.h"
#include "collision/CollisionObject.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundSource.h"
#include "sound/SoundEngine.h"

namespace {
	Vector3 FIRE_COLLISION_SIZE = Vector3(20.0f, 150.0f, 20.0f);
	Vector3 FIRE_COLLISION_POSITION = Vector3(100.0f, 0.0f, 100.0f);

	Vector3 FIRE_POS = Vector3(800.0f, 200.0f, -900.0f);
	Quaternion FIRE_ROT = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
	Vector3 FIRE_SCALE = Vector3(10.0f, 10.0f, 10.0f);

	const float LENGTH = 1500.0f;			//効果音を再生する距離
	const float SE_VOLUME = 0.3f;

}

FireGimmic::FireGimmic()
{
}

FireGimmic::~FireGimmic()
{
	if (m_se != nullptr) {
		DeleteGO(m_se);
	}
	if (m_fire != nullptr) {
		DeleteGO(m_fire);
	}

	DeleteGO(m_fireCollision_North);
	DeleteGO(m_fireCollision_South);
	DeleteGO(m_fireCollision_East);
	DeleteGO(m_fireCollision_West);
}

bool FireGimmic::Start()
{
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fire.efk");

	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/fire.wav");

	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	m_firstPosition = m_position;

	//コリジョンオブジェクトの初期化
	//4種類つくって

	m_fireCollision_North = NewGO<CollisionObject>(0);
	m_fireCollision_North->CreateBox(
		m_firstPosition,
		m_fireRot_North,
		FIRE_COLLISION_SIZE
	);

	m_fireCollision_South = NewGO<CollisionObject>(0);
	m_fireCollision_South->CreateBox(
		m_firstPosition,
		m_fireRot_South,
		FIRE_COLLISION_SIZE
	);

	m_fireCollision_East = NewGO<CollisionObject>(0);
	m_fireCollision_East->CreateBox(
		m_firstPosition,
		m_fireRot_East,
		FIRE_COLLISION_SIZE
	);

	m_fireCollision_West = NewGO<CollisionObject>(0);
	m_fireCollision_West->CreateBox(
		m_firstPosition,
		m_fireRot_West,
		FIRE_COLLISION_SIZE
	);

	//コリジョンオブジェクトが自動で削除されないようにする
	m_fireCollision_North->SetIsEnableAutoDelete(false);
	m_fireCollision_South->SetIsEnableAutoDelete(false);
	m_fireCollision_East->SetIsEnableAutoDelete(false);
	m_fireCollision_West->SetIsEnableAutoDelete(false);

	return true;
}

EffectEmitter* FireGimmic::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//エフェクトの再生
	EffectEmitter* effect = NewGO<EffectEmitter>(0);
	effect->Init(name);
	effect->SetPosition(pos);
	effect->SetRotation(rot);
	effect->SetScale(scale);
	effect->Play();
	return effect;
}

void FireGimmic::Collision()
{
	//プレイヤーと火炎放射器の距離を計算
	Vector3 toPlayer = m_player->m_position - FIRE_COLLISION_POSITION;
	float disToPlayer = toPlayer.Length();

	if (disToPlayer <= LENGTH)
	{
		m_fireRot_North.SetRotationDegY(270.0f);
		m_fireRot_South.SetRotationDegY(90.0f);
		m_fireRot_East.SetRotationDegY(180.0f);
		m_fireRot_West.SetRotationDegY(360.0f);

		//enumで4方向分作って、すぐ切り替えられるように関数を作る
		//引数で回転値(m_fireRot)を渡してみるかな？

		m_fire = PlayEffect(enEffectName_Fire, FIRE_POS, m_fireRot_East, FIRE_SCALE);

		/*if (!m_fire->IsPlay())
		{
			if (m_se->IsPlaying())
			{
				m_se->Stop();
			}
			return;
		}*/
		m_effectIntervalTimer = 0.0f;
		PlaySE();
		m_status = enStatus_Fire;
	}
}

void FireGimmic::PlaySE()
{
	m_se = NewGO<SoundSource>(0);
	m_se->Init(0);
	m_se->Play(true);
	m_se->SetVolume(SE_VOLUME);
}


void FireGimmic::Update()
{
	if (m_status == enStatus_Idle) {
		Collision();
	}
	else {
		//火が出ている状態
		// エフェクトの再生が終わる or プレイヤーとの距離が一定以上になったらおしまい
		Vector3 toPlayer = m_player->m_position - FIRE_COLLISION_POSITION;
		float disToPlayer = toPlayer.Length();
		//火炎放射の放射する時間を調節する計算
		m_effectIntervalTimer += g_gameTime->GetFrameDeltaTime();
		if (m_effectIntervalTimer >= m_effectInterval || disToPlayer > LENGTH)
		{
			// エフェクトの再生時間が一定時間を経過したら終了する
			if (m_se->IsPlaying())
			{
				m_se->Stop();
			}
			DeleteGO(m_se);
			DeleteGO(m_fire);
			m_se = nullptr;
			m_fire = nullptr;
			m_status = enStatus_Idle;
		}
	}
}

void FireGimmic::Render(RenderContext& rc)
{
	//	m_modelRender.Draw(rc);
}