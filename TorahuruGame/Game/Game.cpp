#include "stdafx.h"
#include "Game.h"
#include"Player.h"
#include"BackGround.h"
#include"GameCamera.h"
#include"Title.h"
#include"ReverseFloor.h"
#include "Specialfloor.h"
#include"Stairs.h"
#include"GameClear.h"
Game::Game()
{

}

Game::~Game() {

	DeleteGO(m_player);
	DeleteGO(m_gamecamera);
	DeleteGO(m_background);

}

void Game::InitSky() {

	DeleteGO(m_SkyCube);
	SkyCube* m_SkyCube = NewGO<SkyCube>(0, "skycube");

	m_SkyCube->SetType(enSkyCubeType_NightToon);
	m_SkyCube->SetLuminance(1.0f);
	m_SkyCube->SetScale(10000.0f);

	// 環境光の計算のためのIBLテクスチャをセットする。
	g_renderingEngine->SetAmbientByIBLTexture(m_SkyCube->GetTextureFilePath(), 1.0f);
	// 環境日光の影響が分かりやすいように、ディレクションライトはオフに。
	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);

}
bool Game::Start()
{
	
	m_player = NewGO<Player>(0, "player");
	m_player->m_position = { 00.0f,-200.0f,10.0f };//プレイヤーのポジションを変える
	

	m_stairs = NewGO<Stairs>(0, "stairs");//階段を追加
	m_stairs->m_position = { 860.0f,-300.0f,20.0f };//階段座標
	m_background = NewGO<BackGround>(0, "background");
	m_gamecamera = NewGO<GameCamera>(0, "gamecamera");

	InitSky();
	m_modelRender.SetPosition(m_position);

	////レベルを構築する
	//m_levelRender.Init("Assets/level/tokusyuyuka2.tkl",[&](LevelObjectData& objData) {
	//return true;
	//	});
	return true;

}

void Game::Update()
{

	wchar_t text[256];
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;
	swprintf_s(text, 256, L"%02d:%02d", minute, sec);
	//表示するテキストを設定。
	m_fontRender.SetText(text);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-100.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
	//フォントの色を設定。
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	m_timer -= g_gameTime->GetFrameDeltaTime();
	m_modelRender.Update();

	if (m_player->StairsCount == 1) {
		NewGO<GameClear>(0, "GameClear");
		DeleteGO(this);
	}

}

void SetPosition(const Vector3 position) {
	
	SetPosition(Vector3(0.0f, -200.0f, 10.0f));
}
void Game::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
	//レベルで読み込んだモデルを表示させる。
	//m_levelRender.Draw(rc);
}