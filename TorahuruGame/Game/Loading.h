#pragma once

class Loading : public IGameObject
{
public:
	Loading();
	~Loading();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	// フェードイン。
	void StartLoading()
	{
		m_state = enState_LoadIn;
	}

	// フェードアウト
	void StartLoadOut()
	{
		m_state = enState_LoadOut;
	}
	// フェード中。
	const bool IsLoading() const
	{
		return m_state != enState_Idle;
	}
	// α値を取得。
	const float GetCurrentAlpha() const
	{
		return m_currentAlpha;
	}

private:
	enum EnState {
		enState_LoadIn,			//フェードイン中。
		enState_LoadOut,		//フェードアウト中。
		enState_Idle,			//アイドル中。
	};
	SpriteRender		m_spriteRender;
	EnState				m_state = enState_Idle;
	float				m_currentAlpha = 0.0f;
};