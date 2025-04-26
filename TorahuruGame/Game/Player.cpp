// include竊偵％縺ｮ繧ｯ繝ｩ繧ｹ蜀・〒莉悶け繝ｩ繧ｹ繧貞盾辣ｧ縺吶ｋ縲・
#include "stdafx.h"
#include "Player.h"
#include"Game.h"
#include"ReverseFloor.h"
#include"SlowFloor.h"
#include"BlindFloor.h"
#include <string>

// const繧剃ｽｿ逕ｨ縺励※螳壽焚繧剃ｽ懈・縺吶ｋ縲・
// namespace竊堤┌蜷榊錐蜑咲ｩｺ髢・
// 螟夜Κ縺九ｉ繧｢繧ｯ繧ｻ繧ｹ縺輔ｌ縺ｪ縺・ｈ縺・↓縺励◆縺・ｮ壽焚繧・未謨ｰ繧呈ｼ邏阪☆繧九・
namespace
{
	// 繝輔ぃ繧､繝ｫ繝代せ繧貞ｮ壽焚螳夂ｾｩ
	//char string;

	// 繝輔ぃ繧､繝ｫ繝代せ縺ｯ譁・ｭ怜・縺ｪ縺ｮ縺ｧ string 繧剃ｽｿ逕ｨ縺吶ｋ縲・
	// const 繧剃ｽｿ逕ｨ縺怜ｮ壽焚繧貞ｮ夂ｾｩ縲・const竊貞､画焚縺悟､画峩荳榊庄縺ｧ縺ゅｋ縺薙→繧堤､ｺ縺吶・
	// 繝偵Η繝ｼ繝槭Φ繧ｨ繝ｩ繝ｼ繧帝亟縺舌ゅ繝偵Η繝ｼ繝槭Φ繧ｨ繝ｩ繝ｼ竊偵ち繧､繝斐Φ繧ｰ遲峨・繝溘せ縺ｧ襍ｷ縺薙ｋ繧ｨ繝ｩ繝ｼ縲・
	const std::string animationFilePath = "Assets/animData/player/";
	const std::string animationExtention = ".tka";

}

Player::Player()
{
}

Player::~Player()
{
	
}

// const縺ｧ繝輔ぃ繧､繝ｫ繧定ｪｭ縺ｿ蜿悶ｋ縲・
void Player::SetAnimation(EnAnimationClip animationClip , std::string animationFileName, bool loopFlag)
{
	// 蜈ｱ騾壼喧縺励◆繝輔ぃ繧､繝ｫ蜷阪・
	std::string FileName = animationFilePath + animationFileName + animationExtention;
	//std::strinstr();
	// c_str()繝｡繧ｾ繝・ヨ繧貞他縺ｳ蜃ｺ縺吶％縺ｨ縺ｧ const char* 縺ｫ螟画鋤縺輔ｌ繧九・
	m_animationClips[animationClip].Load(FileName.c_str());
	m_animationClips[animationClip].SetLoopFlag(loopFlag);
}

// bool竊・true縺ｨfalse繧貞愛蛻･縺吶ｋ縲・縺薙・2遞ｮ鬘槭・蛟､縺励°蜿悶ｌ縺ｪ縺・・
bool Player::Start()
{
	// 蠕・ｩ溘い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縲・
	SetAnimation(enAnimClip_Idle, "playerIdle", true);
	// 豁ｩ縺阪い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縲・
	SetAnimation(enAnimClip_Walk, "playerWalking", true);
	// 襍ｰ繧翫い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縲・
	SetAnimation(enAnimClip_Run, "playerRunning", true);
	// 縺励ｃ縺後∩繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縲・
	SetAnimation(enAnimClip_Crouch, "playerCrouch", true);
	// 縺励ｃ縺後∩豁ｩ縺阪い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縲・
	SetAnimation(enAnimClip_CrouchWalk, "playerCrouched walking", true);

	// 繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ繧定ｪｭ縺ｿ霎ｼ繧縲・
	m_modelRender.Init("Assets/modelData/player/player.tkm", m_animationClips, enAnimationClip_Num);//m_animationClips=菴慕ｨｮ鬘槭≠繧九°
	/*ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/player/player.tkm";
	modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	modelInitData.m_vsSkinEntryPointFunc = "VSMainSkin";
	modelInitData.m_psEntryPointFunc = "PSMainHardShadow";
	modelInitData.animationClips = m_animationClips;
	modelInitData.numAnimationClips = enAnimationClip_Num;
	m_modelRender.InitForwardRendering(modelInitData);*/
	// 繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ縺ｮ譖ｴ譁ｰ縲・
	m_modelRender.Update();
	// 繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ縺ｮ蜷代″繧貞､峨∴繧九・
	rotation.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(rotation);
	//繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ繧ｳ繝ｳ繝医Ο繝ｼ繝ｩ繝ｼ繧貞・譛溷喧縺吶ｋ
	m_charCon.Init(25.0f, 75.0f, m_position);

	return true;
}

void Player::Update() {
	Move();					//繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ縺ｮ遘ｻ蜍・
	Rotation();				//繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ縺ｮ蝗櫁ｻ｢
	ManageState();			//繧ｹ繝・・繝育ｮ｡逅・・
	SutaminaCalk();
	PlayAnimation();		//繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ蜀咲函縲・
	m_modelRender.Update();	//繝｢繝・Ν譖ｴ譁ｰ
}

void Player::Move() {
	// 荵礼ｮ礼畑
	float m_dash = 1.0f;
	// 繧ゅ＠A繝懊ち繝ｳ縺梧款縺輔ｌ縺溘ｉ縲・
	if (g_pad[0]->IsPress(enButtonA))
	{
		// 遘ｻ蜍暮溷ｺｦ繧剃ｸ翫￡繧九・
		m_dash *= 2.0f;

		if (m_sutamina <= 0.0f)
		{
			m_dash /= m_dash;
		}
	}
	// 繧ゅ＠B繝懊ち繝ｳ縺梧款縺輔ｌ縺溘ｉ縲・
	else if (g_pad[0]->IsPress(enButtonB))
	{
		m_dash *= 0.5f;
	}

	// xz縺ｮ遘ｻ蜍暮溷ｺｦ繧・.0f縺ｫ縺吶ｋ縲・
	// 0.0f縺ｧ蛻晄悄蛹悶☆繧九％縺ｨ縺ｧ蜑榊屓縺ｮ遘ｻ蜍暮溷ｺｦ縺ｮ蠖ｱ髻ｿ繧・
	// 蜿励￠縺壹↓譁ｰ縺励＞蜈･蜉帙↓蝓ｺ縺･縺・◆遘ｻ蜍輔′蜿ｯ閭ｽ縲・
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//蟾ｦ繧ｹ繝・ぅ繝・け縺ｮ蜈･蜉幃㍼繧貞叙蠕励・
	//繧ｹ繝・ぅ繝・け縺ｮ豌ｴ蟷ｳ譁ｹ蜷代・
	stickL.x = g_pad[0]->GetLStickXF();
	//繧ｹ繝・ぅ繝・け縺ｮ蝙ら峩譁ｹ蜷代・
	stickL.y = g_pad[0]->GetLStickYF();

	//繧ｫ繝｡繝ｩ縺ｮ蜑肴婿蜷代→蜿ｳ譁ｹ蜷代・繝吶け繝医Ν繧呈戟縺｣縺ｦ縺上ｋ縲・
	//繝励Ξ繧､繝､繝ｼ縺後←縺ｮ譁ｹ蜷代↓遘ｻ蜍輔☆繧九°繧呈ｱｺ繧√ｋ縲・
	//繧ｫ繝｡繝ｩ縺ｮ蜑肴婿蜷代・繝吶け繝医Ν繧貞叙蠕励・
	Vector3 forward = g_camera3D->GetForward();
	//繧ｫ繝｡繝ｩ縺ｮ蜿ｳ譁ｹ蜷代・繝吶け繝医Ν繧貞叙蠕励・
	Vector3 right = g_camera3D->GetRight();
	//y譁ｹ蜷代↓縺ｯ遘ｻ蜍輔＆縺帙↑縺・・
	//縺薙≧縺吶ｋ縺薙→縺ｧ繝励Ξ繧､繝､繝ｼ縺ｯ蝨ｰ髱｢荳翫〒縺ｮ縺ｿ遘ｻ蜍輔☆繧九・
	forward.y = 0.0f;
	right.y = 0.0f;

	//蟾ｦ繧ｹ繝・ぅ繝・け縺ｮ蜈･蜉幃㍼縺ｨ180.0f繧・
	// 荵礼ｮ励・
	//遘ｻ蜍暮溷ｺｦ繧呈ｱｺ繧√ｋ縲・
	right	*= stickL.x * 180.0f * m_dash * m_moveDir;
	forward *= stickL.y * 180.0f * m_dash * m_moveDir;

	/*right *= stickL.x * 500.0f * m_dash * m_moveDir;
	forward *= stickL.y * 500.0f * m_dash * m_moveDir;*/

	//遘ｻ蜍暮溷ｺｦ縺ｫ繧ｹ繝・ぅ繝・け縺ｮ蜈･蜉幃㍼繧貞刈邂励☆繧九・
	// m_run竊偵ム繝・す繝･譎ら畑縺ｮ螟画焚縲・
	m_moveSpeed += right + forward;

	//蝨ｰ髱｢縺ｫ莉倥＞縺ｦ縺・◆繧峨・
	if (m_charCon.IsOnGround())
	{
		//驥榊鴨繧堤┌縺上☆縲・
		m_moveSpeed.y = 0.0f;
	}
	//蝨ｰ髱｢縺ｫ莉倥＞縺ｦ縺・↑縺九▲縺溘ｉ縲・
	else
	{
		//驥榊鴨繧堤匱逕溘＆縺帙ｋ縲・
		m_moveSpeed.y -= 5.0f;
	}
	

	//繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ繧ｳ繝ｳ繝医Ο繝ｼ繝ｩ繝ｼ繧剃ｽｿ縺｣縺ｦ蠎ｧ讓吶ｒ遘ｻ蜍輔＆縺帙ｋ縲・
	m_position = m_charCon.Execute(m_moveSpeed, 1.0f / 60.0f);
	//邨ｵ謠上″縺輔ｓ縺ｫ蠎ｧ讓吶ｒ謨吶∴繧九・
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{//x縺吸縺ｮ遘ｻ蜍暮溷ｺｦ縺後≠縺｣縺溘ｉ(繧ｹ繝・ぅ繝・け縺ｮ蜈･蜉帙′縺ゅ▲縺溘ｉ)縲・
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ縺ｮ譁ｹ蜷代ｒ螟峨∴繧九・
		rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//邨ｵ謠上″縺輔ｓ縺ｫ蝗櫁ｻ｢繧呈蕗縺医ｋ縲・
		m_modelRender.SetRotation(rotation);
	}
}

void Player::StateManagement()
{
	// todo:tamaki 
	// switch譁・ｒ縺薙％縺ｫ蜈･繧後ｋ縲ゅ・
	// enum縺ｮ蜷榊燕縺ｯMove縺ｧ縺殻縲・縲・
	// 繝励Ξ繧､繝､繝ｼ繧ｹ繝・・繝医・驟榊・繧剃ｽ懊ｋ縲・
	// 縺昴・驟榊・縺ｮ荳ｭ縺ｫplayerMove繧аlayerRun縺ｨ縺九・繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ縺悟・繧九・
	// 繝ｪ繧ｯ繧ｨ繧ｹ繝医せ繝・・繝医・繝｡繝ｳ繝仙､画焚繧剃ｽ懊ｋ縲ゅ・
	// switch譁・・蠢・ｦ√↑縺・庄閭ｽ諤ｧ縺悟､ｧ縲・

	//switch譁・・
	//switch (m_currentState) {
	//	// 繧ｹ繝・・繝医′Idle縺縺｣縺溘ｉ縲・
	//case State_Idle:
	//	//蠕・ｩ溘い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
	//	m_modelRender.PlayAnimation(enAnimClip_Idle);
	//	break;
	//	// 繧ｹ繝・・繝医′Walk縺縺｣縺溘ｉ縲・
	//case State_Walk:
	//	//豁ｩ縺阪い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
	//	m_modelRender.PlayAnimation(enAnimClip_Walk);
	//	break;
	//case State_StayRun:
	//	//豁ｩ縺阪い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
	//	m_modelRender.PlayAnimation(enAnimClip_Walk);
	//	break;
	//	// 繧ｹ繝・・繝医′Run縺縺｣縺溘ｉ縲・
	//case State_Run:
	//	// 襍ｰ繧翫い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
	//	m_modelRender.PlayAnimation(enAnimClip_Run);
	//	break;
	//	// 繧ｹ繝・・繝医′Crouch縺縺｣縺溘ｉ縲・
	//case State_Crouch:
	//	// 縺励ｃ縺後∩繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
	//	m_modelRender.PlayAnimation(enAnimClip_Crouch);
	//	break;
	//	// 繧ｹ繝・・繝医′CrouchWalk縺縺｣縺溘ｉ縲・
	//case State_CrouchWalk:
	//	// 縺励ｃ縺後∩豁ｩ縺阪い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
	//	m_modelRender.PlayAnimation(enAnimClip_CrouchWalk);
	//	break;
	//	// 繧ｹ繝・・繝医′Crouching縺縺｣縺溘ｉ縲・
	//case State_Crouching:
	//	// 縺励ｃ縺後∩縺薙∩繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
	//	m_modelRender.PlayAnimation(enAnimClip_Crouching);
	//	break;
	//	// 繧ｹ繝・・繝医′CrouchStanding縺縺｣縺溘ｉ縲・
	//case State_CrouchStanding:
	//	// 遶九■荳翫′繧翫い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
	//	m_modelRender.PlayAnimation(enAnimClip_CrouchStanding);
	//	break;
	//}

	// Move[];
}

//繧ｹ繝・・繝育ｮ｡逅・・
void Player::ManageState()
{
	//蝨ｰ髱｢縺ｫ莉倥＞縺ｦ縺・◆繧峨・
	//x縺吸縺ｮ遘ｻ蜍暮溷ｺｦ縺後≠縺｣縺溘ｉ(繧ｹ繝・ぅ繝・け縺ｮ蜈･蜉帙′縺ゅ▲縺溘ｉ)縲・
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//繧ｹ繝・・繝医ｒ2(豁ｩ縺・縺ｫ縺吶ｋ縲・
		m_currentState = State_Walk;
		// 襍ｰ縺｣縺ｦ縺ｪ縺・愛螳壹↓縺吶ｋ縲・
		m_dashFlag = false;

		// 繧ゅ＠A繝懊ち繝ｳ縺梧款縺輔ｌ縺溘ｉ縲・
		if (g_pad[0]->IsPress(enButtonA))
		{
			// 襍ｰ繧九・
			m_currentState = State_Run;
			// 襍ｰ縺｣縺ｦ縺・ｋ蛻､螳壹↓縺吶ｋ縲・
			m_dashFlag = true;

			// 繧ｹ繧ｿ繝溘リ縺・縺ｧ襍ｰ縺｣縺ｦ縺ｪ縺・愛螳壹・縺ｨ縺・
		    if (m_sutamina <= 0 && m_dashFlag != false)
		    {
				// 繝繝・す繝･迥ｶ諷九°繧画ｭｩ縺丞愛螳壹↓縺ｪ繧九・
			    m_currentState = State_StayRun;
		    }
		}
		// 繧ゅ＠B繝懊ち繝ｳ縺梧款縺輔ｌ縺溘ｉ縲・
		else if (g_pad[0]->IsPress(enButtonB))
		{
			// 縺励ｃ縺後・縲・
			m_currentState = State_CrouchWalk;
		}
	}
	//x縺ｨz縺ｮ遘ｻ蜍暮溷ｺｦ縺檎┌縺九▲縺溘ｉ(繧ｹ繝・ぅ繝・け縺ｮ蜈･蜉帙′辟｡縺九▲縺溘ｉ)縲・
	else
	{
		//繧ｹ繝・・繝医ｒ0(蠕・ｩ・縺ｫ縺吶ｋ縲・
		m_currentState = State_Idle;

		// 繧ゅ＠B繝懊ち繝ｳ縺梧款縺輔ｌ縺溘ｉ縲・
		if (g_pad[0]->IsPress(enButtonB))
		{
			// 縺励ｃ縺後・縲・
			m_currentState = State_Crouch;
		}
	}
}

void Player::SutaminaCalk()
{
	// 繝励Ξ繧､繝､繝ｼ縺後ム繝・す繝･縺励※縺溘ｉ縲・
	if (m_currentState == State_Run)
	{
		// 繧ｹ繧ｿ繝溘リ繧呈ｸ帙ｉ縺吶・
		//g_gameTime->GetFrameDeltaTime(); 竊・繝輔Ξ繝ｼ繝繝ｬ繝ｼ繝医↓髢｢菫ゅ↑縺丈ｸ螳壹・繧ｹ繝斐・繝峨〒蜃ｦ逅・ｒ騾ｲ繧√ｉ繧後ｋ縲・
		// 60FPS縺・繝輔Ξ繝ｼ繝縺ｫ縺九°繧区凾髢・竊・1遘・ﾃｷ 60 = 邏・.06遘偵・
		// 縺薙ｌ繧貞･ｽ縺阪↑謨ｰ縺ｧ荵礼ｮ冷・FPS縺ｫ蟾ｦ蜿ｳ縺輔ｌ縺壹↓貂帙ｉ縺帙ｋ縲・
		m_sutamina -= 20.0f * g_gameTime->GetFrameDeltaTime();// 1遘偵〒貂帙ｋ縲・
		// 繧ｹ繧ｿ繝溘リ縺・莉･荳九↓縺ｪ縺｣縺溘ｉ縲・
		if (m_sutamina <= 0)
		{
			// 繧ｹ繧ｿ繝溘リ繧・縺ｫ縺吶ｋ縲・
			m_sutamina = 0;
		}
	}
	// 襍ｰ縺｣縺ｦ縺・↑縺・→縺阪・
	else if(m_dashFlag != true)
	{
		// 繧ｹ繧ｿ繝溘リ繧貞屓蠕ｩ縺吶ｋ縲・
		m_sutamina += 20.0f * g_gameTime->GetFrameDeltaTime();
		// 繧ｹ繧ｿ繝溘リ縺・00莉･荳翫↓縺ｪ縺｣縺溘ｉ縲・
		if (m_sutamina >= 100)
		{
			//繧ｹ繧ｿ繝溘リ繧・00縺ｫ縺吶ｋ縲・
			m_sutamina = m_max_sutamina;
		}
	}
}

//繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ蜀咲函縲・
void Player::PlayAnimation()
{
	//switch譁・・
	switch (m_currentState) {
		// 繧ｹ繝・・繝医′Idle縺縺｣縺溘ｉ縲・
	case State_Idle:
		//蠕・ｩ溘い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
		m_modelRender.PlayAnimation(enAnimClip_Idle);
		break;
		// 繧ｹ繝・・繝医′Walk縺縺｣縺溘ｉ縲・
	case State_Walk:
		//豁ｩ縺阪い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
		m_modelRender.PlayAnimation(enAnimClip_Walk);
		break;
	case State_StayRun:
		//豁ｩ縺阪い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
		m_modelRender.PlayAnimation(enAnimClip_Walk);
		break;
		// 繧ｹ繝・・繝医′Run縺縺｣縺溘ｉ縲・
	case State_Run:
		// 襍ｰ繧翫い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
		m_modelRender.PlayAnimation(enAnimClip_Run);
		break;
		// 繧ｹ繝・・繝医′Crouch縺縺｣縺溘ｉ縲・
	case State_Crouch:
		// 縺励ｃ縺後∩繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
		m_modelRender.PlayAnimation(enAnimClip_Crouch);
		break;
		// 繧ｹ繝・・繝医′CrouchWalk縺縺｣縺溘ｉ縲・
	case State_CrouchWalk:
		// 縺励ｃ縺後∩豁ｩ縺阪い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
		m_modelRender.PlayAnimation(enAnimClip_CrouchWalk);
		break;
		// 繧ｹ繝・・繝医′Crouching縺縺｣縺溘ｉ縲・
	case State_Crouching:
		// 縺励ｃ縺後∩縺薙∩繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
		m_modelRender.PlayAnimation(enAnimClip_Crouching);
		break;
		// 繧ｹ繝・・繝医′CrouchStanding縺縺｣縺溘ｉ縲・
	case State_CrouchStanding:
		// 遶九■荳翫′繧翫い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕溘☆繧九・
		m_modelRender.PlayAnimation(enAnimClip_CrouchStanding);
		break;
	}
}


void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}