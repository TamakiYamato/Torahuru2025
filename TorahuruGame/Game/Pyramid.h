#pragma once
class Game;
class Player;
class SecondFloor;
class BackGroundTwo;
class Loading;
class Enemy;
class ThirdFloor;
class Enemy;

class Pyramid:public IGameObject
{
public:
	Pyramid();
	~Pyramid();

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);
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
	}
private:
	PhysicsStaticObject			m_physicsStaticObject;
	ModelRender m_modelRender;
	Player* m_player = nullptr;
	CollisionObject* m_collisionObject = nullptr;//当たり判定
	Quaternion     m_rotation;
	int			moveState = 0;		//荳翫↓遘ｻ蜍輔°荳九↓遘ｻ蜍・
	SecondFloor* m_secondfloor = nullptr;
	ThirdFloor* m_thirdfloor = nullptr;
	Enemy* m_enemy = nullptr;
	Vector3						m_scale;
	Vector3						m_position;
};

