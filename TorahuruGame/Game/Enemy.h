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
	void CheckPlayerProximityAndDie();

	enum EnemyState {	//=移動速度に代入。
		enEnemyState_Idle = 0,			//待機・監視
		enEnemyState_Walk = 150,			//戻る
		enEnemyState_Chase = 200,			//追跡
		enEnemyState_Attack,				//攻撃

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



	CharacterController			m_charCon;										//キャラコン。
	ModelRender					m_modelRender;									//モデルレンダー。
	Player* m_player;
	EnemyAnimation* m_enemyAnim;

	Vector3						m_position = Vector3::Zero;					//座標。
	Vector3						m_scale = Vector3::One;						//大きさ。
	Vector3						m_forward = Vector3::AxisZ;					//enemyの正面ベクトル。
	Vector3						m_firstPosition = Vector3::Zero;					//スタート時の座標。
	Vector3						m_moveSpeed = Vector3::Zero;					//移動速度。
	Quaternion					m_rotation = Quaternion::Identity;				//回転。

	int		m_enemyState = enEnemyState_Chase;		//enemyの状態。
};
