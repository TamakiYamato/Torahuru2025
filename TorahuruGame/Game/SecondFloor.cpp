#include "stdafx.h"
#include "SecondFloor.h"
#include "BackGroundTwo.h"
#include "Player.h"
#include "RotationFloor.h"
#include "Loading.h"
#include"Enemy.h"
#include"FirstFloor.h"
#include"EnemyAnimation.h"
SecondFloor::SecondFloor()
{

}

SecondFloor::~SecondFloor()
{	

}

bool SecondFloor::Start()
{
	
	m_player = FindGO<Player>("player");
	if (m_player == nullptr) {
		m_player = NewGO<Player>(0, "player");
	}
	m_enemy = FindGO<Enemy>("enemy");
	m_enemyAnimation = FindGO<EnemyAnimation>("enemyAnimation");
	//プレイヤーの取得
	////レベル実装
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
		});

	return true;
}

void SecondFloor::Update()
{
	//m_firstFloor->Refresh();	//前のフロアをリセット
	m_loading = FindGO<Loading>("loading");
	m_loading->StartLoading();
}

void SecondFloor::Render(RenderContext& rc)
{
	//レベルの描画
	m_levelRender.Draw(rc);
}
