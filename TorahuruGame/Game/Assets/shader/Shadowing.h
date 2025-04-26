// 繧ｷ繝｣繝峨え繧､繝ｳ繧ｰ髢｢菫ゅ・蜃ｦ逅・・

#ifndef _SHADOWING_H_
#define _SHADOWING_H_

#include "Shadowing_const.h"
#include "PBRLighting_Const.h"

static const int INFINITY = 40.0f; 

///////////////////////////////////////
// 繧ｵ繝ｳ繝励Λ繧ｹ繝・・繝医・
///////////////////////////////////////
#include "Sampler.h"

// 繝√ぉ繝薙す繧ｧ繝輔・荳咲ｭ牙ｼ上ｒ蛻ｩ逕ｨ縺励※縲∝ｽｱ縺ｫ縺ｪ繧句庄閭ｽ諤ｧ繧定ｨ育ｮ励☆繧九・
float Chebyshev(float2 moments, float depth)
{
    if (depth <= moments.x) {
		return 0.0;
	}
    // 驕ｮ阡ｽ縺輔ｌ縺ｦ縺・ｋ縺ｪ繧峨√メ繧ｧ繝薙す繧ｧ繝輔・荳咲ｭ牙ｼ上ｒ蛻ｩ逕ｨ縺励※蜈峨′蠖薙◆繧狗｢ｺ邇・ｒ豎ゅａ繧・
    float depth_sq = moments.x * moments.x;
    // 縺薙・繧ｰ繝ｫ繝ｼ繝励・蛻・淵蜈ｷ蜷医ｒ豎ゅａ繧・
    // 蛻・淵縺悟､ｧ縺阪＞縺ｻ縺ｩ縲」ariance縺ｮ謨ｰ蛟､縺ｯ螟ｧ縺阪￥縺ｪ繧・
    float variance = moments.y - depth_sq;
    // 縺薙・繝斐け繧ｻ繝ｫ縺ｮ繝ｩ繧､繝医°繧芽ｦ九◆豺ｱ蠎ｦ蛟､縺ｨ繧ｷ繝｣繝峨え繝槭ャ繝励・蟷ｳ蝮・・豺ｱ蠎ｦ蛟､縺ｮ蟾ｮ繧呈ｱゅａ繧・
    float md = depth - moments.x;
    // 蜈峨′螻翫￥遒ｺ邇・ｒ豎ゅａ繧・
    float lit_factor = variance / (variance + md * md);
    float lig_factor_min = 0.3f;
    // 蜈峨′螻翫￥遒ｺ邇・・荳矩剞莉･荳九・蠖ｱ縺ｫ縺ｪ繧九ｈ縺・↓縺吶ｋ縲・
    lit_factor = saturate((lit_factor - lig_factor_min) / (1.0f - lig_factor_min));
    // 蜈峨′螻翫￥遒ｺ邇・°繧牙ｽｱ縺ｫ縺ｪ繧狗｢ｺ邇・ｒ豎ゅａ繧九・
    return 1.0f - lit_factor;
}
float CalcShadowRate(
    Texture2D<float4> shadowMap[NUM_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP],
    float4x4 mlvp[NUM_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP], 
    int ligNo, 
    float3 worldPos, 
    int isSoftShadow
)
{
    float shadow = 0.0f;
    for(int cascadeIndex = 0; cascadeIndex < NUM_SHADOW_MAP; cascadeIndex++)
    {
        float4 posInLVP = mul( mlvp[ligNo][cascadeIndex], float4( worldPos, 1.0f ));
        float2 shadowMapUV = posInLVP.xy / posInLVP.w;
        float zInLVP = posInLVP.z / posInLVP.w;
        shadowMapUV *= float2(0.5f, -0.5f);
        shadowMapUV += 0.5f;
        // 繧ｷ繝｣繝峨え繝槭ャ繝誘V縺檎ｯ・峇蜀・°蛻､螳・
        if(shadowMapUV.x >= 0.0f && shadowMapUV.x <= 1.0f
            && shadowMapUV.y >= 0.0f && shadowMapUV.y <= 1.0f
            && zInLVP < 0.98f && zInLVP > 0.02f)
        {
            // 繧ｷ繝｣繝峨え繝槭ャ繝励°繧牙､繧偵し繝ｳ繝励Μ繝ｳ繧ｰ
            float4 shadowValue = shadowMap[ligNo][cascadeIndex].Sample(Sampler, shadowMapUV);
            zInLVP -= 0.001f;
            float pos = exp(INFINITY * zInLVP);
            if( isSoftShadow ){
                // 繧ｽ繝輔ヨ繧ｷ繝｣繝峨え縲・
                shadow = Chebyshev(shadowValue.xy, pos);
            }else if(pos >= shadowValue.r ){
                // 繝上・繝峨す繝｣繝峨え縲・
                shadow = 1.0f;
            }
           
            break;
        }
    }
    return shadow;
}

#endif // _SHADOWING_H_