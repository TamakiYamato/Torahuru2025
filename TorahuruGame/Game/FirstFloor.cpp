#include "stdafx.h"
#include "FirstFloor.h"
#include "BackGround.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "FloorManager.h"
#include "FireGimmic.h"
#include "Stairs.h"


FirstFloor::FirstFloor()
{
}

FirstFloor::~FirstFloor()
{
}

bool FirstFloor::Start()
{
	m_floorManager = NewGO<FloorManager>(0, "floorManager");

	//レベル実装
	m_levelRender.Init("Assets/level/BackGround1.tkl", [&](LevelObjectData& objData)
		{	//floor1の実装
			if (objData.ForwardMatchName(L"Box") == true) {								//ステージ
				m_background = NewGO<BackGround>(0, "Box");
				m_background->SetPosition(objData.position);
				m_background->SetScale(objData.scale);
				return true;
			}
			if (objData.ForwardMatchName(L"ReverseFloor") == true) {					//あべこべ床
				m_reverseFloor = NewGO<ReverseFloor>(0, "ReverseFloor");
				m_reverseFloor->SetPosition(objData.position);
				m_reverseFloor->SetScale(objData.scale);
				return true;
			}
			if (objData.ForwardMatchName(L"SlowFloor") == true) {						//鈍足床
				m_slowFloor = NewGO<SlowFloor>(0, "SlowFloor");
				m_slowFloor->SetPosition(objData.position);
				m_slowFloor->SetScale(objData.scale);
				return true;
			}
			if (objData.ForwardMatchName(L"BlindFloor") == true) {						//視界制限床
				m_blindFloor = NewGO<BlindFloor>(0, "BlindFloor");
				m_blindFloor->SetPosition(objData.position);
				m_blindFloor->SetScale(objData.scale);
				return true;
			}
			if (objData.ForwardMatchName(L"FireGimmic") == true) {
				m_fireGimmic = NewGO<FireGimmic>(0, "firegimmic");                      //火炎放射器
				m_fireGimmic->SetPosition(objData.position);
				m_fireGimmic->SetScale(objData.scale);
				m_fireGimmic->SetRotation(objData.rotation);
				return true;
			}
			if (objData.ForwardMatchName(L"Stairs") == true) {
				m_stairs = NewGO<Stairs>(0, "stairs");
				m_stairs->SetPosition(objData.position);
				m_stairs->SetScale(objData.scale);
				m_stairs->SetRotation(objData.rotation);
			}

	});

	return true;
}
	
void FirstFloor::Update()
{
}

void FirstFloor::Render(RenderContext& rc)
{
	//レベルの描画
	m_levelRender.Draw(rc);
}

