#pragma once
class Game;
class Player;
class GameClear;
class kaidan:public IGameObject
{
public:
	kaidan();
	~kaidan();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc);
	ModelRender				m_modelRender;				//モデルレンダラー。
	Vector3	                m_position;					//座標。
	Vector3					m_scale;					//大きさ。
	Quaternion				m_rotation;					//回転。
	PhysicsStaticObject		m_physicsStaticObject;		//静的物理オブジェクト。
	Player* m_player;
	Game* m_game;

	Vector3					m_defPosition;
	SpriteRender m_spriteRender;
	
};



