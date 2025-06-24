#pragma once
#include "Title.h"
#include "Loading.h"
#include "Game.h"
#include "FirstFloor.h"
#include "SecondFloor.h"
#include "GameClear.h"
#include "GameOver.h"

// ゲーム全体のシーン管理を行うマネージャークラス
// IGameObjectを継承し、各シーン（タイトル・ゲーム・リザルト・ゲームオーバー）の生成・削除を管理する

// ゲームシーンの列挙型
enum GameScene {
	enGameScene_Title,
	enGameScene_Game,
	enGameScene_Stage1,
	enGameScene_Stage2,
	enGameScene_GameClear,
	enGameScene_GameOver,
	enGameScene_Num // シーン数（必要なら）
};

class GameManager : public IGameObject
{
public:
	GameManager() {};
	~GameManager() {};

	// ゲーム開始時の初期化処理
	bool Start();
	// 毎フレーム呼ばれる更新処理
	void Update();

	Title* m_title = nullptr; // タイトルシーンのポインタ
	Loading* m_loading = nullptr; // ローディングシーンのポインタ
	Game* m_game = nullptr; // ゲームシーンのポインタ
	FirstFloor* m_firstFloor = nullptr; // フロア1のポインタ
	SecondFloor* m_secondFloor = nullptr; // フロア2のポインタ
	GameClear* m_gameClear = nullptr; // リザルトシーンのポインタ
	Gameover* m_gameOver = nullptr;	// ゲームオーバーシーンのポインタ

	GameScene m_gameScene = enGameScene_Title; // 現在のゲームシーンを管理する変数

	 GameScene GetNextScene() const
	{
		return m_gameScene;
	}

	// タイトルシーンの生成
	void CreateTitle()
	{
		m_title = NewGO<Title>(0, "Title"); // タイトルシーンの初期化
	};
	// タイトルシーンの削除
	void DeleteTitle()
	{
		if (m_title) {
			DeleteGO(m_title); // タイトルシーンの削除
			m_title = nullptr; // ポインタをnullptrに設定
		}
	};

	void CreateLoading() {
		m_loading = NewGO<Loading>(0, "loading");
	};

	void DeleteLoading() {
		if (m_loading) {
			DeleteGO(m_loading);
			m_loading = nullptr;
		}
	}

	// ゲームシーンの生成
	void CreateGame()
	{
		m_game = NewGO<Game>(0, "game"); // ゲームシーンの初期化
	};
	// ゲームシーンの削除
	void DeleteGame()
	{
		if (m_game) {
			DeleteGO(m_game); // ゲームシーンの削除
			m_game = nullptr; // ポインタをnullptrに設定
		}
	};

	//フロア1の生成
	void CreateFirstFloor() {
		m_firstFloor = NewGO<FirstFloor>(0, "firstFloor");
	}
	//フロア1の削除
	void DeleteFirstFloor() {
		if (m_firstFloor) {
			DeleteGO(m_firstFloor);
			m_firstFloor = nullptr;
		}
	}

	//フロア2の生成
	void CreateSecondFloor()
	{
		m_secondFloor = NewGO<SecondFloor>(0, "secondFloor"); // フロア2の初期化
	};
	// フロア2の削除
	void DeleteSecondFloor()
	{
		if (m_secondFloor) {
			DeleteGO(m_secondFloor); // フロア2の削除
			m_secondFloor = nullptr; // ポインタをnullptrに設定
		}
	};

	// リザルトシーンの生成
	void CreateGameClear()
	{
		m_gameClear = NewGO<GameClear>(0, "gameClear"); // リザルトシーンの初期化
	};
	// リザルトシーンの削除
	void DeleteGameClear()
	{
		if (m_gameClear) {
			DeleteGO(m_gameClear); // リザルトシーンの削除
			m_gameClear = nullptr; // ポインタをnullptrに設定
		}
	};

	// ゲームオーバーシーンの生成
	void CreateGameOver()
	{
		m_gameOver = NewGO<Gameover>(0, "gameOver"); // ゲームオーバーシーンの初期化
	};
	// ゲームオーバーシーンの削除
	void DeleteGameOver()
	{
		if (m_gameOver) {
			DeleteGO(m_gameOver); // ゲームオーバーシーンの削除
			m_gameOver = nullptr; // ポインタをnullptrに設定
		}
	};
};