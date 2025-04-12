#pragma once
class Player;
class BlindFloor;
class BlindFloor : public IGameObject
{
public:
	BlindFloor();
	~BlindFloor();

	bool Start();
	void BlindControlFloor();
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
	CollisionObject*			m_collisionObject;
	Player*						m_player;

	Vector3						m_scale;
	Vector3						m_position = Vector3::Zero;

	bool m_onBlindFloor = false;	//è∞Ç…ç⁄Ç¡ÇƒÇ¢ÇÈÇ©ÇÃîªíËópïœêîÅB

};

