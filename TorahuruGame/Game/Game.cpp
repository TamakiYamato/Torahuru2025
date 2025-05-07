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
#include "Tutorial.h"
#include "Stairs.h"
#include "Sutamina.h"
#include "GameClear.h"
#include "Gameover.h"
#include "Loading.h"
#include "FireGimmic.h"
#include "FirstFloor.h"
#include "sound/SoundSource.h"
#include "sound/SoundEngine.h"

Game::Game()
{
}

Game::~Game() {

	DeleteGO(m_player);
	DeleteGO(m_gamecamera);
	DeleteGO(m_stairs);
	DeleteGO(m_firstFloor->m_background);
	DeleteGO(m_firstFloor->m_floorManager);
	DeleteGO(m_firstFloor->m_fireGimmic);

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
	
	// IBLテクスチャの設定
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f);

	// Directionライトの設定
	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
}

void Game::TutorialText()
{
	// todo:tamaki 郢昶・ﾎ礼ｹ晢ｽｼ郢晏現ﾎ懃ｹｧ・｢郢晢ｽｫ鬩溷調・ｽ・ｮ騾包ｽｨ(陟募ｾ娯括邵ｺ・ｩ髴托ｽｽ陷会｣ｰ邵ｺ蜉ｱ竏ｪ邵ｺ蜷ｶﾂ繝ｻ
	
	//m_tutorial = NewGO<Tutorial>(0, "tutorial");
	//m_tutorial->m_position = { 50.0f,40.0f,-350.0f };   // 霓｣・ｫ霓､蜿門鋤陝・・蜍｣
	//// 2邵ｺ・､郢ｧ竏壹・霓｣・ｫ霓､蜿門鋤陝・・蜍｣邵ｺ・ｮ陟趣ｽｧ隶薙・
	////m_tutorial4->m_position = { 2000.0f,40.0f,-1300.0f };   // 霓｣・ｫ霓､蜿門鋤陝・・蜍｣

	//m_tutorial2 = NewGO<Tutorial>(0, "tutorial");
	//m_tutorial2->m_position = { -950.0f,40.0f,-1050.0f };  // 邵ｺ繧・・邵ｺ阮吮・陟弱・

	//m_tutorial3 = NewGO<Tutorial>(0, "tutorial");
	//m_tutorial3->m_position = { -500.0f, 40.0f, -1850.0f }; // 鬩､蟠趣ｽｶ・ｳ陟弱・
	//
	//m_tutorial4 = NewGO<Tutorial>(0, "tutorial");
	//m_tutorial4->m_position = { 800.0f,40.0f,-1200.0f }; // 髫穂ｹ滄・陋ｻ・ｶ鬮ｯ莉呻ｽｺ繝ｻ
}

// 第一フロア。
void Game::SetFirstFloor()
{
	m_firstFloor = NewGO<FirstFloor>(0, "firstFloor");
}

void Game::SetSutamina()
{
	m_setSutamina = NewGO<Sutamina>(0, "sutamina");
}

// ロード用。
void Game::SetLoading()
{
	m_Load = FindGO<Loading>("loading");
	// 画面の明るさを徐々に上げる。
	m_Load->StartLoading();

}

void Game::SetGameClear()
{
	/*m_isWaitLoadOut = true;
	m_Load->StartLoadOut();*/
}

bool Game::Start()
{
	m_player				= NewGO<Player>(0, "player");
	m_player->m_position	= { 0.0f,0.0f,0.0f };				//プレイヤーの座標設定	
	m_stairs				= NewGO<Stairs>(0, "stairs");		//階段
	m_stairs->m_position	= { 1000.0f,-10.0f,20.0f };			//階段の座標設定
	m_gamecamera            = NewGO<GameCamera>(0, "gamecamera");
	m_se					= NewGO<SoundSource>(0, "se");

	InitSky();
	SetSutamina();
	TutorialText();
	m_modelRender.SetPosition(m_position);
	// ゲームの読み込みが終わった後、画面を明るくする。
	SetLoading();

	// 第一フロアを呼び出す。
	SetFirstFloor();

	return true;
}

void Game::Update()
{
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
	Vector3 diff = m_player->m_position - m_stairs->m_position;		//プレイヤーと階段との距離
	if (diff.Length() <= 100.0f) {
		NewGO<GameClear>(0, "GameClear");
		DeleteGO(this);
		SetGameClear();
	}

	//ゲームオーバー条件
	if (m_timer <= 0.0f) {
		NewGO<Gameover>(0, "Gameover");
		DeleteGO(this);
	}
}

void SetPosition(const Vector3 position) {
	
	SetPosition(Vector3(0.0f, -200.0f, 10.0f));
}

void Game::Render(RenderContext& rc)
{
	//文字の描画
	m_fontRender.Draw(rc);
}

