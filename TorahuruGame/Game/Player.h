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
	//ステート管理。
	void ManageState();
	//アニメーションの再生。
	void PlayAnimation();
	// 座標を取得
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// プレイヤーが死亡している？
	const bool isPlayerDead() const
	{
		return m_hp <= 0;
	}

	CharacterController& GetCharacterController()
	{
		return m_charCon;
	}

	enum PlayerState {
		State_Idle,// 待機。
		State_Walk,// 歩く。
		State_Run,// 走る。
		State_Crouch,// しゃがむ。
		State_Crouching,// しゃがみこむ。
		State_CrouchStanding,// 立ち上がる。
		State_CrouchWalk// しゃがみ歩き。
	};

	enum EnAnimationClip {
		enAnimClip_Idle,// 待機。
		enAnimClip_Walk,// 歩く
		enAnimClip_Run,// 走る。
		enAnimClip_Crouch,// しゃがむ。
		enAnimClip_Crouching,// しゃがみこむ。
		enAnimClip_CrouchStanding,// 立ち上がる。
		enAnimClip_CrouchWalk,// しゃがみ歩き。
		enAnimClip_Jump,
		enAnimationClip_Num
	};

	//アニメーションを共通化する。
	void SetAnimation(EnAnimationClip animationClip, std::string animationFileName, bool loopFlag);

	AnimationClip			m_animationClips[enAnimationClip_Num];
	CharacterController		m_charCon;//キャラコン
	ReverseFloor*			m_reverseFloor;
	SlowFloor*				m_slowFloor;
	BlindFloor*				m_blindFloor;
	ModelRender				m_modelRender;
	Vector3					m_position;
	Vector3					m_moveSpeed;//移動速度
	Vector3					m_dash;
	PlayerState				m_playerState = State_Idle;
	Quaternion				rotation;

	//int m_playerState;//歩くプログラム
	int						m_hp = 0;
	//int StairsCount=0 ;//Stairs=階段のカウント


private:
};