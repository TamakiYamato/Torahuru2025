#pragma once
class ThirdFloor;
class Player;
class GameClear;
class SecondFloor;
class PuzzleCube : public IGameObject
{
public:
	PuzzleCube();
	~PuzzleCube();
	bool Start();
	void Rotation();
	void SetRotation();
	bool SetClear()const;
	void SetUI();
	void SetText();
	void Update();
	void Render(RenderContext& rc);

	// 追加: Y軸回転角度（度数法）
	float m_rotationY = 0.0f;
	float m_rotation2Y = 0.0f;
	float m_rotation3Y = 0.0f;

	// 追加: 回転角度の取得・設定
	float GetRotationY() const { return m_rotationY; }
	void SetRotationY(float deg) { m_rotationY = deg; }

	bool m_clear = false;
	bool m_uiFlag = false;
	bool m_rotationFlag = false;

private:
	Player* m_player;
	//GameClear m_gameClear;
	// ブロック部分のモデルレンダラー。
	ModelRender m_cubeRender;
	ModelRender m_cubeRender2;
	ModelRender m_cubeRender3;
	// 土台部分のモデルレンダラー。
	ModelRender m_pedestalRender;
	ModelRender m_pedestalRender2;
	ModelRender m_pedestalRender3;
	SpriteRender m_spriteRender;
	FontRender m_fomtRender;
	Vector3 m_position;
	float m_posi = 0.0f;
	float m_posi2 = 0.0f;
	float m_posi3 = 0.0f;
	float i = 0.0f;
	FontRender m_fontRender;
	Vector3 m_scale;
	Quaternion m_rotation;
	Quaternion m_rotation2;
	Quaternion m_rotation3;
	PhysicsStaticObject m_physicsStaticObject;
	PhysicsStaticObject m_physicsStaticObject2;
	PhysicsStaticObject m_physicsStaticObject3;

	CollisionObject m_collisionObject;

	BoxCollider m_boxCollider;	
	RigidBody m_rigidBody;

};

