#pragma once
class Player;
class ReverseFloor;
class ReverseFloor : public IGameObject
{
public:
	ReverseFloor();
	~ReverseFloor();

	bool Start();
	void ReverseControlFloor();
	void Update();
	void Render(RenderContext& rc);


	Vector3						m_position = Vector3::Zero;
	PhysicsStaticObject			m_physicsStaticObject;
	ModelRender					m_modelRender;

	CollisionObject* m_collisionObject = nullptr;
	Player* m_player;

	bool GimmikFlag = false;
};


