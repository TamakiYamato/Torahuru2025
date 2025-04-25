#pragma once

class Tutorial : public IGameObject
{
public:
	Tutorial();
	~Tutorial();
	bool Start();
	void HintText();
	void Update();
	void Render(RenderContext& rc);

	enum TextState {
		State_Normal,    // 何も指してない状態。
		State_Fire,      // 火炎放射器。
		State_Reverse,   // あべこべ床。
		State_Slow,      // 鈍足床。
		State_Blind      // 視界制限床。
	};

	// メンバ変数。
	Vector3                    m_position;                   // モデルの位置。
	
	ModelRender			       m_modelRender;                // モデルレンダー。
private:
	// メンバ変数。
	TextState                  m_text = State_Normal;        // 状態。
	ReverseFloor*              m_reverseFloor;               // あべこべ床。
	SlowFloor*                 m_slowFloor;                  // 鈍足床。
	BlindFloor*                m_BlindFloor;                 // 視界制限床。
	SpriteRender               m_spriteRender;               // スプライトレンダー。
	FontRender                 m_fontRender;                 // フォントレンダー。
};
