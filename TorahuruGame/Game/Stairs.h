#pragma once
class Game;
class Player;
class GameClear;
class Title;
class Stairs :public IGameObject
{
public:
	Stairs();
	~Stairs();
	bool Start() ;
	void Update() ;
	void Render(RenderContext& renderContext);
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
	PhysicsStaticObject			m_physicsStaticObject;
	ModelRender m_modelRender;
	Player*		m_player = nullptr;
	CollisionObject* m_collisionObject = nullptr;//当たり判定
	Quaternion     m_rotation;
	int			moveState = 0;		//荳翫↓遘ｻ蜍輔°荳九↓遘ｻ蜍・

	Vector3						m_scale;
	Vector3						m_position ;
	

};

