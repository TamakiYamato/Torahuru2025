#pragma once
class EnemyAnimation;
class Game;
class Player;
class FloorManager;
class SecondFloor;
class Enemy : public IGameObject
{
private:
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// start
	/// </summary>
	/// <returns></returns>
	bool Start();

	/// <summary>
	/// アップデート
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);

	/// <summary>
	/// 重力を加える
	/// </summary>
	void SetGravity();

	/// <summary>
	/// 敵キャラクターの状態遷移を処理する共通のメソッド
	/// </summary>
	void CommonStateTransitionProcess();

	/// <summary>
	/// 移動速度を消し、その場でplayerが来るのを待つ
	/// </summary>
	void Stand();

	/// <summary>
	/// 最初の位置に戻る。
	/// </summary>
	void ReturnToSpawn();

	/// <summary>
	/// プレイヤーを追跡。
	/// </summary>
	void Chase();

	/// <summary>
	/// 移動方向に基づいて敵キャラクターの回転を計算
	/// モデルの位置と回転を更新
	/// 前方ベクトルの更新
	/// </summary>
	void Rotation();

	/// <summary>
	/// プレイヤを探す。
	/// </summary>
	bool SearchPlayer();

	/// <summary>
	/// ステート管理。
	/// </summary>
	void ManageState();

	/// <summary>
	/// アニメーションの管理
	/// </summary>
	void PlayAnimation(int enemyState);

	/// <summary>
	/// プレイヤーがエネミーに一定距離近づいたら即死ステートに変更
	/// </summary>
	void CheckPlayerProximityAndDie();

	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// キャラコンの取得
	/// </summary>
	/// <returns></returns>
	CharacterController& GetCharacterController()
	{
		return m_charCon;
	}

	CharacterController	m_charCon; //キャラコン。
	ModelRender	m_modelRender; //モデルレンダー。
	Player* m_player; //プレイヤー。
	EnemyAnimation* m_enemyAnim; //敵のアニメーション。
	FloorManager* m_floorManager; //フロアマネージャー。
	SecondFloor* m_secondfloor = nullptr; //セカンドフロア。

	float m_chaseTimer = 0.0f; //追跡時間。
	float m_idleTimer = 0.0f; //待機時間。
	bool m_hasWaitedBeforeReturn = true; //初期値へ戻る前に待機状態に移行したかどうか。
	bool m_isReadyIdle = false; //待機状態にしてよいかのフラグ

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// 回転を設定します。
	/// </summary>
	/// <param name="rotation">設定するクォータニオン回転。</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_currentRotation = rotation;

	}

	/// <summary>
	/// スケール値を設定します。
	/// </summary>
	/// <param name="scale">設定するスケール値（Vector3 型の参照）。</param>
	void SetScale(const Vector3& scale) 
	{
		m_scale = scale;
	}

	/// <summary>
	/// アニメーションを設定します。
	/// </summary>
	/// <param name="enemyAnim"></param>
	void SetAnimation(EnemyAnimation* enemyAnim) 
	{
		m_enemyAnim = enemyAnim;
	}

	/// <summary>
	/// 敵キャラクターの状態を表す列挙型です。
	/// </summary>
	enum EnemyState {				//移動速度に代入。
		enEnemyState_Idle,			//待機・監視
		enEnemyState_Walk,			//戻る
		enEnemyState_Chase,			//追跡
		enEnemyState_Attack,		//攻撃
	};

	Vector3	m_position = Vector3::Zero;	//座標。
	Vector3	m_scale = Vector3::One;	//大きさ。
	Vector3	m_forward = Vector3::AxisZ;	//enemyの正面ベクトル。
	Vector3	m_initialPosition = Vector3::Zero; //スタート時の座標。
	Vector3	m_moveSpeed = Vector3::Zero; //移動速度。
	Vector3	m_savedMoveSpeed = Vector3::Zero; //移動速度を一時的に保存
	Quaternion m_currentRotation = Quaternion::Identity; //今の角度の保存。
	Quaternion m_initialRotation = Quaternion::Identity; //スタート時の角度。

	int	m_enemyState = enEnemyState_Idle; //enemyの状態。

};
