#pragma once
class Game;
class Player;
class GameClear;
class Stairs :public IGameObject
{
public:
	Stairs();
	~Stairs();
	bool Start() ;
	void Update() ;
	void Render(RenderContext& renderContext);
	ModelRender m_modelRender;
	Vector3 m_position;
	int moveState = 0; //ã‚ÉˆÚ“®‚©‰º‚ÉˆÚ“®
};

