#pragma once
class Player;
class SlowFloor;
class SlowFloor : public IGameObject
{
public:
	SlowFloor();
	~SlowFloor();

	bool Start();
	void SlowControlFloor();
	void Update();
	void Render(RenderContext& rc);

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	PhysicsStaticObject			m_physicsStaticObject;
	ModelRender					m_modelRender;
	CollisionObject*			m_collisionObject = nullptr;
	Player*						m_player;

	Vector3						m_scale;
	Vector3						m_position = Vector3::Zero;

	bool m_onSlowFloor = false;	//床に載っているかの判定用変数。
};

