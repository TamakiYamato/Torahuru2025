#include "stdafx.h"
#include "FireGimmic.h"
#include "Game.h"
#include "Player.h"
#include "FirstFloor.h"
#include "collision/CollisionObject.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundSource.h"
#include "sound/SoundEngine.h"

namespace {
	const Vector3 COLLISION_SIZE = Vector3(150.0f, 250.0f, 900.0f);
	const Vector3 COLLISION_SIZE2 = Vector3(150.0f, 250.0f, 450.0f);
	const Vector3 COLLISION_POSITION = Vector3(10.0f, 0.0f, 10.0f);

	const Vector3 FIREPOSITION = Vector3(-470.0f, 70.0f, -400.0f);
	const Vector3 FIREPOSITION2 = Vector3(1750.0f, 70.0f, -1200.0f);

	const Vector3 FIRESCALE = Vector3(20.0f, 10.0f, 10.0f);
	const Vector3 FIRESCALE2 = Vector3(15.0f, 10.0f, 10.0f);

	const Quaternion FIREQUATERNION = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

	const float FIREROT_NORTH = 270.0f;
	const float FIREROT_SOUTH = 90.0f;
	const float FIREROT_EAST = 180.0f;
	const float FIREROT_WEST = 360.0f;

	const float LENGTH = 3000.0f;			//長さ
	const float SE_VOLUME = 0.01f;

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

	m_position = FIREPOSITION;
	m_position2 = FIREPOSITION2;

	m_scale = COLLISION_SIZE;
	m_scale2 = COLLISION_SIZE2;

	Vector3 offset = Vector3{ 0.0f,0.0f,m_scale.z / 2.0f };
	Vector3 offset2 = Vector3{ 0.0f,0.0f,m_scale2.z / 2.0f };

	//火炎放射器のコリジョンの生成
	m_fireCollision = NewGO<CollisionObject>(0);
	m_fireCollision->SetName("fireCollision");
	Vector3 position = m_position - offset;
	m_fireCollision->CreateBox(
		position,
		m_fireRot_South,
		m_scale
	);

	m_fireCollision2 = NewGO<CollisionObject>(0);
	m_fireCollision2->SetName("fireCollision");
	Vector3 position2 = m_position2 - offset2;
	m_fireCollision2->CreateBox(
		position2,
		m_fireRot_South,
		m_scale2
	);

	m_status = enStatus_Idle;

	//コリジョンが自動で消えないようにする
	m_fireCollision->SetIsEnableAutoDelete(false);
	m_fireCollision2->SetIsEnableAutoDelete(false);

	return true;
}

EffectEmitter* FireGimmic::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//effectの設定
	EffectEmitter* effect = NewGO<EffectEmitter>(0);
	if (!effect)return nullptr;

	effect->Init(name);
	effect->SetPosition(pos);
	effect->SetRotation(rot);
	effect->SetScale(scale);
	effect->Play();
	return effect;
}

void FireGimmic::PlayCollision()
{
	//プレイヤーと火炎放射器とのベクトルを計算
	Vector3 toPlayer = m_player->m_position - COLLISION_POSITION;
	float disToPlayer = toPlayer.Length();

	//再生時間を計算
	m_effectPlayTimer += g_gameTime->GetFrameDeltaTime();

	//再生時間内の間
	if (m_effectPlayTimer <= m_effectPlay && disToPlayer <= LENGTH)
	{
		m_fireRot_North.SetRotationDegY(FIREROT_NORTH);
		m_fireRot_South.SetRotationDegY(FIREROT_SOUTH);
		m_fireRot_East.SetRotationDegY(FIREROT_EAST);
		m_fireRot_West.SetRotationDegY(FIREROT_WEST);

		if (m_moveFlag) {
			m_fire = PlayEffect(enEffectName_Fire, FIREPOSITION, m_fireRot_North, FIRESCALE);
			m_fire2 = PlayEffect(enEffectName_Fire, FIREPOSITION2, m_fireRot_North, FIRESCALE2);
			PlaySE();
			m_moveFlag = false;
		}
	}

	//再生時間外の場合
	else if(m_effectPlayTimer >= m_effectPlay){
		m_effectPlayTimer = 0.0f;
		m_status = enStatus_Idle;
		m_isMoveFireFlag = false;
		m_moveFlag = true;
	}
}

void FireGimmic::IntervalCollision()
{
	//playerと火炎放射器とのベクトルを計算
	Vector3 toPlayer = m_player->m_position - COLLISION_POSITION;
	float disToPlayer = toPlayer.Length();
	//火炎放射器を止める時間の計測
	m_effectIntervalTimer += g_gameTime->GetFrameDeltaTime();

	//火炎放射器を止める間
	if (m_effectIntervalTimer <= m_effectInterval && disToPlayer > LENGTH)
	{
		//火炎放射器のエフェクトの再生を止める
		if (m_fire && m_fire->IsPlay()) {
			m_fire->Stop();
			m_fire2->Stop();
		}
		//かえん放射器の効果音の再生を止める
		if (m_se && m_se->IsPlaying())
		{
			m_se->Stop();
		}

		DeleteGO(m_se);
		DeleteGO(m_fire);
		DeleteGO(m_fire2);

		m_se = nullptr;
		m_fire = nullptr;
		m_fire2 = nullptr;
	}

	//火炎放射器を動かす時間になった時
	else if (m_effectIntervalTimer >= m_effectInterval) {
		m_isMoveFireFlag = true;
		m_status = enStatus_Fire;
		m_effectIntervalTimer = 0.0f;
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
	if (m_status == enStatus_Fire) {
		PlayCollision();
	}

	else if(m_status == enStatus_Idle){
		IntervalCollision();
	}

	// m_isMoveFireFlag によって当たり判定の有効・無効を制御
	if (m_isMoveFireFlag) {
		m_fireCollision->SetIsEnable(true);
		m_fireCollision2->SetIsEnable(true);
	}
	else {
		m_fireCollision->SetIsEnable(false);
		m_fireCollision2->SetIsEnable(false);
	}
}

void FireGimmic::Render(RenderContext& rc)
{
}