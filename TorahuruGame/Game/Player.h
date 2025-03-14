#pragma once

//class Enemy;
class Player :public IGameObject
{

public:
	Player(); ~Player();
	bool Start();
	void Update();
	Player* player;
	void Render(RenderContext& rc);
	void Move();
	void Anim() {};
	void Rotation();
	int sumahoCount = 0;//すまほのカウント
	//ステート管理。
	void ManageState();
	//アニメーションの再生。
	void PlayAnimation();
	ModelRender m_modelRender;
	Vector3 m_position;//すまほ

	int ClearCount = 0;
	enum EnAnimationClip {
		enAnimClip_Run,
		enAnimClip_Idle,//歩く
		enAnimClip_Jump,
		//走る。
		enAnimationClip_Num,

	};
	CharacterController characterController;//キャラコン
	Vector3 moveSpeed;//移動速度
	AnimationClip m_animationClips[enAnimationClip_Num];
	int m_playerState;//歩くプログラム
	Quaternion rotation;
private:
	//Enemy* m_enemy = nullptr;
};



