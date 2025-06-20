#include "stdafx.h"
#include "FirstFloor.h"
#include "BackGround.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "FloorManager.h"
#include "FireGimmic.h"
#include "Stairs.h"
#include"GameClear.h"
#include"Player.h"
#include"SecondFloor.h"
#include"GameCamera.h"
#include"Stamina.h"
#include"Scene.h"
#include"TutorialUI.h"
#include"Loading.h"
#include"FireTriggerFloor.h"
#include "PuzzleCube.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
FirstFloor::FirstFloor()
{

}

FirstFloor::~FirstFloor()
{

	DeleteGO(m_stairs);
	DeleteGO(m_background);
	DeleteGO(m_firstFloor);
	//DeleteGO(m_floorManager);
	DeleteGO(m_fireGimmic);
	DeleteGO(m_tutorialUI);
	DeleteGO(m_stamina);
	DeleteGO(m_collisitonObject);
	DeleteGO(m_fireTriggerFloor);
	
	for(ReverseFloor* reverseFloor : m_reverseFloorList) {
		DeleteGO(reverseFloor);
	}
	for (SlowFloor* slowFloor : m_slowFloorList) {
		DeleteGO(slowFloor);
	}
	for (BlindFloor* blindFloor : m_blindFloorList) {
		DeleteGO(blindFloor);
	}
	for(FireGimmic* fireGimmic : m_fireGimmicList) {
		DeleteGO(fireGimmic);
	}
	for (Stairs* stairs : m_stairsGimmicList) {
		DeleteGO(stairs);
	}
	for(FireTriggerFloor* fireTriggerFloor : m_fireTriggerFloorList) {
		DeleteGO(fireTriggerFloor);
	}
	
}

bool FirstFloor::Start()
{

	m_player = FindGO<Player>("player");
	m_floorManager = NewGO<FloorManager>(0, "floorManager");
	m_gamecamera = FindGO<GameCamera>("gamecamera");

	//レベル実装
	//当たり判定の可視化
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	// 効果音の音源を読み込む。
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/kaidan.wav");
	m_levelRender.Init("Assets/level/BackGround1.tkl", [&](LevelObjectData& objData)
		{	//floor1の実装
			if (objData.ForwardMatchName(L"Box") == true) {								//ステージ
				m_background = NewGO<BackGround>(0, "Box");
				m_background->SetPosition(objData.position);
				m_background->SetScale(objData.scale);
				return true;
			}
			else if (objData.ForwardMatchName(L"ReverseFloor") == true) {					//あべこべ床
				ReverseFloor* reverseFloor = NewGO<ReverseFloor>(0, "ReverseFloor");
				m_reverseFloorList.push_back(reverseFloor);
				reverseFloor->SetPosition(objData.position);
				reverseFloor->SetScale(objData.scale);
				return true;
			}
			else if (objData.ForwardMatchName(L"SlowFloor") == true) {						//鈍足床
				SlowFloor*slowfloor = NewGO<SlowFloor>(0, "SlowFloor");
				m_slowFloorList.push_back(slowfloor);
				slowfloor->SetPosition(objData.position);
				slowfloor->SetScale(objData.scale);
				return true;
			}
			else if (objData.ForwardMatchName(L"BlindFloor") == true) {						//視界制限床
				BlindFloor*blindfloor = NewGO<BlindFloor>(0, "BlindFloor");
				m_blindFloorList.push_back(blindfloor);
				blindfloor->SetPosition(objData.position);
				blindfloor->SetScale(objData.scale);
				return true;
			}
			else if (objData.ForwardMatchName(L"FireGimmic") == true) {
				FireGimmic*fireGimmic = NewGO<FireGimmic>(0, "firegimmic");                      //火炎放射器
				m_fireGimmicList.push_back(fireGimmic);
				fireGimmic->SetPosition(objData.position);
				fireGimmic->SetScale(objData.scale);
				fireGimmic->SetRotation(objData.rotation);
				return true;
			}
			else if (objData.ForwardMatchName(L"Stairs") == true) {
				m_stairs = NewGO<Stairs>(0, "stairs");
				m_stairsGimmicList.push_back(m_stairs);
				m_stairs->SetPosition(objData.position);
				m_stairs->SetScale(objData.scale);
				m_stairs->SetRotation(objData.rotation);
				return true;
			}
			/*else if (objData.ForwardMatchName(L"FireTrigger") == true) {
				m_fireTriggerFloor = NewGO<FireTriggerFloor>(0, "FireTriggerFloor");
				m_fireTriggerFloorList.push_back(m_fireTriggerFloor);
				m_fireTriggerFloor->SetPosition(objData.position);
				m_fireTriggerFloor->SetScale(objData.scale);
				return true;
			}*/
		});

	return true;
}


void FirstFloor::Update()
{
	if (m_stairs  && m_player ) {
		Vector3 playerPos = m_player->GetPosition();
		Vector3 stairsPos = m_stairs->GetPosition();
		float distance = (playerPos - stairsPos).Length();
		
		if (distance < 200.0f) {
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

			GoToNextStage();
			
		}
	}
}

void FirstFloor::GoToNextStage() {
	m_gamecamera->Refresh();//refreshでコリジョンのバグを解消する
	// 階段の効果音を再生。
	SoundSource* se = NewGO<SoundSource>(0);
	se->Init(2);
	//効果音ループさせない。
	se->Play(false);
	//音量。
	se->SetVolume(4.0f);
	//SetLoading(); // ローディング画面を生成
	m_secondFloor = NewGO<SecondFloor>(0, "secondFloor");  // 次のステージを生成
	SetPosition();

	//LoadingとSecondFloorの切り替えを行うコードを書いておく!!
	DeleteGO(this);  // 現在のステージを削除
}

void FirstFloor::SetPosition() {
	m_player->SetPosition(Vector3(0.0f, 0.0f, 0.0f)); // プレイヤーの位置をリセット
}
void FirstFloor::Render(RenderContext& rc)
{
	//レベルの描画
	m_levelRender.Draw(rc);
}
