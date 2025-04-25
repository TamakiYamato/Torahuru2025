#pragma once
#include "MakeEffect.h"

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

	//void PlayEffect();											//エフェクトの再生
	void Collision();											//エフェクト再生中のみコリジョンを作成
	void PlaySE();												//効果音を再生する

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
	// エフェクトの再生間隔を設定する
	void SetEffectInterval(const float& time)
	{
		m_effectInterval = time;
	}

	// スピードと移動制限を設定する
	void SetSppedLimit(const float& speed, const float& limit)
	{
		m_speed = speed;
		m_limit = limit;
	}


	// 移動するフラグを設定する
	void SetMoveFlag(const bool& flag)
	{
		m_moveFlag = flag;
	}

	EffectEmitter* PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);//エフェクトの基本的な情報を登録する!!

private:
	enum Status {
		enStatus_Idle,	// 火が出ていない状態
		enStatus_Fire,	// 火が出ている状態
	};
	Status					m_status = enStatus_Idle;
	ModelRender				m_modelRender;
	EffectEmitter* m_fire = nullptr;					//炎のギミックエフェクト
	EffectEmitter* m_fire2 = nullptr;					//炎のギミックエフェクト
	SoundSource* m_se;								//炎SE
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	SpriteRender			m_mapSprite;						//マップの画像
	Quaternion m_fireRot_North;                                    //炎の角度　北
	Quaternion m_fireRot_South;                                    //炎の角度　南
	Quaternion m_fireRot_East;                                    //炎の角度　東
	Quaternion m_fireRot_West;                                    //炎の角度　西

	CollisionObject* m_fireCollision;

	Vector3					m_position = Vector3::Zero;
	Vector3                 m_scale = Vector3::Zero;
    Quaternion              m_rotaion;
	Vector3					m_firstPosition = Vector3::Zero;
	bool					m_moveFlag = false;					//trueだったら動く
	float					m_effectIntervalTimer = 0.0f;		//エフェクトの間隔制御のタイマー
	float					m_effectInterval = 5.0f;			//エフェクトを停止させる間隔
	float	m_limit = 100.0f;
	float	m_speed = 20.0f;

};
