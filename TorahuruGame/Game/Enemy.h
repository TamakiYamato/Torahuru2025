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
	void Stand();
	void Move();
	void Chase();
	void SearchPlayer();
	void ManageState();
	void PlayAnimation();
	void CheckPlayerProximityAndDie();
	void Attack();
	float GetAngleBetweenQuaternions(const Quaternion& q1, const Quaternion& q2);

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
	//値を指定した最小値と最大値の範囲に制限するための関数
	template<typename T>
	T Clamp(T value, T minVal, T maxVal)
	{
		if (value < minVal) return minVal ;
		if (value > maxVal) return maxVal;
		return value;
	}

	//キャラコンの取得
	CharacterController& GetCharacterController()
	{
		return m_charCon;
	}


	CharacterController			m_charCon;									//キャラコン。
	ModelRender					m_modelRender;								//モデルレンダー。
	Player*						m_player;
	EnemyAnimation*				m_enemyAnim;
	FloorManager*				m_floorManager;								//フロアマネージャー。
	SecondFloor* m_secondfloor = nullptr;
	Vector3						m_position = Vector3::Zero;					//座標。
	Vector3						m_scale = Vector3::One;						//大きさ。
	Vector3						m_forward = Vector3::AxisZ;					//enemyの正面ベクトル。
	Vector3						m_initialPosition = Vector3::Zero;			//スタート時の座標。
	Vector3						m_moveSpeed = Vector3::Zero;				//移動速度。
	Quaternion					m_currentRotation = Quaternion::Identity;	//今の角度の保存。
	Quaternion					m_initialRotation = Quaternion::Identity;	//スタート時の角度。

	int							m_enemyState = enEnemyState_Idle;			//enemyの状態。
	float						m_moveDir = 1.0f;							//床の効果を受けときの変更
};
