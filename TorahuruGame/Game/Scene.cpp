#include "stdafx.h"
//#include "Scene.h"
//#include"TutorialUI.h"
//#include "Game.h"
//#include"FirstFloor.h"
//#include"SecondFloor.h"
//#include"Title.h"
//Scene_Manager* Scene_Manager::instance = nullptr;//シングルトンインスタンスの初期化
//
//
//bool Scene::Start()
//{
//
//	return true;
//}
//
//bool TitleScene::Start()
//{
//
//	// タイトルシーンの初期化処理を行う。
//	m_title = NewGO<Title>(0, "Title"); // タイトルシーンの初期化処理を行う。
//	return true;
//}
//
//bool FirstFloorScene::Start()
//{
//	// ステージ1の初期化処理を行う。
//	m_game = NewGO<Game>(0, "game"); // ゲームの初期化処理を行う。
//	m_firstfloor = NewGO<FirstFloor>(0, "fircefloor"); // ステージ1の初期化処理を行う。
//
//	return true;
//}
//
//bool SecondFloorScene::Start()
//{
//	// ステージ2の初期化処理を行う。
//	m_secondfloor = NewGO<SecondFloor>(0, "secondfloor"); // ステージ2の初期化処理を行う。
//	return true;
//}
//
//bool Scene_Manager::Start()
//{
//
//	return true;
//}
//
//void Scene::Update()
//{
//	// シーンマネージャーのUpdateを呼び出す。
//	Scene_Manager::GetInstance()->Update();
//}
//
//// タイトルシーン::更新処理。
//void TitleScene::Update()
//{
//	//Titleメニューのスタートが押されているかでステージ遷移を判定する。
//	if (g_pad[0]->IsPress(enButtonA))
//	{
//		Scene_Manager::GetInstance()->SetRequest(SceneID::S_Stage1);
//	}
//}
//
//// ステージ1シーン::更新処理。
//void FirstFloorScene::Update()
//{
//	// ステージをクリアしたかの判定を行う。]
//	return;
//}
//
//// ステージ2シーン::更新処理。
//void SecondFloorScene::Update()
//{
//
//	// ステージをクリアしたかの判定を行う。
//	return ;
//}
//
//// マネージャー::更新処理。
//void Scene_Manager::Update()
//{
//	// IDが無効でない場合、シーン遷移を行う。
//	if (requestSceneID != SceneID::Invalid)
//	{
//		ChangeScene(); // シーン遷移。
//	}
//
//	if (scene) scene->Update(); // シーンの更新処理を呼び出す。
//}
//
//// シーンの初期化処理。
//void Scene_Manager::ChangeScene()
//{
//	// 既存のシーンの解放。
//	if (scene)
//	{
//		delete scene;
//		scene = nullptr;
//	}
//
//
//	if (requestSceneID != SceneID::Invalid)
//	{
//		delete scene;
//
//		switch (requestSceneID)
//		{
//		case SceneID::S_Title:
//			scene = new TitleScene(); // シーンの初期化。
//			requestSceneID = SceneID::Invalid; // シーン遷移後にリクエストを無効化。
//			break;
//		case SceneID::S_Stage1:
//			scene = new FirstFloorScene(); // シーンの初期化。
//			requestSceneID = SceneID::Invalid;
//			break;
//		case SceneID::S_Stage2:
//			scene = new SecondFloorScene(); // シーンの初期化。
//			requestSceneID = SceneID::Invalid;
//			break;
//		default:
//			break;
//		}
//	}
//
//	// シーンが作られたら Start() を呼び出す。
//	if (scene)
//	{
//		scene->Start(); // シーンの初期化処理を呼び出す。
//		// リクエストされたシーンIDを無効化。
//		requestSceneID = SceneID::Invalid;
//
//	}
//
//}