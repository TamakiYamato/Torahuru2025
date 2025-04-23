#pragma once
class Enemy;
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
		enEnemyState_Idle,			//待機・監視
		enEnemyState_Walk,			//戻る
		enEnemyState_Chase,			//追跡
		enEnemyState_Attack,		//攻撃

	};
	enum EnAnimationClip {
		enAnimationClip_Idle,		//待機・監視
		enAnimationClip_Run,		//走る
		enAnimationClip_Walk,		//歩く
		enAnimationClip_Num		
	};

	// 座標を取得
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	//キャラコンの取得
	CharacterController& GetCharacterController()
	{
		return m_charCon;
	}
	//アニメーションを共通化する。
	void SetAnimation(EnAnimationClip animationClip, std::string animationFileName, bool loopFlag);

	

	AnimationClip				m_enemyAnim[enAnimationClip_Num];
	CharacterController			m_charCon;										//キャラコン。
	ModelRender					m_modelRender;									//モデルレンダー。
	Player*						m_player;

	Vector3						m_position		= Vector3::Zero;				//座標。
	Vector3						m_scale			= Vector3::One;					//大きさ。
	Vector3						m_forward		= Vector3::AxisZ;				//enemyの正面ベクトル。
	Vector3						m_firstPosition = Vector3::Zero;				//スタート時の座標。
	Quaternion					m_rotation		= Quaternion::Identity;			//回転。

	int		m_enemyState = enEnemyState_Chase;		//enemyの状態。
};

