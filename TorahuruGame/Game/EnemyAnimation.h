#pragma once
class Enemy;
class EnemyAnimation : public IGameObject
{
public:
	EnemyAnimation();
	~EnemyAnimation();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	enum EnAnimationClip {
		enAnimationClip_Idle,		//蠕・ｩ溘・逶｣隕・
		enAnimationClip_Run,		//襍ｰ繧・
		enAnimationClip_Walk,		//豁ｩ縺・
		enAnimationClip_Num
	};

	//繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・騾壼喧縺吶ｋ縲・
	void SetAnimation(EnAnimationClip animationClip, std::string animationFileName, bool loopFlag);

	CharacterController			m_charCon;										//繧ｭ繝｣繝ｩ繧ｳ繝ｳ縲・
	ModelRender					m_modelRender;									//繝｢繝・Ν繝ｬ繝ｳ繝繝ｼ縲・
	AnimationClip				m_enemyAnim[enAnimationClip_Num];

	Vector3						m_position = Vector3::Zero;						//蠎ｧ讓吶・
	Vector3						m_scale = Vector3::One;							//螟ｧ縺阪＆縲・
	Quaternion					m_rotation = Quaternion::Identity;				//蝗櫁ｻ｢縲・
};


