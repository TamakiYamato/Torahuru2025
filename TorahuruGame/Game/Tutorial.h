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
		State_Normal,    // 菴輔ｂ謖・＠縺ｦ縺ｪ縺・憾諷九・
		State_Fire,      // 轣ｫ轤取叛蟆・勣縲・
		State_Reverse,   // 縺ゅ∋縺薙∋蠎翫・
		State_Slow,      // 驤崎ｶｳ蠎翫・
		State_Blind      // 隕也阜蛻ｶ髯仙ｺ翫・
	};

	// 繝｡繝ｳ繝仙､画焚縲・
	Vector3                    m_position;                   // 繝｢繝・Ν縺ｮ菴咲ｽｮ縲・
	
	ModelRender			       m_modelRender;                // 繝｢繝・Ν繝ｬ繝ｳ繝繝ｼ縲・
private:
	// 繝｡繝ｳ繝仙､画焚縲・
	TextState                  m_text = State_Normal;        // 迥ｶ諷九・
	ReverseFloor*              m_reverseFloor;               // 縺ゅ∋縺薙∋蠎翫・
	SlowFloor*                 m_slowFloor;                  // 驤崎ｶｳ蠎翫・
	BlindFloor*                m_BlindFloor;                 // 隕也阜蛻ｶ髯仙ｺ翫・
	SpriteRender               m_spriteRender;               // 繧ｹ繝励Λ繧､繝医Ξ繝ｳ繝繝ｼ縲・
	FontRender                 m_fontRender;                 // 繝輔か繝ｳ繝医Ξ繝ｳ繝繝ｼ縲・
};
