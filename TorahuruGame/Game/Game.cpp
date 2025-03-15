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



	// �����̌v�Z�̂��߂�IBL�e�N�X�`�����Z�b�g����B
	g_renderingEngine->SetAmbientByIBLTexture(m_SkyCube->GetTextureFilePath(), 1.0f);
	// �������̉e����������₷���悤�ɁA�f�B���N�V�������C�g�̓I�t�ɁB
	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
}
bool Game::Start()
{
	m_player = NewGO<Player>(0, "player");
	m_player->m_position = { 00.0f,-200.0f,10.0f };//�v���C���[�̃|�W�V������ς���

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
	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(text);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(-100.0f, 500.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(2.0f);
	//�t�H���g�̐F��ݒ�B
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	m_timer -= g_gameTime->GetFrameDeltaTime();
	m_modelRender.Update();
}
void Game::Render(RenderContext& rc)
{

	m_fontRender.Draw(rc);
}