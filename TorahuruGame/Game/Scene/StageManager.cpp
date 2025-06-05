#include "stdafx.h"
//#include "StageManager.h"
//#include"TutorialUI.h"
//#include"FirstFloor.h"
//#include"SecondFloor.h"
//StageManager::StageManager()
//{
//}
//
//StageManager::~StageManager()
//{
//
//}
//
//bool StageManager::Start() {
//	InitializeStage();
//	return true;
//}
//
//
//void StageManager::Update() {
//	switch (m_stageNumber) {
//	case Stage1:
//		//ステージ1の処理をここに記述
//		m_floor = NewGO<FirstFloor>(0, "firstfloor");//FirstFloorの生成
//		m_stageNumber = Invalid;//ステージ番号を無効にする
//		m_isTutorial = true;//チュートリアルを有効にする
//		break;
//
//	case Stage2:
//		//ステージ2の処理をここに記述
//		m_floor = NewGO<SecondFloor>(0, "secondfloor");//SecondFloorの生成
//		m_stageNumber = Invalid;//ステージ番号を無効にする
//		m_isTutorial = false;//チュートリアルを無効にする
//		break;
//
//	case Stage3:
//		//ステージ3の処理をここに記述
//		break;
//
//	}
//}
//
//void StageManager::InitializeStage()
//{
//	//ステージの初期化処理をここに記述
//	m_stageNumber = Stage1; //ステージ番号の初期化:ここに番号が割り当てられている
//}
//
//
//
