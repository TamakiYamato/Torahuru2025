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

	//郢ｧ・ｹ郢昴・繝ｻ郢ｧ・ｸ陷繝ｻ竊鍋ｸｺ繧・ｽ脚eversefloor郢ｧ蛛ｵ笘・ｸｺ・ｹ邵ｺ・ｦ髫穂ｹ昶命邵ｺ莉｣・狗ｸｲ繝ｻ
	const auto& reverseFloors = FindGOs<ReverseFloor>("ReverseFloor");
	for (auto reverseFloor : reverseFloors)
	{
		//郢晄亢縺・ｹ晢ｽｳ郢晏現ﾎ帷ｹｧ・､郢晏現・定恆莨∝求邵ｺ蜷ｶ・狗ｸｲ繝ｻ
		DeleteGO(reverseFloor);
	}

	//郢ｧ・ｹ郢昴・繝ｻ郢ｧ・ｸ陷繝ｻ竊鍋ｸｺ繧・ｽ虐lowfloor郢ｧ蛛ｵ笘・ｸｺ・ｹ邵ｺ・ｦ髫穂ｹ昶命邵ｺ莉｣・狗ｸｲ繝ｻ
	const auto& slowFloors = FindGOs<SlowFloor>("SlowFloor");
	for (auto slowFloor : slowFloors)
	{
		//郢晄亢縺・ｹ晢ｽｳ郢晏現ﾎ帷ｹｧ・､郢晏現・定恆莨∝求邵ｺ蜷ｶ・狗ｸｲ繝ｻ
		DeleteGO(slowFloor);
	}

	//郢ｧ・ｹ郢昴・繝ｻ郢ｧ・ｸ陷繝ｻ竊鍋ｸｺ繧・ｽ誼lindfloor郢ｧ蛛ｵ笘・ｸｺ・ｹ邵ｺ・ｦ髫穂ｹ昶命邵ｺ莉｣・狗ｸｲ繝ｻ
	const auto& blindFloors = FindGOs<BlindFloor>("BlindFloor");
	for (auto blindFloor : blindFloors)
	{
		//郢晄亢縺・ｹ晢ｽｳ郢晏現ﾎ帷ｹｧ・､郢晏現・定恆莨∝求邵ｺ蜷ｶ・狗ｸｲ繝ｻ
		DeleteGO(blindFloor);
	}
}

void Game::InitSky() {

	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	m_skyCube->SetType(enSkyCubeType_NightToon);
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(10000.0f);
	
	// 霑ｺ・ｰ陟・・繝ｻ邵ｺ・ｮ髫ｪ閧ｲ・ｮ蜉ｱ繝ｻ邵ｺ貅假ｽ∫ｸｺ・ｮIBL郢昴・縺醍ｹｧ・ｹ郢昶・ﾎ慕ｹｧ蛛ｵ縺晉ｹ昴・繝ｨ邵ｺ蜷ｶ・狗ｸｲ繝ｻ
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f);

	// 霑ｺ・ｰ陟・・蠕玖怦蟲ｨ繝ｻ陟厄ｽｱ鬮ｻ・ｿ邵ｺ謔溘・邵ｺ荵晢ｽ顔ｹｧ繝ｻ笘・ｸｺ繝ｻ・育ｸｺ繝ｻ竊鍋ｸｲ竏壹Ι郢ｧ・｣郢晢ｽｬ郢ｧ・ｯ郢ｧ・ｷ郢晢ｽｧ郢晢ｽｳ郢晢ｽｩ郢ｧ・､郢晏現繝ｻ郢ｧ・ｪ郢晁ｼ披・邵ｲ繝ｻ
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

void Game::SetSutamina()
{
	m_setSutamina = NewGO<Sutamina>(0, "sutamina");
}

bool Game::Start()
{
	m_player				= NewGO<Player>(0, "player");
	m_player->m_position	= { 0.0f,0.0f,0.0f };			//郢晏干ﾎ樒ｹｧ・､郢晢ｽ､郢晢ｽｼ邵ｺ・ｮ郢晄亢縺夂ｹｧ・ｷ郢晢ｽｧ郢晢ｽｳ郢ｧ雋橸ｽ､蟲ｨ竏ｴ郢ｧ繝ｻ
	m_stairs				= NewGO<Stairs>(0, "stairs");			//鬮ｫ蜿厄ｽｮ・ｵ郢ｧ螳夲ｽｿ・ｽ陷会｣ｰ
	m_stairs->m_position	= { 1000.0f,-10.0f,20.0f };		//鬮ｫ蜿厄ｽｮ・ｵ陟趣ｽｧ隶薙・
	m_gamecamera            = NewGO<GameCamera>(0, "gamecamera");
	m_se					= NewGO<SoundSource>(0, "se");
	m_floorManager			= NewGO<FloorManager>(0, "floorManager");

	InitSky();
	SetSutamina();
	TutorialText();
	m_modelRender.SetPosition(m_position);

	//郢晢ｽｬ郢晏生ﾎ晉ｹｧ蜻茨ｽｧ迢暦ｽｯ蟲ｨ笘・ｹｧ繝ｻ
	m_levelRender.Init("Assets/level/BackGround1.tkl",[&](LevelObjectData& objData) {	//3驕橸ｽｮ鬯俶ｧｭ繝ｻ陟守ｿｫ笘・ｸｺ・ｹ邵ｺ・ｦ鬩溷調・ｽ・ｮ邵ｺ蜉ｱ笳・kl邵ｲ繝ｻ
		if (objData.ForwardMatchName(L"Box") == true) {								//邵ｺ繧・・邵ｺ阮吮・陟守ｿｫ繝ｻ3dsMax邵ｺ・ｮ陷ｷ讎顔√邵ｲ繝ｻ
			m_background = NewGO<BackGround>(0, "Box");
			m_background->SetPosition(objData.position);
			m_background->SetScale(objData.scale);
			return true;
		}
		if (objData.ForwardMatchName(L"ReverseFloor") == true) {					//邵ｺ繧・・邵ｺ阮吮・陟守ｿｫ繝ｻ3dsMax邵ｺ・ｮ陷ｷ讎顔√邵ｲ繝ｻ
			m_reverseFloor = NewGO<ReverseFloor>(0, "ReverseFloor");
			m_reverseFloor->SetPosition(objData.position);
			m_reverseFloor->SetScale(objData.scale);
			return true;
		}
		if (objData.ForwardMatchName(L"SlowFloor") == true) {						//鬩､蟠趣ｽｶ・ｳ陟守ｿｫ繝ｻ3dsMax邵ｺ・ｮ陷ｷ讎顔√邵ｲ繝ｻ
			m_slowFloor = NewGO<SlowFloor>(0, "SlowFloor");
			m_slowFloor->SetPosition(objData.position);
			m_slowFloor->SetScale(objData.scale);
			return true;
		}
		if (objData.ForwardMatchName(L"BlindFloor") == true) {						////髫穂ｹ滄・陋ｻ・ｶ鬮ｯ莉呻ｽｺ鄙ｫ繝ｻ3dsMax邵ｺ・ｮ陷ｷ讎顔√邵ｲ繝ｻ
			m_blindFloor = NewGO<BlindFloor>(0, "BlindFloor");
			m_blindFloor->SetPosition(objData.position);
			m_blindFloor->SetScale(objData.scale);
		    return true;
		}
		if (objData.ForwardMatchName(L"FireGimmic") == true) {
			m_fireGimmic = NewGO<FireGimmic>(0, "firegimmic");                      ////郢晁ｼ斐＜郢ｧ・､郢ｧ・｢郢晢ｽｼ郢ｧ・ｮ郢晄ｺ倥Ε郢ｧ・ｯ邵ｺ・ｮ3dsMax邵ｺ・ｮ陷ｷ讎顔√
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
	//隴弱ｋ菫｣邵ｺ・ｮ髫ｪ閧ｲ・ｮ繝ｻ
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;
	m_timer -= g_gameTime->GetFrameDeltaTime();

	//////郢ｧ・ｿ郢ｧ・､郢晄ｧｭ繝ｻ邵ｺ・ｮ髯ｦ・ｨ驕会ｽｺ///////
	wchar_t text[256];
	swprintf_s(text, 256, L"%02d:%02d", minute, sec);
	//髯ｦ・ｨ驕会ｽｺ邵ｺ蜷ｶ・狗ｹ昴・縺冗ｹｧ・ｹ郢晏現・帝坎・ｭ陞ｳ螢ｹﾂ繝ｻ
	m_fontRender.SetText(text);
	//郢晁ｼ斐°郢晢ｽｳ郢晏現繝ｻ闖ｴ蜥ｲ・ｽ・ｮ郢ｧ螳夲ｽｨ・ｭ陞ｳ螢ｹﾂ繝ｻ
	m_fontRender.SetPosition(Vector3(-100.0f, 500.0f, 0.0f));
	//郢晁ｼ斐°郢晢ｽｳ郢晏現繝ｻ陞滂ｽｧ邵ｺ髦ｪ・・ｹｧ螳夲ｽｨ・ｭ陞ｳ螢ｹﾂ繝ｻ
	m_fontRender.SetScale(2.0f);
	//郢晁ｼ斐°郢晢ｽｳ郢晏現繝ｻ豼ｶ・ｲ郢ｧ螳夲ｽｨ・ｭ陞ｳ螢ｹﾂ繝ｻ
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });



	m_modelRender.Update();
	Vector3 diff = m_player->m_position - m_stairs->m_position;		//diff邵ｺ・ｧPlayer邵ｺ・ｨStairs邵ｺ・ｨ邵ｺ・ｮ髴肴辨螻ｬ郢ｧ蜻茨ｽｸ・ｬ郢ｧ荵昶螺郢ｧ竏壺・髴托ｽｽ陷会｣ｰ邵ｺ蜉ｱ窶ｻ邵ｺ繝ｻ竏ｪ邵ｺ繝ｻ
	if (diff.Length() <= 100.0f) {
		NewGO<GameClear>(0, "GameClear");
		DeleteGO(this);
	}

	//郢ｧ・ｲ郢晢ｽｼ郢晢｣ｰ郢ｧ・ｪ郢晢ｽｼ郢晁・繝ｻ騾包ｽｨ邵ｺ・ｮ郢ｧ・ｿ郢ｧ・､郢晄ｧｭ繝ｻ
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
	//郢晢ｽｬ郢晏生ﾎ晉ｸｺ・ｧ髫ｱ・ｭ邵ｺ・ｿ髴趣ｽｼ郢ｧ阮吮味郢晢ｽ｢郢昴・ﾎ晉ｹｧ螳夲ｽ｡・ｨ驕会ｽｺ邵ｺ霈披雷郢ｧ荵敖繝ｻ
	m_levelRender.Draw(rc);
}