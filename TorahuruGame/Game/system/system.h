#pragma once

class GraphicsEngine;
extern HWND			g_hWnd ;				//繧ｦ繧｣繝ｳ繝峨え繝上Φ繝峨Ν縲・

//繧ｲ繝ｼ繝縺ｮ蛻晄悄蛹悶・
void InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
//繧ｦ繧｣繝ｳ繝峨え繝｡繝・そ繝ｼ繧ｸ繧偵ョ繧｣繧ｹ繝代ャ繝√Ｇalse縺瑚ｿ斐▲縺ｦ縺阪◆繧峨√ご繝ｼ繝邨ゆｺ・・
bool DispatchWindowMessage();