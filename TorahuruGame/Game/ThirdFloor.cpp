#include "stdafx.h"
#include "Player.h"
#include "Loading.h"
#include "ThirdFloor.h"
#include "BackGround.h"
#include "BackGroundThree.h"
#include "PuzzleCube.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "FloorManager.h"
#include "FireGimmic.h"
#include "Stairs.h"

ThirdFloor::ThirdFloor()
{

}

ThirdFloor::~ThirdFloor()
{

}

bool ThirdFloor::Start()
{
	
    m_player = FindGO<Player>("player");
    if (m_player == nullptr) {
        m_player = NewGO<Player>(0, "player");
    }
	DeleteGO(m_player); // 既存のプレイヤーを削除して新しいプレイヤーを作成
	////レベル実装
	m_levelRender.Init("Assets/level/testStage3.tkl", [&](LevelObjectData& objData) {	//floor1の実装
		if (objData.ForwardMatchName(L"GameStage3") == true) {								//ステージ
			BackGroundThree* m_backgroundThree = NewGO<BackGroundThree>(0, "backgroundthree");
			m_backgroundThree->SetPosition(objData.position);
			m_backgroundThree->SetScale(objData.scale);
			return true;
		}
		else if (objData.ForwardMatchName(L"Ch01_nonPBR") == true) {
			m_player->SetPosition(objData.position);
			return true;
		}
		/*else if (objData.ForwardMatchName(L"PuzzleCube") == true) {
			PuzzleCube* m_puzzleCube = NewGO<PuzzleCube>(0, "puzzlecube");
			m_puzzleCube->SetPosition(objData.position);
			m_puzzleCube->SetScale(objData.scale);
			return true;
		}*/
		/*else if (objData.ForwardMatchName(L"Ch24_nonPBR") == true) {
			Enemy* m_enemy = NewGO<Enemy>(0, "enemy");
			m_enemy->SetPosition(objData.position);
			m_enemy->SetRotation(objData.rotation);
			m_enemy->SetScale(objData.scale);
			m_enemy->SetAnimation(m_enemyAnimation);
			return true;
		}*/
		});


    return true;
}

void ThirdFloor::Update()
{
	m_loading = FindGO<Loading>("loading");
	m_loading->StartLoading();
}

void ThirdFloor::Render(RenderContext& rc)
{
    //レベルの描画
    m_levelRender.Draw(rc);
}
