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
		enAnimationClip_Idle,		//待機・監視
		enAnimationClip_Run,		//走る
		enAnimationClip_Walk,		//歩く
		enAnimationClip_Num
	};

	//アニメーションを共通化する。
	void SetAnimation(EnAnimationClip animationClip, std::string animationFileName, bool loopFlag);

	CharacterController			m_charCon;										//キャラコン。
	ModelRender					m_modelRender;									//モデルレンダー。
	AnimationClip				m_enemyAnim[enAnimationClip_Num];

	Vector3						m_position = Vector3::Zero;						//座標。
	Vector3						m_scale = Vector3::One;							//大きさ。
	Quaternion					m_rotation = Quaternion::Identity;				//回転。
};


