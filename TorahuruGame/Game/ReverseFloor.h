#pragma once
class Player;
class RevreseFloor;
class ReverseFloor : public IGameObject
{
public:
	ReverseFloor();
	~ReverseFloor();

	bool Start();
	void ReverseControlFloor();
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

	Vector3						m_scale;
	Vector3						m_position = Vector3::Zero;
	PhysicsStaticObject			m_physicsStaticObject;
	
	ModelRender					m_modelRender;

	CollisionObject* m_collisionObject = nullptr;
	Player* m_player;


	bool m_onReverseFloor = false;
};


