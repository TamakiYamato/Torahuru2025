#include "stdafx.h"
#include "SecondFloor.h"
#include "BackGroundTwo.h"
#include "Player.h"
#include "RotationFloor.h"
#include "Loading.h"
#include "Game.h"
#include"Enemy.h"
#include"FirstFloor.h"
#include"PuzzleCube.h"
#include"EnemyAnimation.h"
#include"BlindFloor.h"
#include"ReverseFloor.h"
#include"SlowFloor.h"
#include"GameCamera.h"
#include"TutorialUI.h"
#include "GameClear.h"

SecondFloor::SecondFloor()
{

}

SecondFloor::~SecondFloor()
{	
	DeleteGO(m_player);
	DeleteGO(m_enemy);
	DeleteGO(m_enemyAnimation);
	DeleteGO(m_tutorialUI);
	DeleteGO(m_collisitonObject);
	for (ReverseFloor* reverseFloor : m_reverseFloorList) {
		DeleteGO(reverseFloor);
	}
	for (SlowFloor* slowFloor : m_slowFloorList) {
		DeleteGO(slowFloor);
	}
	for (BlindFloor* blindFloor : m_blindFloorList) {
		DeleteGO(blindFloor);
	}
	
}

bool SecondFloor::Start()
{
	m_player = FindGO<Player>("player");
	if (m_player == nullptr) {
		m_player = NewGO<Player>(0, "player");
	}
	m_enemy = FindGO<Enemy>("enemy");
	m_enemyAnimation = FindGO<EnemyAnimation>("enemyAnimation");
	// 絵合わせギミックを探す。
	if (m_puzzleCube == nullptr) {
		m_puzzleCube = FindGO<PuzzleCube>("PuzzleCube");
	}
	
	m_player->m_playerTouchFlag = true;	//プレイヤーがfloor2についたかどうかのフラグをtrueにする
	//プレイヤーの取得
	////レベル実装
	////当たり判定の可視化
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	m_levelRender.Init("Assets/level/BackGround2second.tkl", [&](LevelObjectData& objData) {	//floor1の実装
		if (objData.ForwardMatchName(L"Stage2second") == true) {								//ステージ
			BackGroundTwo* backgroundTwo = NewGO<BackGroundTwo>(0, "backgroundtwo");
			backgroundTwo->SetPosition(objData.position);
			backgroundTwo->SetScale(objData.scale);
			return true;
		}

		else if (objData.ForwardMatchName(L"Ch01_nonPBR") == true) {
			
			m_player->SetPosition(objData.position);
			return true; 
		}
		else if (objData.ForwardMatchName(L"kaitenyukasecond") == true) {
			RotationFloor* rotationfloor = NewGO<RotationFloor>(0, "rotationfloor");
			rotationfloor->SetPosition(objData.position);
			rotationfloor->SetScale(objData.scale);
			return true;
		}
		else if (objData.ForwardMatchName(L"Ch24_nonPBR") == true) {
			Enemy* m_enemy = NewGO<Enemy>(0, "enemy");
			m_enemy->SetPosition(objData.position);
			m_enemy->SetRotation(objData.rotation);
			m_enemy->SetScale(objData.scale);
			m_enemy->SetAnimation(m_enemyAnimation);
			return true;
		}
		

		else if (objData.ForwardMatchName(L"BlindFloor") == true) {						//視界制限床
			BlindFloor* blindfloor = NewGO<BlindFloor>(0, "BlindFloor");
			m_blindFloorList.push_back(blindfloor);
			blindfloor->SetPosition(objData.position);
			blindfloor->SetScale(objData.scale);
			return true;
		}
		else if (objData.ForwardMatchName(L"SlowFloor") == true) {						//鈍足床
			SlowFloor* slowfloor = NewGO<SlowFloor>(0, "SlowFloor");
			m_slowFloorList.push_back(slowfloor);
			slowfloor->SetPosition(objData.position);
			slowfloor->SetScale(objData.scale);
			return true;
		}
		else if (objData.ForwardMatchName(L"ReverseFloor") == true) {					//あべこべ床
			ReverseFloor* reverseFloor = NewGO<ReverseFloor>(0, "ReverseFloor");
			m_reverseFloorList.push_back(reverseFloor);
			reverseFloor->SetPosition(objData.position);
			reverseFloor->SetScale(objData.scale);
			return true;
		}



		});

	m_puzzleCube = NewGO<PuzzleCube>(0, "puzzleCube");

	return true;
}

void SecondFloor::Update()
{

} 


void SecondFloor::SetPosition() {
	m_player->SetPosition(Vector3(0.0f, 0.0f, 0.0f)); // プレイヤーの位置をリセット
}
void SecondFloor::Render(RenderContext& rc)
{
	//レベルの描画
	m_levelRender.Draw(rc);
}