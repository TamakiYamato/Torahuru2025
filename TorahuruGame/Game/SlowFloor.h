#pragma once
class Player;
class Enemy;
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
	Enemy*						m_enemy;

	Vector3						m_scale;
	Vector3						m_position = Vector3::Zero;

	bool m_onPlayerSlowFloor = false;	//プレイヤーが床の上にいるかのフラグ。
	bool m_onEnemySlowFloor = false;	//エネミーが床の上にいるかのフラグ。
};

