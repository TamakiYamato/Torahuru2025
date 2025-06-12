#pragma once
class Player;
class Enemy;
class FloorManager;
class FirstFloor;
class SecondFloor;
class FireTriggerFloor : public IGameObject 
{
public:
	FireTriggerFloor() {};
	~FireTriggerFloor() {};

	bool Start();
	void FireTriggerControlFloor();
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


	PhysicsStaticObject	m_physicsStaticObject;
	ModelRender	m_modelRender;
	CollisionObject* m_collisionObject;
	Player* m_player;
	Enemy* m_enemy;
	FirstFloor* m_firstFloor = nullptr;
	SecondFloor* m_secondFloor = nullptr;
	Vector3						m_scale;
	Vector3						m_position = Vector3::Zero;
	FireTriggerFloor* m_fireTriggerFloor = nullptr;
	bool m_onFireTriggerFloor = false;	//プレイヤーが床の上にいるかどうか
};


