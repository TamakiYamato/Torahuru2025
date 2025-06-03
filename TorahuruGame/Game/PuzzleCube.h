#pragma once
class PuzzleCube : IGameObject
{
public:
	PuzzleCube();
	~PuzzleCube();
	bool Start();

	ModelRender m_modelRender;

	FontRender m_fontRender;
};

