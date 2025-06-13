#pragma once
class EnemyAnimation;
class Game;
class Player;
class FloorManager;
class SecondFloor;
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void CommonStateTransitionProcess();
	void SetGravity();
	void Stand();
	void ReturnToSpawn();
	void Chase();
	void Rotation();
	bool SearchPlayer();
	void ManageState();
	void PlayAnimation(int enemyState);
	void CheckPlayerProximityAndDie();

	enum EnemyState {				//移動速度に代入。
		enEnemyState_Idle,			//待機・監視
		enEnemyState_Walk,			//戻る
		enEnemyState_Chase,			//追跡
		enEnemyState_Attack,		//攻撃

	};

	// 座標を取得
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	void SetRotation(const Quaternion& rotation) {
		m_currentRotation = rotation;

	}
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	void SetAnimation(EnemyAnimation* enemyAnim) {
		m_enemyAnim = enemyAnim;
	}

	//キャラコンの取得
	CharacterController& GetCharacterController()
	{
		return m_charCon;
	}


	CharacterController			m_charCon;									//キャラコン。
	ModelRender					m_modelRender;								//モデルレンダー。
	Player* m_player;
	EnemyAnimation* m_enemyAnim;
	FloorManager* m_floorManager;								//フロアマネージャー。
	SecondFloor* m_secondfloor = nullptr;
	Vector3						m_position = Vector3::Zero;					//座標。
	Vector3						m_scale = Vector3::One;						//大きさ。
	Vector3						m_forward = Vector3::AxisZ;					//enemyの正面ベクトル。
	Vector3						m_initialPosition = Vector3::Zero;			//スタート時の座標。
	Vector3						m_moveSpeed = Vector3::Zero;				//移動速度。
	Vector3						m_savedMoveSpeed = Vector3::Zero;			//移動速度を一時的に保存
	Quaternion					m_currentRotation = Quaternion::Identity;	//今の角度の保存。
	Quaternion					m_initialRotation = Quaternion::Identity;	//スタート時の角度。

	int							m_enemyState = enEnemyState_Idle;			//enemyの状態。
	float						m_moveRate = 1.0f;							//床の効果を受けときの変更
	float						m_chaseTimer = 0.0f;						//追跡時間。
	float						m_idleTimer = 0.0f;							//待機時間。
	bool						m_hasWaitedBeforeReturn = true;				//初期値へ戻る前に待機状態に移行したかどうか。
	bool						m_isReadyIdle = false;						//待機状態にしてよいかのフラグ
};
