///////////////////////////////////////
// PBR繝吶・繧ｹ縺ｮ繝・ぅ繝輔ぃ繝ｼ繝峨Λ繧､繝・ぅ繝ｳ繧ｰ縺ｮSRV_UAV繝ｬ繧ｸ繧ｹ繧ｿ險ｭ螳・
///////////////////////////////////////


#ifndef _DEFERREDLIGHTING_SRV_UAV_REGISTER_H_
#define _DEFERREDLIGHTING_SRV_UAV_REGISTER_H_

#include "Shadowing_const.h"

Texture2D<float4> albedoTexture : register(t0);                                         // 繧｢繝ｫ繝吶ラ
Texture2D<float4> normalTexture : register(t1);                                         // 豕慕ｷ・
Texture2D<float4> metallicShadowSmoothTexture : register(t2);                           // 繝｡繧ｿ繝ｪ繝・け縲√す繝｣繝峨え縲√せ繝繝ｼ繧ｹ繝・け繧ｹ繝√Ε縲Ｓ縺ｫ驥大ｱ槫ｺｦ縲“縺ｫ蠖ｱ繝代Λ繝｡繝ｼ繧ｿ縲∥縺ｫ貊代ｉ縺九＆縲・
Texture2D<float4> g_shadowMap[NUM_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP] : register(t3);    // 繧ｷ繝｣繝峨え繝槭ャ繝励・
TextureCube<float4> g_skyCubeMap : register(t15);                                       // 繧ｹ繧ｫ繧､繧ｭ繝･繝ｼ繝・
StructuredBuffer<uint> pointLightListInTile : register(t20);                            // 繧ｿ繧､繝ｫ縺斐→縺ｮ繝昴う繝ｳ繝医Λ繧､繝医・繧､繝ｳ繝・ャ繧ｯ繧ｹ縺ｮ繝ｪ繧ｹ繝・
StructuredBuffer<uint> spotLightListInTile : register(t21);                             // 繧ｿ繧､繝ｫ縺斐→縺ｮ繧ｹ繝昴ャ繝医Λ繧､繝医・繧､繝ｳ繝・ャ繧ｯ繧ｹ縺ｮ繝ｪ繧ｹ繝医・
Texture2D<float4> g_reflectionTextureArray[NUM_REFLECTION_TEXTURE] : register(t22);     // 繝ｪ繝輔Ξ繧ｯ繧ｷ繝ｧ繝ｳ繝・け繧ｹ繝√Ε縲・


#endif // _DEFERREDLIGHTING_SRV_UAV_REGISTER_H_