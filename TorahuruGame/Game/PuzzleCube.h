#pragma once
class ThirdFloor;
class PuzzleCube : public IGameObject
{
public:
	PuzzleCube();
	~PuzzleCube();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void SetPosition(const Vector3& position)

	{
		m_position = position;
	}
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_scale = Vector3::One;
	FontRender m_fontRender;
};

