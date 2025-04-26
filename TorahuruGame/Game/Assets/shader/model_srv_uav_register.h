//////////////////////////////////////////////////////////////////////////////
// 繝輔か繝ｯ繝ｼ繝峨Ξ繝ｳ繝繝ｪ繝ｳ繧ｰ縺ｧ菴ｿ逕ｨ縺輔ｌ繧九Δ繝・Ν繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮSRV_UAV繝ｬ繧ｸ繧ｹ繧ｿ險ｭ螳・
//////////////////////////////////////////////////////////////////////////////

#ifndef _MODEL_SRV_UAV_REGISTER_H_
#define _MODEL_SRV_UAV_REGISTER_H_

#include "Shadowing_const.h"

Texture2D<float4> albedoTexture : register(t0);                 // 繧｢繝ｫ繝吶ラ
Texture2D<float4> normalTexture : register(t1);                 // 豕慕ｷ・
Texture2D<float4> metallicShadowSmoothTexture : register(t2);   // 繝｡繧ｿ繝ｪ繝・け縲√す繝｣繝峨え縲√せ繝繝ｼ繧ｹ繝・け繧ｹ繝√Ε縲Ｓ縺ｫ驥大ｱ槫ｺｦ縲“縺ｫ蠖ｱ繝代Λ繝｡繝ｼ繧ｿ縲∥縺ｫ貊代ｉ縺九＆縲・
TextureCube<float4> g_skyCubeMap : register(t11);               // 繧ｹ繧ｫ繧､繧ｭ繝･繝ｼ繝・
Texture2D<float4> g_shadowMap[NUM_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP] : register(t12);  //繧ｷ繝｣繝峨え繝槭ャ繝励・

#endif // _MODEL_SRV_UAV_REGISTER_H_