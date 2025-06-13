#pragma once
class FirstFloor;
class SecondFloor;
class ThirdFloor;
class Game;

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
		if (m_matizikan > 0.0f)
		{
			return;
		}

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

	bool IsFadeOutEnd()
	{
		return m_isstate;
	}

	bool IsFadeInEnd()
	{
		return m_state == enState_Idle && m_currentAlpha >= 1.0f;
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
	bool 			m_isstate = false;
	float 			m_matizikan = 0.0f; // フェード時間。
	
};