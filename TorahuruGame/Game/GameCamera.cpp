#include "stdafx.h"
#include "GameCamera.h"
#include"Game.h"
#include"Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//豕ｨ隕也せ縺九ｉ隕也せ縺ｾ縺ｧ縺ｮ繝吶け繝医Ν繧定ｨｭ螳壹・
	m_toCameraPos.Set(0.0f, 150.0f, -300.0f);

	//繝励Ξ繧､繝､繝ｼ縺ｮ繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ繧呈爾縺吶・
	m_player = FindGO<Player>("player");

	// 繝舌ロ繧ｫ繝｡繝ｩ縺ｮ蛻晄悄蛹悶・
	m_springCamera.Init(
		*g_camera3D,   // 繝舌ロ繧ｫ繝｡繝ｩ縺ｮ蜃ｦ逅・ｒ陦後≧繧ｫ繝｡繝ｩ繧呈欠螳壹☆繧九・
		1000.0f,       // 繧ｫ繝｡繝ｩ縺ｮ遘ｻ蜍暮溷ｺｦ縺ｮ譛螟ｧ蛟､縲・
		true,          // 繧ｫ繝｡繝ｩ縺ｨ蝨ｰ蠖｢縺ｨ縺ｮ蠖薙◆繧雁愛螳壹ｒ縺ｨ繧九°縺ｩ縺・°縺ｮ繝輔Λ繧ｰ縲・
		5.0f           // 繧ｫ繝｡繝ｩ縺ｫ險ｭ螳壹＆繧後ｋ逅・ｽ薙さ繝ｪ繧ｸ繝ｧ繝ｳ縺ｮ蜊雁ｾ・らｬｬ3蠑墓焚縺荊rue縺ｮ譎ゅ↓譛牙柑縺ｫ縺ｪ繧九・
	);

	//繧ｫ繝｡繝ｩ縺ｮ繝九い繧ｯ繝ｪ繝・・縺ｨ繝輔ぃ繝ｼ繧ｯ繝ｪ繝・・繧定ｨｭ螳壹☆繧九・
	/*g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(1000000.0f);*/

	return true;
}

void GameCamera::Update()
{

	//繧ｫ繝｡繝ｩ繧呈峩譁ｰ縲・
	//豕ｨ隕也せ繧定ｨ育ｮ励☆繧九・
	Vector3 target = m_player->m_position;
	//繝励Ξ繧､繝､縺ｮ雜ｳ蜈・°繧峨■繧・▲縺ｨ荳翫ｒ豕ｨ隕也せ縺ｨ縺吶ｋ縲・
	target.y += 100.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//繝代ャ繝峨・蜈･蜉帙ｒ菴ｿ縺｣縺ｦ繧ｫ繝｡繝ｩ繧貞屓縺吶・
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y霆ｸ蜻ｨ繧翫・蝗櫁ｻ｢
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_toCameraPos);
	//X霆ｸ蜻ｨ繧翫・蝗櫁ｻ｢縲・
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_toCameraPos);
	//繧ｫ繝｡繝ｩ縺ｮ蝗櫁ｻ｢縺ｮ荳企剞繧偵メ繧ｧ繝・け縺吶ｋ縲・
	//豕ｨ隕也せ縺九ｉ隕也せ縺ｾ縺ｧ縺ｮ繝吶け繝医Ν繧呈ｭ｣隕丞喧縺吶ｋ縲・
	//豁｣隕丞喧縺吶ｋ縺ｨ縲√・繧ｯ繝医Ν縺ｮ螟ｧ縺阪＆縺鯉ｼ代↓縺ｪ繧九・
	//螟ｧ縺阪＆縺鯉ｼ代↓縺ｪ繧九→縺・≧縺薙→縺ｯ縲√・繧ｯ繝医Ν縺九ｉ蠑ｷ縺輔′縺ｪ縺上↑繧翫∵婿蜷代・縺ｿ縺ｮ諠・ｱ縺ｨ縺ｪ繧九→縺・≧縺薙→縲・
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.2f) {
		//繧ｫ繝｡繝ｩ縺御ｸ雁髄縺阪☆縺弱・
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		//繧ｫ繝｡繝ｩ縺御ｸ句髄縺阪☆縺弱・
		m_toCameraPos = toCameraPosOld;
	}

	//隕也せ繧定ｨ育ｮ励☆繧九Ｘ
	Vector3 pos = target + m_toCameraPos;

	// 繝舌ロ繧ｫ繝｡繝ｩ縺ｫ豕ｨ隕也せ縺ｨ隕也せ繧定ｨｭ螳壹☆繧九・
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(target);

	// 繧ｫ繝｡繝ｩ縺ｮ譖ｴ譁ｰ縲・
	m_springCamera.Update();

	//繝｡繧､繝ｳ繧ｫ繝｡繝ｩ縺ｫ豕ｨ隕也せ縺ｨ隕也せ繧定ｨｭ螳壹☆繧九・
	/*g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);*/

	//繧ｫ繝｡繝ｩ縺ｮ譖ｴ譁ｰ縲・
	/*g_camera3D->Update();*/
}