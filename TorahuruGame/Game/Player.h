#pragma once

//class Enemy;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	Player* player;
	void Render(RenderContext& rc);
	void Move();
	void Anim() {};
	void Rotation();
	//ステート管理。
	void ManageState();
	//アニメーションの再生。
	void PlayAnimation();
	int ClearCount=0;//クリアカウント
	enum PlayerState {
		State_Idle,// 待機。
		State_Walk,// 歩く。
		State_Run,// 走る。
		State_Crouch,// しゃがむ。
		State_Crouching,// しゃがみこむ。
		State_CrouchStanding,// 立ち上がる。
		State_CrouchWalk,// しゃがみ歩き。
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
		enAnimationClip_Num,
	};

	CharacterController characterController;//キャラコン
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_moveSpeed;//移動速度
	Vector3 m_dash;
	AnimationClip m_animationClips[enAnimationClip_Num];
	int m_playerState;//歩くプログラム
	Quaternion rotation;

private:
	//Enemy* m_enemy = nullptr;
};