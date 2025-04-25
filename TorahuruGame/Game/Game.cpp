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
#include "FireGimmic.h"
#include "sound/SoundSource.h"
#include "sound/SoundEngine.h"

Game::Game()
{

}

Game::~Game() {

	DeleteGO(m_player);
	DeleteGO(m_gamecamera);
	DeleteGO(m_background);
	DeleteGO(m_stairs);
	DeleteGO(m_floorManager);
	DeleteGO(m_fireGimmic);

	//繧ｹ繝・・繧ｸ蜀・↓縺ゅｋreversefloor繧偵☆縺ｹ縺ｦ隕九▽縺代ｋ縲・
	const auto& reverseFloors = FindGOs<ReverseFloor>("ReverseFloor");
	for (auto reverseFloor : reverseFloors)
	{
		//繝昴う繝ｳ繝医Λ繧､繝医ｒ蜑企勁縺吶ｋ縲・
		DeleteGO(reverseFloor);
	}

	//繧ｹ繝・・繧ｸ蜀・↓縺ゅｋslowfloor繧偵☆縺ｹ縺ｦ隕九▽縺代ｋ縲・
	const auto& slowFloors = FindGOs<SlowFloor>("SlowFloor");
	for (auto slowFloor : slowFloors)
	{
		//繝昴う繝ｳ繝医Λ繧､繝医ｒ蜑企勁縺吶ｋ縲・
		DeleteGO(slowFloor);
	}

	//繧ｹ繝・・繧ｸ蜀・↓縺ゅｋblindfloor繧偵☆縺ｹ縺ｦ隕九▽縺代ｋ縲・
	const auto& blindFloors = FindGOs<BlindFloor>("BlindFloor");
	for (auto blindFloor : blindFloors)
	{
		//繝昴う繝ｳ繝医Λ繧､繝医ｒ蜑企勁縺吶ｋ縲・
		DeleteGO(blindFloor);
	}
}

void Game::InitSky() {

	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	m_skyCube->SetType(enSkyCubeType_NightToon);
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(10000.0f);
	
	// 迺ｰ蠅・・縺ｮ險育ｮ励・縺溘ａ縺ｮIBL繝・け繧ｹ繝√Ε繧偵そ繝・ヨ縺吶ｋ縲・
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f);

	// 迺ｰ蠅・律蜈峨・蠖ｱ髻ｿ縺悟・縺九ｊ繧・☆縺・ｈ縺・↓縲√ョ繧｣繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ繝ｩ繧､繝医・繧ｪ繝輔↓縲・
	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
}

void Game::TutorialText()
{
	// todo:tamaki 繝√Η繝ｼ繝医Μ繧｢繝ｫ驟咲ｽｮ逕ｨ(蠕後⊇縺ｩ霑ｽ蜉縺励∪縺吶・
	
	//m_tutorial = NewGO<Tutorial>(0, "tutorial");
	//m_tutorial->m_position = { 50.0f,40.0f,-350.0f };   // 轣ｫ轤取叛蟆・勣
	//// 2縺､繧√・轣ｫ轤取叛蟆・勣縺ｮ蠎ｧ讓・
	////m_tutorial4->m_position = { 2000.0f,40.0f,-1300.0f };   // 轣ｫ轤取叛蟆・勣

	//m_tutorial2 = NewGO<Tutorial>(0, "tutorial");
	//m_tutorial2->m_position = { -950.0f,40.0f,-1050.0f };  // 縺ゅ∋縺薙∋蠎・

	//m_tutorial3 = NewGO<Tutorial>(0, "tutorial");
	//m_tutorial3->m_position = { -500.0f, 40.0f, -1850.0f }; // 驤崎ｶｳ蠎・
	//
	//m_tutorial4 = NewGO<Tutorial>(0, "tutorial");
	//m_tutorial4->m_position = { 800.0f,40.0f,-1200.0f }; // 隕也阜蛻ｶ髯仙ｺ・
}

void Game::SetSutamina()
{
	m_setSutamina = NewGO<Sutamina>(0, "sutamina");
}

bool Game::Start()
{
	m_player				= NewGO<Player>(0, "player");
	m_player->m_position	= { 0.0f,0.0f,0.0f };			//繝励Ξ繧､繝､繝ｼ縺ｮ繝昴ず繧ｷ繝ｧ繝ｳ繧貞､峨∴繧・
	m_stairs				= NewGO<Stairs>(0, "stairs");			//髫取ｮｵ繧定ｿｽ蜉
	m_stairs->m_position	= { 1000.0f,-10.0f,20.0f };		//髫取ｮｵ蠎ｧ讓・
	m_gamecamera            = NewGO<GameCamera>(0, "gamecamera");
	m_se					= NewGO<SoundSource>(0, "se");
	m_floorManager			= NewGO<FloorManager>(0, "floorManager");

	InitSky();
	SetSutamina();
	TutorialText();
	m_modelRender.SetPosition(m_position);

	//繝ｬ繝吶Ν繧呈ｧ狗ｯ峨☆繧・
	m_levelRender.Init("Assets/level/BackGround1.tkl",[&](LevelObjectData& objData) {	//3遞ｮ鬘槭・蠎翫☆縺ｹ縺ｦ驟咲ｽｮ縺励◆tkl縲・
		if (objData.ForwardMatchName(L"Box") == true) {								//縺ゅ∋縺薙∋蠎翫・3dsMax縺ｮ蜷榊燕縲・
			m_background = NewGO<BackGround>(0, "Box");
			m_background->SetPosition(objData.position);
			m_background->SetScale(objData.scale);
			return true;
		}
		if (objData.ForwardMatchName(L"ReverseFloor") == true) {					//縺ゅ∋縺薙∋蠎翫・3dsMax縺ｮ蜷榊燕縲・
			m_reverseFloor = NewGO<ReverseFloor>(0, "ReverseFloor");
			m_reverseFloor->SetPosition(objData.position);
			m_reverseFloor->SetScale(objData.scale);
			return true;
		}
		if (objData.ForwardMatchName(L"SlowFloor") == true) {						//驤崎ｶｳ蠎翫・3dsMax縺ｮ蜷榊燕縲・
			m_slowFloor = NewGO<SlowFloor>(0, "SlowFloor");
			m_slowFloor->SetPosition(objData.position);
			m_slowFloor->SetScale(objData.scale);
			return true;
		}
		if (objData.ForwardMatchName(L"BlindFloor") == true) {						////隕也阜蛻ｶ髯仙ｺ翫・3dsMax縺ｮ蜷榊燕縲・
			m_blindFloor = NewGO<BlindFloor>(0, "BlindFloor");
			m_blindFloor->SetPosition(objData.position);
			m_blindFloor->SetScale(objData.scale);
		    return true;
		}
		if (objData.ForwardMatchName(L"FireGimmic") == true) {
			m_fireGimmic = NewGO<FireGimmic>(0, "firegimmic");                      ////繝輔ぃ繧､繧｢繝ｼ繧ｮ繝溘ャ繧ｯ縺ｮ3dsMax縺ｮ蜷榊燕
			m_fireGimmic->SetPosition(objData.position);
			m_fireGimmic->SetScale(objData.scale);
			m_fireGimmic->SetRotation(objData.rotation);
			return true;
		 }

	
	});

	return true;
}

void Game::Update()
{
	//譎る俣縺ｮ險育ｮ・
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;
	m_timer -= g_gameTime->GetFrameDeltaTime();

	//////繧ｿ繧､繝槭・縺ｮ陦ｨ遉ｺ///////
	wchar_t text[256];
	swprintf_s(text, 256, L"%02d:%02d", minute, sec);
	//陦ｨ遉ｺ縺吶ｋ繝・く繧ｹ繝医ｒ險ｭ螳壹・
	m_fontRender.SetText(text);
	//繝輔か繝ｳ繝医・菴咲ｽｮ繧定ｨｭ螳壹・
	m_fontRender.SetPosition(Vector3(-100.0f, 500.0f, 0.0f));
	//繝輔か繝ｳ繝医・螟ｧ縺阪＆繧定ｨｭ螳壹・
	m_fontRender.SetScale(2.0f);
	//繝輔か繝ｳ繝医・濶ｲ繧定ｨｭ螳壹・
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });



	m_modelRender.Update();
	Vector3 diff = m_player->m_position - m_stairs->m_position;		//diff縺ｧPlayer縺ｨStairs縺ｨ縺ｮ霍晞屬繧呈ｸｬ繧九◆繧√↓霑ｽ蜉縺励※縺・∪縺・
	if (diff.Length() <= 100.0f) {
		NewGO<GameClear>(0, "GameClear");
		DeleteGO(this);
	}

	//繧ｲ繝ｼ繝繧ｪ繝ｼ繝舌・逕ｨ縺ｮ繧ｿ繧､繝槭・
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
	m_fontRender.Draw(rc);
	//繝ｬ繝吶Ν縺ｧ隱ｭ縺ｿ霎ｼ繧薙□繝｢繝・Ν繧定｡ｨ遉ｺ縺輔○繧九・
	m_levelRender.Draw(rc);
}