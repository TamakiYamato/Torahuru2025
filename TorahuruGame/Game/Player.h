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
	int sumahoCount = 0;//���܂ق̃J�E���g
	//�X�e�[�g�Ǘ��B
	void ManageState();
	//�A�j���[�V�����̍Đ��B
	void PlayAnimation();
	ModelRender m_modelRender;
	Vector3 m_position;//���܂�

	int ClearCount = 0;
	enum EnAnimationClip {
		enAnimClip_Run,
		enAnimClip_Idle,//����
		enAnimClip_Jump,
		//����B
		enAnimationClip_Num,

	};
	CharacterController characterController;//�L�����R��
	Vector3 moveSpeed;//�ړ����x
	AnimationClip m_animationClips[enAnimationClip_Num];
	int m_playerState;//�����v���O����
	Quaternion rotation;
private:
	//Enemy* m_enemy = nullptr;
};



