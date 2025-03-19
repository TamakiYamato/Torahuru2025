#include "stdafx.h"
#include "Player.h"
#include"Game.h"

Player::Player() {

}

Player::~Player()
{

}

bool Player:: Start()
{
	// �ҋ@�A�j���[�V����
	m_animationClips[enAnimClip_Idle].Load("Assets/animData/player/playerIdle.tka");
	m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	// �����A�j���[�V�����B
	m_animationClips[enAnimClip_Walk].Load("Assets/animData/player/playerWalking.tka");
	m_animationClips[enAnimClip_Walk].SetLoopFlag(true);
	// ����A�j���[�V�����B
	m_animationClips[enAnimClip_Run].Load("Assets/animData/player/playerRunning.tka");
	m_animationClips[enAnimClip_Run].SetLoopFlag(true);
	// ���Ⴊ�݃A�j���[�V�����B
	m_animationClips[enAnimClip_Crouch].Load("Assets/animData/player/playerCrouch.tka");
	m_animationClips[enAnimClip_Crouch].SetLoopFlag(true);
	// ���Ⴊ�ݕ����A�j���[�V�����B
	m_animationClips[enAnimClip_CrouchWalk].Load("Assets/animData/player/playerCrouched walking.tka");
	m_animationClips[enAnimClip_CrouchWalk].SetLoopFlag(true);
	// ���Ⴊ�݂��݃A�j���[�V�����B
	m_animationClips[enAnimClip_Crouching].Load("Assets/animData/player/playerCrouching.tka");
	m_animationClips[enAnimClip_Crouching].SetLoopFlag(false);
	// �����オ��A�j���[�V�����B
	m_animationClips[enAnimClip_CrouchStanding].Load("Assets/animData/player/playerCrouch Standing.tka");
	m_animationClips[enAnimClip_CrouchStanding].SetLoopFlag(false);

	/*m_animationClips[enAnimClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimClip_Jump].SetLoopFlag(false);*/
	// �L�����N�^�[��ǂݍ��ށB
	//m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);//�O��ނ̃A�j���[�V����:m_animationClips=����ނ��邩
	m_modelRender.Init("Assets/modelData/player/player.tkm", m_animationClips, enAnimationClip_Num);
	// �L�����N�^�[�̍X�V�B
	m_modelRender.Update();
	// �L�����N�^�[�̌�����ς���B
	rotation.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(rotation);
	//�L�����N�^�[�R���g���[���[������������
	characterController.Init(25.0f, 75.0f, m_position);

	return true;
}

void Player::Update() {
	Move();//�L�����N�^�[�̈ړ�
	Rotation();//�L�����N�^�[�̉�]
	//Anim();
	//�X�e�[�g�Ǘ��B
	ManageState();
	//�A�j���[�V�����̍Đ��B
	PlayAnimation();
	m_modelRender.Update();//���f���X�V
}

void Player::Move() {
	// ��Z�p
	float m_dash = 1.0f;
	// ����A�{�^���������ꂽ��B
	if (g_pad[0]->IsPress(enButtonA))
	{
		// �ړ����x���グ��B
		m_dash *= 2.0f;
	}
	// ����B�{�^���������ꂽ��B
	if (g_pad[0]->IsPress(enButtonB))
	{
		m_dash /= 2.0f;
	}

	// xz�̈ړ����x��0.0f�ɂ���B
	// 0.0f�ŏ��������邱�ƂőO��̈ړ����x�̉e����
	// �󂯂��ɐV�������͂Ɋ�Â����ړ����\�B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	//�v���C���[�̐i�s���������肷��B
	Vector3 stickL;
	//�X�e�B�b�N�̐��������B
	stickL.x = g_pad[0]->GetLStickXF();
	//�X�e�B�b�N�̐��������B
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	//�v���C���[���ǂ̕����Ɉړ����邩�����߂�B
	//�J�����̑O�����̃x�N�g�����擾�B
	Vector3 forward = g_camera3D->GetForward();
	//�J�����̉E�����̃x�N�g�����擾�B
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ��B
	//�������邱�ƂŃv���C���[�͒n�ʏ�ł݈̂ړ�����B
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�120.0f��
	// ��Z�B
	//�ړ����x�����߂�B
	right *= stickL.x * 180.0f * m_dash;
	forward *= stickL.y * 180.0f * m_dash;

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	// m_run���_�b�V�����p�̕ϐ��B
	m_moveSpeed += right + forward;

	//�n�ʂɕt���Ă�����B
	if (characterController.IsOnGround())
	{
		//�d�͂𖳂����B
		m_moveSpeed.y = 0.0f;
		//A�{�^���������ꂽ��B
		//if (g_pad[0]->IsTrigger(enButtonA))
		//{
		//	//�W�����v������B
		//	moveSpeed.y = 250.0f;
		//}
	}
	//�n�ʂɕt���Ă��Ȃ�������B
	else
	{
		//�d�͂𔭐�������B
		m_moveSpeed.y -= 5.0f;
	}
	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	m_position = characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
	//�G�`������ɍ��W��������B
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//�G�`������ɉ�]��������B
		m_modelRender.SetRotation(rotation);
	}
}

//�X�e�[�g�Ǘ��B
void Player::ManageState()
{
	//�n�ʂɕt���Ă��Ȃ�������B
	if (characterController.IsOnGround() == false)
	{
		//�X�e�[�g��1(�W�����v��)�ɂ���B
		m_playerState = 1;
		//������ManageState�̏������I��点��B
		return;
	}

	//�n�ʂɕt���Ă�����B
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�X�e�[�g��2(����)�ɂ���B
		m_playerState = State_Walk;

		// ����A�{�^���������ꂽ��B
		if (g_pad[0]->IsPress(enButtonA))
		{
			// ����B
			m_playerState = State_Run;
		}
		// ����B�{�^���������ꂽ��B
		else if (g_pad[0]->IsPress(enButtonB))
		{
			// ���Ⴊ�ށB
			m_playerState = State_CrouchWalk;
		}
	}
	//x��z�̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B
	else
	{
		//�X�e�[�g��0(�ҋ@)�ɂ���B
		m_playerState = State_Idle;

		// ����B�{�^���������ꂽ��B
	    if (g_pad[0]->IsPress(enButtonB))
	    {
		    // ���Ⴊ�ށB
		    m_playerState = State_Crouch;
	    }
	}
}

//�A�j���[�V�����̍Đ��B
void Player::PlayAnimation()
{
	//switch���B
	switch (m_playerState) {
		// �X�e�[�g��Idle��������B
	case State_Idle:
		//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimClip_Idle);
		break;
		// �X�e�[�g��Walk��������B
	case State_Walk:
		//�����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimClip_Walk);
		break;
		// �X�e�[�g��Run��������B
	case State_Run:
		// ����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimClip_Run);
		break;
		// �X�e�[�g��Crouch��������B
	case State_Crouch:
		// ���Ⴊ�݃A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimClip_Crouch);
		break;
		// �X�e�[�g��CrouchWalk��������B
	case State_CrouchWalk:
		// ���Ⴊ�ݕ����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimClip_CrouchWalk);
		break;
		// �X�e�[�g��Crouching��������B
	case State_Crouching:
		// ���Ⴊ�݂��݃A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimClip_Crouching);
		break;
		// �X�e�[�g��CrouchStanding��������B
	case State_CrouchStanding:
		// �����オ��A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimClip_CrouchStanding);
		break;
	}
}

void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}