#pragma once
class Player;
class Enemy;
class FloorManager;
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

	Vector3						m_scale;
	Vector3						m_position = Vector3::Zero;

	bool m_onPlayerFireTriggerFloor = false;	//プレイヤーが床の上にいるかどうか
	bool m_onEnemyFireTriggerFloor = false;	//エネミーが床の上にいるかどうか

};


