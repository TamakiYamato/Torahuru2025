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
	Vector3 fireScale2 = Vector3(15.0f, 10.0f, 10.0f);

	const float LENGTH = 3000.0f;			//蜉ｹ譫憺浹繧貞・逕溘☆繧玖ｷ晞屬
	const float SE_VOLUME = 0.05f;

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

	//繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ繧ｪ繝悶ず繧ｧ繧ｯ繝医・蛻晄悄蛹・
	//4遞ｮ鬘槭▽縺上▲縺ｦ
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

	//繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ繧ｪ繝悶ず繧ｧ繧ｯ繝医′閾ｪ蜍輔〒蜑企勁縺輔ｌ縺ｪ縺・ｈ縺・↓縺吶ｋ
	m_fireCollision->SetIsEnableAutoDelete(false);

	return true;
}

EffectEmitter* FireGimmic::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//繧ｨ繝輔ぉ繧ｯ繝医・蜀咲函
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
	//繝励Ξ繧､繝､繝ｼ縺ｨ轣ｫ轤取叛蟆・勣縺ｮ霍晞屬繧定ｨ育ｮ・
	Vector3 toPlayer = m_player->m_position - COLLISION_POSITION;
	float disToPlayer = toPlayer.Length();

	if (disToPlayer <= LENGTH)
	{
		m_fireRot_North.SetRotationDegY(270.0f);
		m_fireRot_South.SetRotationDegY(90.0f);
		m_fireRot_East.SetRotationDegY(180.0f);
		m_fireRot_West.SetRotationDegY(360.0f);

		//enum縺ｧ4譁ｹ蜷大・菴懊▲縺ｦ縲√☆縺仙・繧頑崛縺医ｉ繧後ｋ繧医≧縺ｫ髢｢謨ｰ繧剃ｽ懊ｋ
		//蠑墓焚縺ｧ蝗櫁ｻ｢蛟､(m_fireRot)繧呈ｸ｡縺励※縺ｿ繧九°縺ｪ・・

		m_fire = PlayEffect(enEffectName_Fire, firePosition, m_fireRot_West, fireScale);
		m_fire2 = PlayEffect(enEffectName_Fire, firePosition2, m_fireRot_North, fireScale2);

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
		//轣ｫ縺悟・縺ｦ縺・ｋ迥ｶ諷・
		// 繧ｨ繝輔ぉ繧ｯ繝医・蜀咲函縺檎ｵゅｏ繧・or 繝励Ξ繧､繝､繝ｼ縺ｨ縺ｮ霍晞屬縺御ｸ螳壻ｻ･荳翫↓縺ｪ縺｣縺溘ｉ縺翫＠縺ｾ縺・
		Vector3 toPlayer = m_player->m_position - COLLISION_POSITION;
		float disToPlayer = toPlayer.Length();
		//轣ｫ轤取叛蟆・・謾ｾ蟆・☆繧区凾髢薙ｒ隱ｿ遽縺吶ｋ險育ｮ・
		m_effectIntervalTimer += g_gameTime->GetFrameDeltaTime();
		if (m_effectIntervalTimer >= m_effectInterval || disToPlayer > LENGTH)
		{
			// 繧ｨ繝輔ぉ繧ｯ繝医・蜀咲函譎る俣縺御ｸ螳壽凾髢薙ｒ邨碁℃縺励◆繧臥ｵゆｺ・☆繧・
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