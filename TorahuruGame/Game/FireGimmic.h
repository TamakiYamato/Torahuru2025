#pragma once
#include "MakeEffect.h"
class Loading;
class Game;
class Player;
class FireTriggerFloor;
class FireGimmic :public IGameObject
{
public:
	FireGimmic() {};
	~FireGimmic();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void PlayCollision();											//コリジョン
	void IntervalCollision();
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
		m_rotation = rotation;
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
	FireTriggerFloor* m_fireTriggerFloor = nullptr;


	SpriteRender			m_mapSprite;				//画像
	Quaternion              m_rotation;
	Quaternion m_fireRot_North;                         //北側
	Quaternion m_fireRot_South;                         //南側
	Quaternion m_fireRot_East;                          //東側
	Quaternion m_fireRot_West;                          //西側
	CollisionObject* m_fireCollision;
	CollisionObject* m_fireCollision2;

	Vector3					m_position = Vector3::Zero;
	Vector3					m_position2 = Vector3::Zero;
	Vector3                 m_scale = Vector3::Zero;
	Vector3                 m_scale2 = Vector3::Zero;

	bool					m_moveFlag = true;					//動かしたかどうかのフラグ
	bool					m_isMoveFireFlag = true;			//動かすかどうかのフラグ

	float					m_effectPlayTimer = 0.0f;			//火炎放射器を動いている間の時間計測
	const float				m_effectPlay = 3.0f;				//火炎放射器を動かす時間
	float					m_effectIntervalTimer = 0.0f;		//火炎放射器を止まっている間の時間計測
	const float				m_effectInterval = 2.5f;			//火炎放射器を止める時間
	float					m_limit = 100.0f;
	float					m_speed = 20.0f;

};
