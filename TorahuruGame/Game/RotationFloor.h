#pragma once
class RotationFloor;
class Game;
class GameClear;
class FirstFloor;
class SecondFloor;
class Player;
class Enemy;
class SecondFloor;

enum enMovingFloorState {
	enMovingFloorState_RotateRight,
	enMovingFloorState_RotateLeft
};



class  RotationFloor:public IGameObject 
{


public:
	RotationFloor();
	~RotationFloor();
	bool Start();
	void Update();
	void Rotation();
	void Render(RenderContext& renderContext);
	
	// 座標を取得
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
	
	//CollisionObject* m_collisitonObject = nullptr;
	PhysicsStaticObject			m_physicsStaticObject;
	ModelRender m_modelRender;
	Player* m_player = nullptr;
	
	Quaternion     m_rotation;
	int			moveState = 0;		
	FirstFloor* m_firstfloor = nullptr;
	SecondFloor* m_secondfloor = nullptr;
	Vector3						m_position;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed = Vector3::Zero;
private:
	float m_rotationAngle = 1.0f;//回転軸
	float m_rotationSpeed = 0.1f;//回転速度
	float GetYDegree() const;
private:
	void Move();
	void MapMove();
	
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{

		m_moveSpeed += addMoveSpeed;
	}
};

