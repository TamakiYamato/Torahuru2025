#pragma once
// ばねカメラを使用したい場合は SpringCameraをインクルードする。
#include "camera/SpringCamera.h"

// クラス宣言。
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
	SpringCamera m_springCamera;   // バネカメラ。
};





