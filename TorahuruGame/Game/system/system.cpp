#include "stdafx.h"
#include "system.h"
#include "graphics/GraphicsEngine.h"
#include "graphics/RenderingEngine.h"
#include "sound/SoundEngine.h"

HWND			g_hWnd = NULL;				//繧ｦ繧｣繝ｳ繝峨え繝上Φ繝峨Ν縲・

///////////////////////////////////////////////////////////////////
//繝｡繝・そ繝ｼ繧ｸ繝励Ο繧ｷ繝ｼ繧ｸ繝｣縲・
//hWnd縺後Γ繝・そ繝ｼ繧ｸ繧帝√▲縺ｦ縺阪◆繧ｦ繧｣繝ｳ繝峨え縺ｮ繝上Φ繝峨Ν縲・
//msg縺後Γ繝・そ繝ｼ繧ｸ縺ｮ遞ｮ鬘槭・
//wParam縺ｨlParam縺ｯ蠑墓焚縲ゆｻ翫・豌励↓縺励↑縺上※繧医＞縲・
///////////////////////////////////////////////////////////////////
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//騾√ｉ繧後※縺阪◆繝｡繝・そ繝ｼ繧ｸ縺ｧ蜃ｦ逅・ｒ蛻・ｲ舌＆縺帙ｋ縲・
	switch (msg)
	{
	case WM_DESTROY:
		//繧ｹ繧ｨ繝ｳ繧ｸ繝ｳ縺ｮ遐ｴ譽・・
		PostQuitMessage(0);
		break;	
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

///////////////////////////////////////////////////////////////////
// 繧ｦ繧｣繝ｳ繝峨え縺ｮ蛻晄悄蛹悶・
///////////////////////////////////////////////////////////////////
void InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName)
{
	//繧ｦ繧｣繝ｳ繝峨え繧ｯ繝ｩ繧ｹ縺ｮ繝代Λ繝｡繝ｼ繧ｿ繧定ｨｭ螳・蜊倥↑繧区ｧ矩菴薙・螟画焚縺ｮ蛻晄悄蛹悶〒縺吶・
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),		//讒矩菴薙・繧ｵ繧､繧ｺ縲・
		CS_CLASSDC,				//繧ｦ繧｣繝ｳ繝峨え縺ｮ繧ｹ繧ｿ繧､繝ｫ縲・
								//縺薙％縺ｮ謖・ｮ壹〒繧ｹ繧ｯ繝ｭ繝ｼ繝ｫ繝舌・繧偵▽縺代◆繧翫〒縺阪ｋ縺後√ご繝ｼ繝縺ｧ縺ｯ荳崎ｦ√↑縺ｮ縺ｧCS_CLASSDC縺ｧ繧医＞縲・
		MsgProc,				//繝｡繝・そ繝ｼ繧ｸ繝励Ο繧ｷ繝ｼ繧ｸ繝｣(蠕瑚ｿｰ)
		0,						//0縺ｧ縺・＞縲・
		0,						//0縺ｧ縺・＞縲・
		GetModuleHandle(NULL),	//縺薙・繧ｯ繝ｩ繧ｹ縺ｮ縺溘ａ縺ｮ繧ｦ繧､繝ｳ繝峨え繝励Ο繧ｷ繝ｼ繧ｸ繝｣縺後≠繧九う繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ繝上Φ繝峨Ν縲・
								//菴輔ｂ豌励↓縺励↑縺上※繧医＞縲・
		NULL,					//繧｢繧､繧ｳ繝ｳ縺ｮ繝上Φ繝峨Ν縲ゅい繧､繧ｳ繝ｳ繧貞､峨∴縺溘＞蝣ｴ蜷医％縺薙ｒ螟画峩縺吶ｋ縲ゅ→繧翫≠縺医★縺薙ｌ縺ｧ縺・＞縲・
		NULL,					//繝槭え繧ｹ繧ｫ繝ｼ繧ｽ繝ｫ縺ｮ繝上Φ繝峨Ν縲・ULL縺ｮ蝣ｴ蜷医・繝・ヵ繧ｩ繝ｫ繝医・
		NULL,					//繧ｦ繧｣繝ｳ繝峨え縺ｮ閭梧勹濶ｲ縲・ULL縺ｮ蝣ｴ蜷医・繝・ヵ繧ｩ繝ｫ繝医・
		NULL,					//繝｡繝九Η繝ｼ蜷阪・ULL縺ｧ縺・＞縲・
		appName,				//繧ｦ繧｣繝ｳ繝峨え繧ｯ繝ｩ繧ｹ縺ｫ莉倥￠繧句錐蜑阪・
		NULL					//NULL縺ｧ縺・＞縲・
	};
	//繧ｦ繧｣繝ｳ繝峨え繧ｯ繝ｩ繧ｹ縺ｮ逋ｻ骭ｲ縲・
	RegisterClassEx(&wc);

	// 繧ｦ繧｣繝ｳ繝峨え縺ｮ菴懈・縲・
	g_hWnd = CreateWindow(
		appName,				//菴ｿ逕ｨ縺吶ｋ繧ｦ繧｣繝ｳ繝峨え繧ｯ繝ｩ繧ｹ縺ｮ蜷榊燕縲・
								//蜈医⊇縺ｩ菴懈・縺励◆繧ｦ繧｣繝ｳ繝峨え繧ｯ繝ｩ繧ｹ縺ｨ蜷後§蜷榊燕縺ｫ縺吶ｋ縲・
		appName,				//繧ｦ繧｣繝ｳ繝峨え縺ｮ蜷榊燕縲ゅえ繧｣繝ｳ繝峨え繧ｯ繝ｩ繧ｹ縺ｮ蜷榊燕縺ｨ蛻･蜷阪〒繧ゅｈ縺・・
		WS_OVERLAPPEDWINDOW,	//繧ｦ繧｣繝ｳ繝峨え繧ｹ繧ｿ繧､繝ｫ縲ゅご繝ｼ繝縺ｧ縺ｯ蝓ｺ譛ｬ逧・↓WS_OVERLAPPEDWINDOW縺ｧ縺・＞縲・
		0,						//繧ｦ繧｣繝ｳ繝峨え縺ｮ蛻晄悄X蠎ｧ讓吶・
		0,						//繧ｦ繧｣繝ｳ繝峨え縺ｮ蛻晄悄Y蠎ｧ讓吶・
		FRAME_BUFFER_W,			//繧ｦ繧｣繝ｳ繝峨え縺ｮ蟷・・
		FRAME_BUFFER_H,			//繧ｦ繧｣繝ｳ繝峨え縺ｮ鬮倥＆縲・
		NULL,					//隕ｪ繧ｦ繧｣繝ｳ繝峨え縲ゅご繝ｼ繝縺ｧ縺ｯ蝓ｺ譛ｬ逧・↓NULL縺ｧ縺・＞縲・
		NULL,					//繝｡繝九Η繝ｼ縲ゆｻ翫・NULL縺ｧ縺・＞縲・
		hInstance,				//繧｢繝励Μ繧ｱ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ縲・
		NULL
	);

	ShowWindow(g_hWnd, nCmdShow);

}


//繧ｲ繝ｼ繝縺ｮ蛻晄悄蛹悶・
void InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName)
{
	//繧ｦ繧｣繝ｳ繝峨え繧貞・譛溷喧縲・
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, appName);
	//k2繧ｨ繝ｳ繧ｸ繝ｳ縺ｮ蛻晄悄蛹悶・
	K2Engine::InitData initData;
	initData.isSoftShadow = true;
	initData.frameBufferWidth = FRAME_BUFFER_W;
	initData.frameBufferHeight = FRAME_BUFFER_H;
	initData.hwnd = g_hWnd;
	K2Engine::CreateInstance(initData);
}
//繧ｦ繧｣繝ｳ繝峨え繝｡繝・そ繝ｼ繧ｸ繧偵ョ繧｣繧ｹ繝代ャ繝√Ｇalse縺瑚ｿ斐▲縺ｦ縺阪◆繧峨√ご繝ｼ繝邨ゆｺ・・
bool DispatchWindowMessage()
{
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		//繧ｦ繧｣繝ｳ繝峨え縺九ｉ縺ｮ繝｡繝・そ繝ｼ繧ｸ繧貞女縺大叙繧九・
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//繧ｦ繧｣繝ｳ繝峨え繝｡繝・そ繝ｼ繧ｸ縺檎ｩｺ縺ｫ縺ｪ縺｣縺溘・
			break;
		}
	}
	return msg.message != WM_QUIT;
}
