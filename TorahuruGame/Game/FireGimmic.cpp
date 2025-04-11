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

	Vector3 firePosition = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 fireScale = Vector3(10.0f, 10.0f, 10.0f);

	const float LENGTH = 1.0f;			//効果音を再生する距離
	const float SE_VOLUME = 1.0f;
}

FireGimmic::FireGimmic()
{
}

FireGimmic::~FireGimmic()
{

}

bool FireGimmic::Start()
{
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/laser.efk");

	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/fire.wav");

	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	m_firstPosition = m_position;

	

	return true;
}

void FireGimmic::Update()
{
	/*m_fire->NewGO<FireGimmic>(0);*/
	/*m_fire->Init(0);
	m_fire->SetScale(fireScale);
	m_fire->SetPosition(firePosition);
	m_fire->Play();*/

	if (g_pad[0]->IsPress(enButtonB))
	{
		PlayEffect(enEffectName_Fire, firePosition, m_rotation, fireScale);
		if (m_fire->IsPlay())
		{
			m_se = NewGO<SoundSource>(0);
			m_se->Init(0);
			m_se->Play(false);
			m_se->SetVolume(SE_VOLUME);
		}
		
		

	}
	Collision();
	PlaySE();
	

}



void FireGimmic::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//エフェクトの再生
	EffectEmitter* effect = NewGO<EffectEmitter>(0);
	effect->Init(name);
	effect->SetPosition(pos);
	effect->SetRotation(rot);
	effect->SetScale(scale);
	effect->Play();

}

void FireGimmic::Collision()
{

}

void FireGimmic::PlaySE()
{

}

void FireGimmic::Render(RenderContext& rc)
{
//	m_modelRender.Draw(rc);
}