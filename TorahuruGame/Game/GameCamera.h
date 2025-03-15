#pragma once
// �΂˃J�������g�p�������ꍇ�� SpringCamera���C���N���[�h����B
#include "camera/SpringCamera.h"

// �N���X�錾�B
class Player;

class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	Player* m_player;
	Vector3 m_toCameraPos;
	SpringCamera m_springCamera;   // �o�l�J�����B
};





