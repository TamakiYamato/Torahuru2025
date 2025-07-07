#pragma once
class RotationFloor;
class Game;
class GameClear;
class FirstFloor;
class SecondFloor;
class Player;
class Enemy;
class SecondFloor;

/// <summary>
/// 回転床のGameObject。
/// </summary>

class  RotationFloor:public IGameObject 
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RotationFloor() {};

	/// <summary>
	/// スタート。
	/// </summary>
	 bool Start();
	
	/// <summary>
	/// アップデート。
	/// </summary>
	 void Update();
		
	 /// <summary>
	 /// 回転。
	 /// </summary>
	 void Rotation();
	
	/// <summary>
	// モデルレンダラー:描画。
	/// </summary>
	 void Render(RenderContext& renderContext);
		
	/// <summary>
	/// 座標を取得。
	/// </summary>
	 const Vector3& GetPosition() const
	 {
		 return m_position;
	 }

	 void SetPosition(const Vector3& position)
	 {
		 m_position = position;
	 }

	 void SetScale(const Vector3& scale)
	 {
		 m_scale = scale;
	 }

	 void SetRotation(const Quaternion& rotation) {
		 m_rotation = rotation;
		 m_modelRender.SetRotation(rotation);
	 }

private:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~RotationFloor() {};
	
	/// <summary>
	/// 回転床のスピード
	/// </summary>
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{
		m_moveSpeed += addMoveSpeed;
	}

	/// <summary>
	/// 回転床の計算処理
	/// </summary>
	void RotationFloorCalc();
	
private:
	float m_rotationAngle = 1.0f; //回転軸。
	float m_rotationSpeed = 0.1f; //回転速度。

	PhysicsStaticObject	m_physicsStaticObject;//静的オブジェクト。
	ModelRender	m_modelRender; //モデルの描画。

	Quaternion m_rotation; //回転参照。

	Vector3	m_position; //回転床のポジション。
	Vector3 m_scale = Vector3::One*10;
	Vector3 m_moveSpeed = Vector3::Zero;

	Player* m_player = nullptr; //クラス参照。
	FirstFloor* m_firstfloor = nullptr;
	SecondFloor* m_secondfloor = nullptr;
};

