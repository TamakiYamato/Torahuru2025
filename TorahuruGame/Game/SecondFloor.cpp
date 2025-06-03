#include "stdafx.h"
#include "SecondFloor.h"
#include "BackGroundTwo.h"
#include "Player.h"
#include "RotationFloor.h"
#include "Loading.h"
SecondFloor::SecondFloor()
{
}

SecondFloor::~SecondFloor()
{	
}

bool SecondFloor::Start()
{
	//auto loading = FindGO<Loading>("loading");
	//if (loading) {
	//	DeleteGO(loading);	//ローディング画面の削除
	//}
	//m_loading = NewGO<Loading>(0, "loading"); // ローディング画面の生成
	m_player = FindGO<Player>("player");	//プレイヤーの取得
	////レベル実装
	m_levelRender.Init("Assets/level/BackGround2.tkl", [&](LevelObjectData& objData) {	//floor1の実装
		if (objData.ForwardMatchName(L"Stage2two") == true) {								//ステージ
			BackGroundTwo* backgroundTwo = NewGO<BackGroundTwo>(0, "Stage2two");
			backgroundTwo->SetPosition(objData.position);
			backgroundTwo->SetScale(objData.scale);
			return true;
		}

		else if (objData.ForwardMatchName(L"Ch01_nonPBR") == true) {
			
			m_player->SetPosition(objData.position);
			return true; 
		}
		else if (objData.ForwardMatchName(L"kaitenyuka") == true) {
			RotationFloor* rotationfloor = NewGO<RotationFloor>(0, "rotationfloor");
			rotationfloor->SetPosition(objData.position);
			rotationfloor->SetScale(objData.scale);
			/*rotationfloor->SetRotation(objData.rotation);*/
			return true;
		}
		
		});


	// --- ローディング画面を消す ---
	//auto loading = FindGO<Loading>("loading");
	/*if (loading) {
		DeleteGO(loading);
	}*/

	return true;
}

void SecondFloor::Update()
{	
	m_loading = FindGO<Loading>("loading");
	m_loading->StartLoading();
}

void SecondFloor::Render(RenderContext& rc)
{
	//レベルの描画
	m_levelRender.Draw(rc);
}
