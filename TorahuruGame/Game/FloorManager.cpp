#include "stdafx.h"
#include "FloorManager.h"
#include "ReverseFloor.h"
#include "SlowFloor.h"
#include "BlindFloor.h"
#include "Player.h"
#include "Game.h"

namespace {
	const float PLAYER_MOVE_SLOW = 0.5;		//繝励Ξ繧､繝､繝ｼ縺ｮ騾溷ｺｦ繧貞､画峩縲・
}

FloorManager::FloorManager()
{

}

FloorManager::~FloorManager()
{
	
}

bool FloorManager::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");	
	

	return true;
}

void FloorManager::Update()
{
	
	////繧ｿ繧､繝槭・縺悟虚縺・※縺ｪ縺・ｼ昜ｻ悶・蠎翫′菴懷虚縺励※縺ｪ縺・→縺・///
	if (m_floorTimer >= 7.0f) {
		FindFloor();		//3遞ｮ鬘槭・蠎翫ｒ縺吶∋縺ｦ隕九▽縺代ｋ
	}

	AddStatus();			//迥ｶ諷九＃縺ｨ縺ｮ蜉ｹ譫懷渚譏

	////繝励Ξ繧､繝､繝ｼ縺悟ｺ翫・蠖ｱ髻ｿ繧貞女縺代※縺・ｋ蝣ｴ蜷・///
	if (m_saveState != Normal) {
		AddStatusTimer();       //迥ｶ諷九・譎る俣
		CalcStatusTime();	//蜉ｹ譫懈凾髢薙・繧ｿ繧､繝槭・繧貞虚縺九☆
	}

	////繝励Ξ繧､繝､繝ｼ縺瑚ｦ也阜蛻ｶ髯千憾諷九・蝣ｴ蜷・///
	if (m_saveState == BlindState) {
		pointLightPosition = m_player->m_position +Vector3(0.0f,200.0f,0.0f);
		m_pointL->SetPosition(pointLightPosition);
	}
}


void FloorManager::Render(RenderContext& rc)
{
	if (m_spriteRender) {
		m_spriteRender->Draw(rc);
	}

	if (m_fontRender) {
		m_fontRender->Draw(rc);
	}
}


void FloorManager::FindFloor()
{
	//繧ｹ繝・・繧ｸ蜀・↓縺ゅｋreversefloor繧偵☆縺ｹ縺ｦ隕九▽縺代ｋ縲・
	const auto& reverseFloors = FindGOs<ReverseFloor>("ReverseFloor");

	//for縺ｯ縺吶∋縺ｦ縺ｮreversefloor繧堤ｹｰ繧願ｿ斐☆縲・
	for (auto reverseFloor : reverseFloors) {
		//繝励Ξ繧､繝､繝ｼ縺悟ｺ翫・荳翫↓縺・◆縺ｨ縺阪∵桃菴懊ｒ騾・↓縺吶ｋ縲・
		if (reverseFloor->m_onReverseFloor == true) {
			m_floorState = ReverseState;
		}
	}

	///////////////////////////////////////////////////
	//繧ｹ繝・・繧ｸ蜀・↓縺ゅｋslowfloor繧偵☆縺ｹ縺ｦ隕九▽縺代ｋ縲・
	const auto& slowFloors = FindGOs<SlowFloor>("SlowFloor");

	//for縺ｯ縺吶∋縺ｦ縺ｮslowfloor繧堤ｹｰ繧願ｿ斐☆
	for (auto slowFloor : slowFloors) {
		//繝励Ξ繧､繝､繝ｼ縺悟ｺ翫・荳翫↓縺・◆縺ｨ縺阪√せ繝斐・繝峨′蜊雁・縺ｫ縺ｪ繧・
		if (slowFloor->m_onSlowFloor == true) {
			m_floorState = SlowState;
		}
	}

	//////////////////////////////////////////////////
	//for縺ｯ縺吶∋縺ｦ縺ｮblindfloor繧堤ｹｰ繧願ｿ斐☆
	//繧ｹ繝・・繧ｸ蜀・↓縺ゅｋblindfloor繧偵☆縺ｹ縺ｦ隕九▽縺代ｋ縲・
	const auto& blindFloors = FindGOs<BlindFloor>("BlindFloor");

	for (auto blindFloor : blindFloors) {
		//繝励Ξ繧､繝､繝ｼ縺悟ｺ翫・荳翫↓縺・◆縺ｨ縺阪∫憾諷九ｒ螟画峩
		if (blindFloor->m_onBlindFloor == true) {
			m_floorState = BlindState;
		}
	}
}


void FloorManager::AddStatus()	/////迥ｶ諷九＃縺ｨ縺ｮ蜉ｹ譫懷渚譏/////
{
	if (m_floorTimer == 7.0f) {		//譎る俣縺悟・譛溷喧縺輔ｌ縺ｦ縺・ｋ・昜ｻ悶・蜉ｹ譫懊′縺ｪ縺・ｴ蜷・
		if (!m_isAddStatus && m_floorState != Normal) {
			switch (m_floorState) {
			case ReverseState:
				if (m_spriteRender) {
					DeleteGO(m_spriteRender);
				}

				//繝・け繧ｹ繝√Ε繧定ｪｭ縺ｿ霎ｼ繧
				m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
				m_spriteRender->Init("Assets/sprite/reverse.DDS", 100.0f, 100.0f);
				m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));
				m_player->m_moveDir *= -1.0f;

				AddStatusTimer();

				break;

			case SlowState:
				if (m_spriteRender) {
					DeleteGO(m_spriteRender);
				}

				m_floorTimer -= g_gameTime->GetFrameDeltaTime();

				//繝・け繧ｹ繝√Ε繧定ｪｭ縺ｿ霎ｼ繧

				m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
				m_spriteRender->Init("Assets/sprite/slow.DDS", 100.0f, 100.0f);
				m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));
				m_player->m_moveDir *= PLAYER_MOVE_SLOW;

				AddStatusTimer();

				break;

			case BlindState:
				if (m_spriteRender) {
					DeleteGO(m_spriteRender);
				}

				m_floorTimer -= g_gameTime->GetFrameDeltaTime();

				//繝・け繧ｹ繝√Ε繧定ｪｭ縺ｿ霎ｼ繧

				m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
				m_spriteRender->Init("Assets/sprite/blind.DDS", 100.0f, 100.0f);
				m_spriteRender->SetPosition(Vector3(640.0f, 360.0f, 0.0f));

				AddStatusTimer();

				//////////////繧ｹ繝・・繧ｸ繧呈囓縺上☆繧・//////////////////////////

				// 迺ｰ蠅・・縺ｮ險育ｮ励・縺溘ａ縺ｮIBL繝・け繧ｹ繝√Ε繧偵そ繝・ヨ縺吶ｋ縲・
				g_renderingEngine->SetAmbientByIBLTexture(m_game->m_skyCube->GetTextureFilePath(), 0.01f);

				// 繧ｷ繝ｼ繝ｳ縺ｮ荳ｭ髢薙・譏弱ｋ縺輔ｒ遉ｺ縺呎・蠎ｦ邇・ｒ謖・ｮ壹☆繧九・
				g_renderingEngine->SetSceneMiddleGray(0.01f);

				// 繝悶Ν繝ｼ繝縺檎匱逕溘☆繧矩明蛟､繧定ｨｭ螳壹・
				// 繝悶Ν繝ｼ繝窶ｦ譏弱ｋ縺・Κ蛻・′縺ｫ縺倥・繧医≧縺ｫ隕九∴繧玖ｦ冶ｦ壼柑譫懊∝・繧貞ｼｷ隱ｿ縺励√Μ繧｢繝ｫ繝ｻ鄒弱＠縺・・蟷ｻ諠ｳ逧・↓隕九○繧・
				g_renderingEngine->SetBloomThreshold(10.0f);

				//////////////繧ｹ繝昴ャ繝医Λ繧､繝・/////////////////////////////
				SetPointLight();

				break;
			default:
				break;
			}
			m_saveState = m_floorState;
			m_floorState = Normal;
		}
	}
}

void FloorManager::AddStatusTimer()
{
	//蜉ｹ譫懈凾髢薙・陦ｨ遉ｺ
	int effectTimer_minute = 0.0f;
	int effectTimer_sec = m_floorTimer;

	m_fontRender = NewGO<FontRender>(0, "fontrender");
	//蜉ｹ譫懈凾髢薙ち繧､繝槭・縺ｮ陦ｨ遉ｺ
	wchar_t reverse_text[256];
	swprintf_s(reverse_text, 256, L"%02d:%02d", effectTimer_minute, effectTimer_sec);
	//陦ｨ遉ｺ縺吶ｋ繝・く繧ｹ繝医ｒ險ｭ螳壹・
	m_fontRender->SetText(reverse_text);
	//繝輔か繝ｳ繝医・菴咲ｽｮ繧定ｨｭ螳壹・
	m_fontRender->SetPosition(Vector3(700.0f, 390.0f, 0.0f));
	//繝輔か繝ｳ繝医・螟ｧ縺阪＆繧定ｨｭ螳壹・
	m_fontRender->SetScale(1.5f);
	//繝輔か繝ｳ繝医・濶ｲ繧定ｨｭ螳壹・
	m_fontRender->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	
}


void FloorManager::SetPointLight()
{
	m_pointL = NewGO<PointLight>(0,"pointLight");
	
	m_pointL->Init();
	m_pointL->SetPosition(pointLightPosition);
	m_pointL->SetAffectPowParam(0.7f);				//蠖ｱ髻ｿ蜉帙ｒ謖√◆縺帙ｋ縲・
	m_pointL->SetColor(Vector3(5.0f, 5.0f, 5.0f));
	m_pointL->SetRange(250.0f);
	m_pointL->Update();	
}

void FloorManager::DeletePointLight()
{
	DeleteGO(m_pointL);
}


void FloorManager::CalcStatusTime()
{
	m_floorTimer -= g_gameTime->GetFrameDeltaTime();	//蜉ｹ譫懈凾髢薙・繧ｫ繧ｦ繝ｳ繝医ム繧ｦ繝ｳ7遘・
	if (m_floorTimer <= 0) {							//譎る俣縺・縺ｫ縺ｪ縺｣縺溷ｴ蜷・
		RevertState();									//蠎翫・蜉ｹ譫懊ｒ豸医☆
		m_floorTimer = 7.0f;							//蜉ｹ譫懈凾髢薙ｒ繝ｪ繧ｻ繝・ヨ
		DeleteGO(m_spriteRender);                       //繝・け繧ｹ繝√Ε繧呈ｶ医☆
		DeleteGO(m_fontRender);
		m_spriteRender = nullptr;
		m_fontRender = nullptr;
	}
}

/// <summary>
/// 繝励Ξ繧､繝､繝ｼ縺悟ｺ翫°繧牙女縺代◆蜉ｹ譫懊ｒ謌ｻ縺・
/// </summary>
void FloorManager::RevertState()
{
	if (!m_isAddStatus) {
		return;
	}
	switch (m_saveState) {
	case Normal:
		m_player->m_moveDir = 1.0f;
		break;
	case ReverseState:
		if (m_spriteRender) {
			DeleteGO(m_spriteRender);
			m_spriteRender = nullptr;
		}
		m_player->m_moveDir *= -1.0f;
		break;
	case SlowState:
		if (m_spriteRender) {
			DeleteGO(m_spriteRender);
			m_spriteRender = nullptr;
		}
		m_player->m_moveDir /= PLAYER_MOVE_SLOW;
		break;
	case BlindState:
		if (m_spriteRender) {
			DeleteGO(m_spriteRender);
			m_spriteRender = nullptr;
		}
		// 迺ｰ蠅・・繧貞・縺ｫ謌ｻ縺・
		g_renderingEngine->SetAmbientByIBLTexture(m_game->m_skyCube->GetTextureFilePath(), 1.0f);
		g_renderingEngine->SetSceneMiddleGray(0.18f);
		g_renderingEngine->SetBloomThreshold(1.0f);
		//繝昴う繝ｳ繝医Λ繧､繝・
		DeletePointLight();
		break;
	}
	m_saveState = Normal;	//菫晏ｭ倥＠縺溘ｂ縺ｮ繧帝壼ｸｸ縺ｫ縲・
}
