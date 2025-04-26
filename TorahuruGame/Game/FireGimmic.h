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

	//void PlayEffect();											//繧ｨ繝輔ぉ繧ｯ繝医・蜀咲函
	void Collision();											//繧ｨ繝輔ぉ繧ｯ繝亥・逕滉ｸｭ縺ｮ縺ｿ繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ繧剃ｽ懈・
	void PlaySE();												//蜉ｹ譫憺浹繧貞・逕溘☆繧・

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
	// 繧ｨ繝輔ぉ繧ｯ繝医・蜀咲函髢馴囈繧定ｨｭ螳壹☆繧・
	void SetEffectInterval(const float& time)
	{
		m_effectInterval = time;
	}

	// 繧ｹ繝斐・繝峨→遘ｻ蜍募宛髯舌ｒ險ｭ螳壹☆繧・
	void SetSppedLimit(const float& speed, const float& limit)
	{
		m_speed = speed;
		m_limit = limit;
	}


	// 遘ｻ蜍輔☆繧九ヵ繝ｩ繧ｰ繧定ｨｭ螳壹☆繧・
	void SetMoveFlag(const bool& flag)
	{
		m_moveFlag = flag;
	}

	EffectEmitter* PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);//繧ｨ繝輔ぉ繧ｯ繝医・蝓ｺ譛ｬ逧・↑諠・ｱ繧堤匳骭ｲ縺吶ｋ!!

private:
	enum Status {
		enStatus_Idle,	// 轣ｫ縺悟・縺ｦ縺・↑縺・憾諷・
		enStatus_Fire,	// 轣ｫ縺悟・縺ｦ縺・ｋ迥ｶ諷・
	};
	Status					m_status = enStatus_Idle;
	ModelRender				m_modelRender;
	EffectEmitter* m_fire = nullptr;					//轤弱・繧ｮ繝溘ャ繧ｯ繧ｨ繝輔ぉ繧ｯ繝・
	EffectEmitter* m_fire2 = nullptr;					//轤弱・繧ｮ繝溘ャ繧ｯ繧ｨ繝輔ぉ繧ｯ繝・
	SoundSource* m_se;								//轤惨E
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	SpriteRender			m_mapSprite;						//繝槭ャ繝励・逕ｻ蜒・
	Quaternion m_fireRot_North;                                    //轤弱・隗貞ｺｦ縲蛹・
	Quaternion m_fireRot_South;                                    //轤弱・隗貞ｺｦ縲蜊・
	Quaternion m_fireRot_East;                                    //轤弱・隗貞ｺｦ縲譚ｱ
	Quaternion m_fireRot_West;                                    //轤弱・隗貞ｺｦ縲隘ｿ

	CollisionObject* m_fireCollision;

	Vector3					m_position = Vector3::Zero;
	Vector3                 m_scale = Vector3::Zero;
    Quaternion              m_rotaion;
	Vector3					m_firstPosition = Vector3::Zero;
	bool					m_moveFlag = false;					//true縺縺｣縺溘ｉ蜍輔￥
	float					m_effectIntervalTimer = 0.0f;		//繧ｨ繝輔ぉ繧ｯ繝医・髢馴囈蛻ｶ蠕｡縺ｮ繧ｿ繧､繝槭・
	float					m_effectInterval = 5.0f;			//繧ｨ繝輔ぉ繧ｯ繝医ｒ蛛懈ｭ｢縺輔○繧矩俣髫・
	float	m_limit = 100.0f;
	float	m_speed = 20.0f;

};
