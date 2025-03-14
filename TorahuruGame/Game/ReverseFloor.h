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

	CollisionObject* m_collisionObject = nullptr;
	Player* m_player;

	bool GimmikFlag = false;
};


