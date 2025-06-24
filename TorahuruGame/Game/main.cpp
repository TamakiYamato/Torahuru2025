#include "stdafx.h"
#include "system/system.h"

#include<InitGUID.h>
#include<dxgidebug.h>
#include "GameManager.h"


void ReportLiveObjects()
{
	//IDXGIDebug* pDxgiDebug;

	//typedef HRESULT(__stdcall* fPtr)(const IID&, void**);
	//HMODULE hDll = GetModuleHandleW(L"dxgidebug.dll");
	//fPtr DXGIGetDebugInterface = (fPtr)GetProcAddress(hDll, "DXGIGetDebugInterface");

	//DXGIGetDebugInterface(__uuidof(IDXGIDebug), (void**)&pDxgiDebug);

	//// 蜃ｺ蜉帙・
	//pDxgiDebug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_DETAIL);
}

///////////////////////////////////////////////////////////////////
// 繧ｦ繧｣繝ｳ繝峨え繝励Ο繧ｰ繝ｩ繝縺ｮ繝｡繧､繝ｳ髢｢謨ｰ縲・
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//繧ｲ繝ｼ繝縺ｮ蛻晄悄蛹悶・
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	//////////////////////////////////////
	// 縺薙％縺九ｉ蛻晄悄蛹悶ｒ陦後≧繧ｳ繝ｼ繝峨ｒ險倩ｿｰ縺吶ｋ縲・
	//////////////////////////////////////

	//Game繧ｯ繝ｩ繧ｹ縺ｮ繧ｪ繝悶ず繧ｧ繧ｯ繝医ｒ菴懈・縲・
	NewGO<GameManager>(0, "gameManager");
	
	//////////////////////////////////////
	// 蛻晄悄蛹悶ｒ陦後≧繧ｳ繝ｼ繝峨ｒ譖ｸ縺上・縺ｯ縺薙％縺ｾ縺ｧ・・ｼ・ｼ・
	//////////////////////////////////////
	
	// 縺薙％縺九ｉ繧ｲ繝ｼ繝繝ｫ繝ｼ繝励・
	while (DispatchWindowMessage())
	{
		if (g_pad[0]->IsTrigger(enButtonA) ){
			g_pad[0]->SetVibration(/*durationSec=*/0.5f, /*normalizedPower=*/1.0f);
		}
		//Scene_Manager::GetInstance()->Update();
		K2Engine::GetInstance()->Execute();
	}

	K2Engine::DeleteInstance();

#ifdef _DEBUG
	ReportLiveObjects();
#endif // _DEBUG
	return 0;
}

