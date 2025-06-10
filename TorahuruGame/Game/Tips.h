#pragma once
class Tips : public IGameObject
{
public:
	Tips();
	~Tips();
	bool Start();
	void Update();
	void SetTime();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	std::vector<std::wstring> tipsList;
	int m_currentTipsIndex;
	float m_tipTimer = 0.0f;
	FontRender m_fontRender;
};

