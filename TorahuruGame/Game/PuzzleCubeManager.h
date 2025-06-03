#pragma once
class PuzzleCube;
class PuzzleCubeManager : IGameObject
{
public:
	PuzzleCubeManager();
	~PuzzleCubeManager();

	bool Start();
	void Update();
	void Rotation();
	void Render(RenderContext& rc);
};

