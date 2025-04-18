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
	Vector3 COLLISION_POSITION = Vector3(100.0f, 0.0f, 100.0f);

	Vector3 firePosition = Vector3(400.0f, 125.0f, -825.0f);
	Vector3 firePosition2 = Vector3(2100.0f, 150.0f, -1200.0f);

	Quaternion fireQuaternion = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

	Vector3 fireScale = Vector3(35.0f, 10.0f, 10.0f);

	const float LENGTH = 3000.0f;			//効果音を再生する距離
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
	if (m_fire2 != nullptr) {
		DeleteGO(m_fire2);
	}

	DeleteGO(m_fireCollision);
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
	m_fireCollision = NewGO<CollisionObject>(0);
	m_fireCollision->CreateBox(
		m_firstPosition,
		m_fireRot_East,
		COLLISION_SIZE
	);

	m_fireCollision = NewGO<CollisionObject>(0);
	m_fireCollision->CreateBox(
		m_firstPosition,
		m_fireRot_West,
		COLLISION_SIZE
	);

	m_fireCollision = NewGO<CollisionObject>(0);
	m_fireCollision->CreateBox(
		m_firstPosition,
		m_fireRot_North,
		COLLISION_SIZE
	);

	m_fireCollision = NewGO<CollisionObject>(0);
	m_fireCollision->CreateBox(
		m_firstPosition,
		m_fireRot_South,
		COLLISION_SIZE
	);

	//コリジョンオブジェクトが自動で削除されないようにする
	m_fireCollision->SetIsEnableAutoDelete(false);

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
	Vector3 toPlayer = m_player->m_position - COLLISION_POSITION;
	float disToPlayer = toPlayer.Length();

	if (disToPlayer <= LENGTH)
	{
		m_fireRot_North.SetRotationDegY(270.0f);
		m_fireRot_South.SetRotationDegY(90.0f);
		m_fireRot_East.SetRotationDegY(180.0f);
		m_fireRot_West.SetRotationDegY(360.0f);

		//enumで4方向分作って、すぐ切り替えられるように関数を作る
		//引数で回転値(m_fireRot)を渡してみるかな？

		m_fire = PlayEffect(enEffectName_Fire, firePosition, m_fireRot_West, fireScale);
		m_fire2 = PlayEffect(enEffectName_Fire, firePosition2, m_fireRot_North, fireScale);

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
		Vector3 toPlayer = m_player->m_position - COLLISION_POSITION;
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
			DeleteGO(m_fire2);
			m_se = nullptr;
			m_fire = nullptr;
			m_fire2 = nullptr;
			m_status = enStatus_Idle;
		}
	}
}

void FireGimmic::Render(RenderContext& rc)
{
	//	m_modelRender.Draw(rc);
}