#pragma once

//class Enemy;
class GameClear;
class Staier;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Anim() {};
	void Rotation();
	void StateManagement();
	void ManageState();						//繧ｹ繝・・繝育ｮ｡逅・・
	void SutaminaCalk();
	void PlayAnimation();					//繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ蜀咲函縲・

	// 蠎ｧ讓吶ｒ蜿門ｾ・
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// 繝励Ξ繧､繝､繝ｼ縺梧ｭｻ莠｡縺励※縺・ｋ・・
	const bool isPlayerDead() const
	{
		return m_hp <= 0;
	}

	//繧ｭ繝｣繝ｩ繧ｳ繝ｳ縺ｮ蜿門ｾ・
	CharacterController& GetCharacterController()
	{
		return m_charCon;
	}

	enum Move {
		State_Idle,					// 蠕・ｩ溘・
		State_Walk,					// 豁ｩ縺上・
		State_Run,					// 襍ｰ繧九・
		State_Crouch,				// 縺励ｃ縺後・縲・
		State_Crouching,			// 縺励ｃ縺後∩縺薙・縲・
		State_CrouchStanding,		// 遶九■荳翫′繧九・
		State_CrouchWalk,			// 縺励ｃ縺後∩豁ｩ縺阪・
		State_StayRun		     	// 縺励ｃ縺後∩豁ｩ縺阪・
	};

	enum EnAnimationClip {
		enAnimClip_Idle,			// 蠕・ｩ溘・
		enAnimClip_Walk,			// 豁ｩ縺・
		enAnimClip_Run,				// 襍ｰ繧九・
		enAnimClip_Crouch,			// 縺励ｃ縺後・縲・
		enAnimClip_Crouching,		// 縺励ｃ縺後∩縺薙・縲・
		enAnimClip_CrouchStanding,	// 遶九■荳翫′繧九・
		enAnimClip_CrouchWalk,		// 縺励ｃ縺後∩豁ｩ縺阪・
		enAnimClip_Jump,			// 繧ｸ繝｣繝ｳ繝・
		enAnimationClip_Num
	};


	//繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・騾壼喧縺吶ｋ縲・
	void SetAnimation(EnAnimationClip animationClip, std::string animationFileName, bool loopFlag);

	AnimationClip				m_animationClips[enAnimationClip_Num];
	CharacterController			m_charCon;							//繧ｭ繝｣繝ｩ繧ｳ繝ｳ
	ModelRender					m_modelRender;
	Vector3						stickL;								//繝励Ξ繧､繝､繝ｼ縺ｮ騾ｲ陦梧婿蜷代ｒ豎ｺ螳壹☆繧九・
	Vector3						m_position;
	Vector3						m_moveSpeed;						//遘ｻ蜍暮溷ｺｦ
	Vector3						m_dash;	
	float						m_hp = 0;
	float						m_max_sutamina = 100;               // 繧ｹ繧ｿ繝溘リ縺ｮ譛螟ｧ蛟､縲・
	float						m_sutamina = m_max_sutamina;    	// 迴ｾ蝨ｨ縺ｮ繧ｹ繧ｿ繝溘リ縲・
	bool						m_dashFlag = false;                 // 襍ｰ繧雁愛螳壹・
	//Move						m_currentState = State_Idle;
	Quaternion					rotation;
	float				    	m_moveDir		= 1.0f;
	int m_currentState;
private:
};