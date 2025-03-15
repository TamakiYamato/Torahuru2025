#include "stdafx.h"
#include "Game.h"
#include"Player.h"
#include"BackGround.h"
#include"GameCamera.h"
#include"Title.h"
#include"Game.h"
#include"Player.h"
#include"ReverseFloor.h"

Game::Game()
{

}
Game::~Game() {

	DeleteGO(m_player);
	DeleteGO(m_gamecamera);
	/*DeleteGO(m_sumaho);*/
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

	m_background = NewGO<BackGround>(0, "background");
	m_gamecamera = NewGO<GameCamera>(0, "gamecamera");
	InitSky();

	m_modelRender.SetPosition(m_position);
	return true;
}
void Game::CountTimer() {

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
}
void Game::Render(RenderContext& rc)
{

	m_fontRender.Draw(rc);
}