#pragma once
#include "MakeEffect.h"
class Loading;
class Game;
class Player;
class FireGimmic :public IGameObject
{
public:
	FireGimmic();
	~FireGimmic();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//void PlayEffect();											//
	void Collision();											//コリジョン
	void PlaySE();												//効果音

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	void SetRotation(const Quaternion& rotation) {
		m_rotaion = rotation;
	}
	// effectを出す時間までの時間
	void SetEffectInterval(const float& time)
	{
		m_effectInterval = time;
	}

	// 発射スピードと放射時間
	void SetSppedLimit(const float& speed, const float& limit)
	{
		m_speed = speed;
		m_limit = limit;
	}


	// 火炎放射器が動いているか
	void SetMoveFlag(const bool& flag)
	{
		m_moveFlag = flag;
	}

	EffectEmitter* PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);//effectの再生

private:
	enum Status {
		enStatus_Idle,	// 待機
		enStatus_Fire,	// 放射中
	};
	Status					m_status = enStatus_Idle;
	ModelRender				m_modelRender;
	EffectEmitter* m_fire = nullptr;					//
	EffectEmitter* m_fire2 = nullptr;					//
	SoundSource* m_se;									//se
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	SpriteRender			m_mapSprite;				//画像
	Quaternion m_fireRot_North;                         //北側
	Quaternion m_fireRot_South;                         //南側
	Quaternion m_fireRot_East;                          //東側
	Quaternion m_fireRot_West;                          //西側
	
	CollisionObject* m_fireCollision;

	Vector3					m_position = Vector3::Zero;
	Vector3                 m_scale = Vector3::Zero;
    Quaternion              m_rotaion;
	Vector3					m_firstPosition = Vector3::Zero;
	bool					m_moveFlag = false;					//動いているかのフラグ
	float					m_effectIntervalTimer = 0.0f;		//火炎放射器を動かさない時間の計測
	float					m_effectInterval = 5.0f;			//火炎放射器を動かさない時間
	float	m_limit = 100.0f;
	float	m_speed = 20.0f;

};
