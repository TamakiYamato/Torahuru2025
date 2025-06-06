#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Title.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "FloorManager.h"
#include "Stairs.h"
#include "Stamina.h"
#include "GameClear.h"
#include "Gameover.h"
#include "Loading.h"
#include "FireGimmic.h"
#include "FirstFloor.h"
#include "TutorialUI.h"
#include"SecondFloor.h"
#include"RotationFloor.h"
#include "sound/SoundSource.h"
#include "sound/SoundEngine.h"
//#include"StageManager.h"

Game::Game()
{

}

Game::~Game() {

	DeleteGO(m_player);
	DeleteGO(m_gamecamera);
	DeleteGO(m_stairs);
	DeleteGO(m_tutorialUI);
	DeleteGO(m_setStamina);
//	DeleteGO(m_stageManager);
	DeleteGO(m_Load);
	//あべこべ床をすべて見つける
	const auto& reverseFloors = FindGOs<ReverseFloor>("ReverseFloor");
	for (auto reverseFloor : reverseFloors)
	{
		//すべて削除する
		DeleteGO(reverseFloor);
	}

	//鈍足床をすべて見つける
	const auto& slowFloors = FindGOs<SlowFloor>("SlowFloor");
	for (auto slowFloor : slowFloors)
	{
		//すべて削除する
		DeleteGO(slowFloor);
	}

	//視界制限床をすべて見つける
	const auto& blindFloors = FindGOs<BlindFloor>("BlindFloor");
	for (auto blindFloor : blindFloors)
	{
		//すべて削除する
		DeleteGO(blindFloor);
	}
}

void Game::InitSky() {

	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	m_skyCube->SetType(enSkyCubeType_NightToon);
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(10000.0f);

}

// Directionライトの設定
void Game::LightSetting()
{
	// IBLテクスチャの設定
	//g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f);
	g_renderingEngine->SetAmbient(Vector3(0.5f, 0.5f, 0.5f));
	// 上からの光
	{
		Vector3 dir(0, -1, 0);
		dir.Normalize();
		Vector3 dirColor(0.5f, 0.5f, 0.5f);

		g_renderingEngine->SetDirectionLight(0, dir, dirColor);
	}

	{
		// 地面からの反射光
		Vector3 dir(0, 1, 0);
		dir.Normalize();
		Vector3 dirColor(0.76, 0.69, 0.52);

		g_renderingEngine->SetDirectionLight(1, dir, dirColor);
	}
};


void Game::SetSutamina()
{
	m_setStamina = NewGO<Stamina>(0, "sutamina");
}

// ロード用。
void Game::SetLoading()
{
}

void Game::SetGameClear()
{
	m_isWaitLoadOut = true;
	m_Load->StartLoadOut();
}

bool Game::Start()
{
	m_player			     = NewGO<Player>(0, "player");
	m_player->m_position  	= { 910.0f,0.0f,0.0f };				//プレイヤーの座標設定	
	//m_stairs		      		= NewGO<Stairs>(0, "stairs");		//階段
	//m_stairs->m_position	= { 1000.0f,-10.0f,20.0f };			//階段の座標設定
	m_gamecamera            = NewGO<GameCamera>(0, "gamecamera");
	m_se					= NewGO<SoundSource>(0, "se");
	m_tutorialUI			= NewGO<TutorialUI>(0,"tutorialUI");
	//m_stageManager=NewGO<StageManager>(0, "stageManager");//ステージマネージャー
	FirstFloor* firstFloor = NewGO<FirstFloor>(0, "firstFloor");	//最初の床
	InitSky();
	SetSutamina();
	m_modelRender.SetPosition(m_position);
	// ゲームの読み込みが終わった後、画面を明るくする。
	SetLoading();
  
	return true;
}

void Game::Update()
{
	m_Load = FindGO<Loading>("loading");//数字が数字の設定準
	// 画面の明るさを徐々に上げる。
	m_Load->StartLoading();


	if (m_floorManager == nullptr) {
		m_floorManager = FindGO<FloorManager>("floorManager");
	}
	if (m_stairs == nullptr) {
		m_stairs = FindGO<Stairs>("stairs");
	}
	// カメラライト
	if (m_floorManager!=nullptr&&m_floorManager->LightCount != 1)
	{
		Vector3 dir = g_camera3D->GetForward();
		dir.Normalize();
		Vector3 dirColor(2.3, 2.3, 2.3);

		LightSetting();

		g_renderingEngine->SetDirectionLight(2, dir, dirColor);
		m_floorManager->LightCount = 0;
	}
	else 
	{
		g_renderingEngine->SetDirectionLight(2, g_vec3Zero, g_vec3Zero);
	}
	// 制限時間
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;
	m_timer -= g_gameTime->GetFrameDeltaTime();

	//////制限時間のテキスト///////
	wchar_t text[256];
	swprintf_s(text, 256, L"%02d:%02d", minute, sec);
	// 文字のセット
	m_fontRender.SetText(text);
	// 文字の座標
	m_fontRender.SetPosition(Vector3(-100.0f, 500.0f, 0.0f));
	// 文字の大きさ
	m_fontRender.SetScale(2.0f);
	// 文字の色
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	//ゲームクリア条件
	m_modelRender.Update();
		//Vector3 diff = m_player->m_position - m_stairs->m_position;		//プレイヤーと階段との距離
		//if (diff.Length() <= 100.0f) {
		//	NewGO<GameClear>(0, "GameClear");
		//	DeleteGO(this);
		//	SetGameClear();
		//	
		//}
	
	//ゲームオーバー条件
	if (m_timer <= 0.0f) {	//タイマーが0になった場合
		NewGO<Gameover>(0, "Gameover");
		DeleteGO(this);
	}

	//if (m_enemqy->m_enemyState == m_enemy->enEnemyState_Attack) {	//敵に攻撃された場合
	//	NewGO<Gameover>(0, "Gameover");
	//	DeleteGO(this);
	//}
}

void SetPosition(const Vector3 position) {
	
	SetPosition(Vector3(0.0f, -200.0f, 10.0f));
}

void Game::Render(RenderContext& rc)
{
	//文字の描画
	m_fontRender.Draw(rc);
}

