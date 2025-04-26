#pragma once
// 縺ｰ縺ｭ繧ｫ繝｡繝ｩ繧剃ｽｿ逕ｨ縺励◆縺・ｴ蜷医・ SpringCamera繧偵う繝ｳ繧ｯ繝ｫ繝ｼ繝峨☆繧九・
#include "camera/SpringCamera.h"

// 繧ｯ繝ｩ繧ｹ螳｣險縲・
class Player;

class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	Player* m_player;
	SpringCamera m_springCamera;   // 繝舌ロ繧ｫ繝｡繝ｩ縲・

	Vector3 m_toCameraPos;
};





