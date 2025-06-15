#include "stdafx.h"
#include "SecondFloor.h"
#include "BackGroundTwo.h"
#include "Player.h"
#include "RotationFloor.h"
#include "Loading.h"
#include"Enemy.h"
#include"FirstFloor.h"
#include"PuzzleCube.h"
#include"EnemyAnimation.h"
#include"Pyramid.h"
#include"ThirdFloor.h"
#include "GameClear.h"

SecondFloor::SecondFloor()
{

}

SecondFloor::~SecondFloor()
{	
	DeleteGO(m_player);
	DeleteGO(m_pyramid);
	DeleteGO(m_enemy);
	DeleteGO(m_enemyAnimation);
	DeleteGO(m_loading);
	
	
	
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
	//当たり判定の可視化
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
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
		else if(objData.ForwardMatchName(L"pyramid") == true) {
			m_pyramid = NewGO<Pyramid>(0, "pyramid");
			m_pyramid->SetPosition(objData.position);
			m_pyramid->SetScale(objData.scale);
			return true;
		}
		
		});

	m_puzzleCube = NewGO<PuzzleCube>(0, "puzzleCube");

	return true;
}

void SecondFloor::Update()
{
	if (m_pyramid && m_player) {
		Vector3 playerPos = m_player->GetPosition();
		Vector3 pyramidPos = m_pyramid->GetPosition();
		float distance = (playerPos - pyramidPos).Length();

		if (distance < 100.0f) {
			//先にここで暗くする処理とそれを終わらせる処理
			m_loading = FindGO<Loading>("loading");
			//⇂ここで暗くする処理
			//ここでLoadingを生成して、次のステージに行く処理をする
			if (m_loading) {
				m_loading->StartLoadOut();
			}

			if (m_loading->IsFadeOutEnd() == false)
			{
				return;
			}

			GoToNeoStage();

		}
    }
} // namespace GameEngine2D

void SecondFloor::GoToNeoStage() {
	m_thirdFloor = NewGO<ThirdFloor>(0, "thirdFloor");  // 次のステージを生成

	SetPosition();

	//LoadingとSecondFloorの切り替えを行うコードを書いておく!!
	DeleteGO(this);  // 現在のステージを削除
}

void SecondFloor::SetPosition() {
	m_player->SetPosition(Vector3(0.0f, 0.0f, 0.0f)); // プレイヤーの位置をリセット
}
void SecondFloor::Render(RenderContext& rc)
{
	//レベルの描画
	m_levelRender.Draw(rc);
}