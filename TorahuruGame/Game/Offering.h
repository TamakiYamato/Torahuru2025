#pragma once
class Player;
class Game;
class Offering : public IGameObject
{
public:
	Offering();
	~Offering();
	bool Start();
	void Update();
	void Rotation();
	void Render(RenderContext&rc);

	PhysicsStaticObject* m_physicsStaticObject;
	CollisionObject* m_collisionObject;
	ModelRender* m_modelRender = nullptr;
	Vector3 m_position = Vector3::Zero;
	Quaternion m_rotation = Quaternion::Identity;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
};

