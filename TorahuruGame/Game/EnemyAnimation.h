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
		enAnimationClip_Idle,		//待機
		enAnimationClip_Run,		//走る
		enAnimationClip_Walk,		//歩く
		enAnimationClip_Num
	};

	//
	void SetAnimation(EnAnimationClip animationClip, std::string animationFileName, bool loopFlag);

	CharacterController			m_charCon;										//キャラクターコントロール
	ModelRender					m_modelRender;									//モデルレンダー
	AnimationClip				m_enemyAnim[enAnimationClip_Num];

	Vector3						m_position = Vector3::Zero;						//ポジション
	Vector3						m_scale = Vector3::One;							//大きさ
	Quaternion					m_rotation = Quaternion::Identity;				//回転
};


