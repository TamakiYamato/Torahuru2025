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
	//�X�e�[�g�Ǘ��B
	void ManageState();
	//�A�j���[�V�����̍Đ��B
	void PlayAnimation();

	enum EnAnimationClip {
		enAnimClip_Idle,// �ҋ@�B
		enAnimClip_Walk,// ����
		enAnimClip_Run,// ����B
		enAnimClip_Crouch,// ���Ⴊ�ށB
		enAnimClip_Crouching,// ���Ⴊ�݂��ށB
		enAnimClip_CrouchStanding,// �����オ��B
		enAnimClip_CrouchWalk,// ���Ⴊ�ݕ����B
		enAnimClip_Jump,
		enAnimationClip_Num,
	};

	CharacterController characterController;//�L�����R��
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 moveSpeed;//�ړ����x
	AnimationClip m_animationClips[enAnimationClip_Num];
	int m_playerState;//�����v���O����
	Quaternion rotation;

private:
	//Enemy* m_enemy = nullptr;
};



