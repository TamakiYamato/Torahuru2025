#pragma once
class BackGround;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class FloorManager;
class FireGimmic;
class Stairs;

class ThirdFloor : IGameObject
{
public:
	ThirdFloor() {};
	~ThirdFloor() {};

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	LevelRender	m_levelRender;						//レベル
	BackGround* m_background = nullptr;
	FloorManager* m_floorManager;					//特殊床の管理
	ReverseFloor* m_reverseFloor;				    //あべこべ床
	SlowFloor* m_slowFloor;						    //鈍足床
	BlindFloor* m_blindFloor;						//視界制限床
	FireGimmic* m_fireGimmic = nullptr;				//火炎放射器
	Stairs* m_stairs;
};

