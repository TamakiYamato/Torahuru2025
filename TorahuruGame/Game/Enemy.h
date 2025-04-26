#pragma once
class Enemy;
class EnemyAnimation;
class Game;
class Player;
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Stand();
	void Move();
	void Chase();
	void SearchPlayer();
	void ManageState();
	void PlayAnimation();

	enum EnemyState {
		enEnemyState_Idle,			//蠕・ｩ溘・逶｣隕・
		enEnemyState_Walk,			//謌ｻ繧・
		enEnemyState_Chase,			//霑ｽ霍｡
		enEnemyState_Attack,		//謾ｻ謦・

	};
	

	// 蠎ｧ讓吶ｒ蜿門ｾ・
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	//繧ｭ繝｣繝ｩ繧ｳ繝ｳ縺ｮ蜿門ｾ・
	CharacterController& GetCharacterController()
	{
		return m_charCon;
	}

	

	CharacterController			m_charCon;										//繧ｭ繝｣繝ｩ繧ｳ繝ｳ縲・
	ModelRender					m_modelRender;									//繝｢繝・Ν繝ｬ繝ｳ繝繝ｼ縲・
	Player*						m_player;
	EnemyAnimation*				m_enemyAnim;

	Vector3						m_position		= Vector3::Zero;				//蠎ｧ讓吶・
	Vector3						m_scale			= Vector3::One;					//螟ｧ縺阪＆縲・
	Vector3						m_forward		= Vector3::AxisZ;				//enemy縺ｮ豁｣髱｢繝吶け繝医Ν縲・
	Vector3						m_firstPosition = Vector3::Zero;				//繧ｹ繧ｿ繝ｼ繝域凾縺ｮ蠎ｧ讓吶・
	Quaternion					m_rotation		= Quaternion::Identity;			//蝗櫁ｻ｢縲・

	int		m_enemyState = enEnemyState_Chase;		//enemy縺ｮ迥ｶ諷九・
};

