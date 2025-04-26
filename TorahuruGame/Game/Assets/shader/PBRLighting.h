///////////////////////////////////////
// PBR繝ｩ繧､繝育畑縺ｮ繝倥ャ繝繝ｼ繝輔ぃ繧､繝ｫ
// 縺薙・繝倥ャ繝繝ｼ繝輔ぃ繧､繝ｫ縺ｯ3dsMax縺ｧ繧ゆｽｿ逕ｨ縺励※縺・∪縺吶・
///////////////////////////////////////

#ifndef _PBRLIGHTING_H_
#define _PBRLIGHTING_H_

///////////////////////////////////////
// 螳壽焚
///////////////////////////////////////
#include "PBRLighting_const.h"

///////////////////////////////////////
// 讒矩菴・
///////////////////////////////////////
#include "PBRLighting_struct.h"

// 縺薙ｌ繧峨・3dsMax縺ｧ縺ｯ荳崎ｦ√・
#ifndef _MAX_

///////////////////////////////////////
// 螳壽焚繝舌ャ繝輔ぃ縲・
///////////////////////////////////////

// 繝ｩ繧､繝育畑縺ｮ螳壽焚繝舌ャ繝輔ぃ繝ｼ
cbuffer cb_0 : register(b1)
{
    LightCB light;  // 繝ｩ繧､繝医ョ繝ｼ繧ｿ
};


#endif // #ifdef _MAX_

///////////////////////////////////////
// 髢｢謨ｰ
///////////////////////////////////////

// 繝吶ャ繧ｯ繝槭Φ蛻・ｸ・ｒ險育ｮ励☆繧・
float Beckmann(float m, float t)
{
    float t2 = t * t;
    float t4 = t * t * t * t;
    float m2 = m * m;
    float D = 1.0f / (4.0f * m2 * t4);
    D *= exp((-1.0f / m2) * (1.0f-t2)/ t2);
    return D;
}

// 繝輔Ξ繝阪Ν繧定ｨ育ｮ励４chlick霑台ｼｼ繧剃ｽｿ逕ｨ
float SpcFresnel(float f0, float u)
{
    // from Schlick
    return f0 + (1-f0) * pow(1-u, 5);
}

/// <summary>
/// 繧ｯ繝・け繝医Λ繝ｳ繧ｹ繝｢繝・Ν縺ｮ髀｡髱｢蜿榊ｰ・ｒ險育ｮ・
/// </summary>
/// <param name="L">蜈画ｺ舌↓蜷代°縺・・繧ｯ繝医Ν</param>
/// <param name="V">隕也せ縺ｫ蜷代°縺・・繧ｯ繝医Ν</param>
/// <param name="N">豕慕ｷ壹・繧ｯ繝医Ν</param>
/// <param name="smooth">貊代ｉ縺九＆</param>
float CookTorranceSpecular(float3 L, float3 V, float3 N, float smooth)
{
    // 繝槭う繧ｯ繝ｭ繝輔ぃ繧ｻ繝・ヨ縺悟ｰ上＆縺上↑繧翫☆縺弱ｋ縺ｨ縲・升髱｢蜿榊ｰ・′蠑ｷ縺上↑繧翫☆縺弱ｋ縺薙→縺後≠繧九・縺ｧ縲・
    // 荳矩剞繧・.5縺ｫ縺励◆縲・
    float microfacet = min( 0.5f, 1.0f - smooth );

    // 驥大ｱ槫ｺｦ繧貞桙逶ｴ蜈･蟆・・譎ゅ・繝輔Ξ繝阪Ν蜿榊ｰ・紫縺ｨ縺励※謇ｱ縺・
    // 驥大ｱ槫ｺｦ縺碁ｫ倥＞縺ｻ縺ｩ繝輔Ξ繝阪Ν蜿榊ｰ・・螟ｧ縺阪￥縺ｪ繧・
    float f0 = 0.5;

    // 繝ｩ繧､繝医↓蜷代°縺・・繧ｯ繝医Ν縺ｨ隕也ｷ壹↓蜷代°縺・・繧ｯ繝医Ν縺ｮ繝上・繝輔・繧ｯ繝医Ν繧呈ｱゅａ繧・
    float3 H = normalize(L + V);

    // 蜷・ｨｮ繝吶け繝医Ν縺後←繧後￥繧峨＞莨ｼ縺ｦ縺・ｋ縺九ｒ蜀・ｩ阪ｒ蛻ｩ逕ｨ縺励※豎ゅａ繧・
    float NdotH = max( saturate(dot(N, H)), 0.001f );
    float VdotH = max( saturate(dot(V, H)), 0.001f );
    float NdotL = max( saturate(dot(N, L)), 0.001f );
    float NdotV = max( saturate(dot(N, V)), 0.001f );

    // D鬆・ｒ繝吶ャ繧ｯ繝槭Φ蛻・ｸ・ｒ逕ｨ縺・※險育ｮ励☆繧・
    float D = Beckmann(microfacet, NdotH);

    // F鬆・ｒSchlick霑台ｼｼ繧堤畑縺・※險育ｮ励☆繧・
    float F = SpcFresnel(f0, VdotH);

    // G鬆・ｒ豎ゅａ繧・
    float G = min(1.0f, min(2*NdotH*NdotV/VdotH, 2*NdotH*NdotL/VdotH));

    // m鬆・ｒ豎ゅａ繧・
    float m = PI * NdotV * NdotH;

    // 縺薙％縺ｾ縺ｧ豎ゅａ縺溘∝､繧貞茜逕ｨ縺励※縲√け繝・け繝医Λ繝ｳ繧ｹ繝｢繝・Ν縺ｮ髀｡髱｢蜿榊ｰ・ｒ豎ゅａ繧・
    return max(F * D * G / m, 0.0);
}

/// <summary>
/// 繝輔Ξ繝阪Ν蜿榊ｰ・ｒ閠・・縺励◆諡｡謨｣蜿榊ｰ・ｒ險育ｮ・
/// </summary>
/// <remark>
/// 縺薙・髢｢謨ｰ縺ｯ繝輔Ξ繝阪Ν蜿榊ｰ・ｒ閠・・縺励◆諡｡謨｣蜿榊ｰ・紫繧定ｨ育ｮ励＠縺ｾ縺・
/// 繝輔Ξ繝阪Ν蜿榊ｰ・・縲∝・縺檎黄菴薙・陦ｨ髱｢縺ｧ蜿榊ｰ・☆繧狗樟雎｡縺ｮ縺ｨ縺薙〒縲・升髱｢蜿榊ｰ・・蠑ｷ縺輔↓縺ｪ繧翫∪縺・
/// 荳譁ｹ諡｡謨｣蜿榊ｰ・・縲∝・縺檎黄菴薙・蜀・Κ縺ｫ蜈･縺｣縺ｦ縲∝・驛ｨ骭ｯ荵ｱ繧定ｵｷ縺薙＠縺ｦ縲∵僑謨｣縺励※蜿榊ｰ・＠縺ｦ縺阪◆蜈峨・縺薙→縺ｧ縺・
/// 縺､縺ｾ繧翫ヵ繝ｬ繝阪Ν蜿榊ｰ・′蠑ｱ縺・→縺阪↓縺ｯ縲∵僑謨｣蜿榊ｰ・′螟ｧ縺阪￥縺ｪ繧翫√ヵ繝ｬ繝阪Ν蜿榊ｰ・′蠑ｷ縺・→縺阪・縲∵僑謨｣蜿榊ｰ・′蟆上＆縺上↑繧翫∪縺・
///
/// </remark>
/// <param name="N">豕慕ｷ・/param>
/// <param name="L">蜈画ｺ舌↓蜷代°縺・・繧ｯ繝医Ν縲ょ・縺ｮ譁ｹ蜷代→騾・髄縺阪・繝吶け繝医Ν縲・/param>
/// <param name="V">隕也ｷ壹↓蜷代°縺・・繧ｯ繝医Ν縲・/param>
/// <param name="roughness">邊励＆縲・・・縺ｮ遽・峇縲・/param>
float CalcDiffuseFromFresnel(float3 N, float3 L, float3 V, float smooth)
{
    // step-1 繝・ぅ繧ｺ繝九・繝吶・繧ｹ縺ｮ繝輔Ξ繝阪Ν蜿榊ｰ・↓繧医ｋ諡｡謨｣蜿榊ｰ・ｒ逵滄擇逶ｮ縺ｫ螳溯｣・☆繧九・
    // 蜈画ｺ舌↓蜷代°縺・・繧ｯ繝医Ν縺ｨ隕也ｷ壹↓蜷代°縺・・繧ｯ繝医Ν縺ｮ繝上・繝輔・繧ｯ繝医Ν繧呈ｱゅａ繧・
    float3 H = normalize(L+V);
    
    //邊励＆縺ｯ0.5縺ｧ蝗ｺ螳壹・
    float roughness = 1.0f - smooth;
    
    //縺薙ｌ縺ｯ
    float energyBias = lerp(0.0f, 0.5f, roughness);
    float energyFactor = lerp(1.0, 1.0/1.51, roughness);

    // 蜈画ｺ舌↓蜷代°縺・・繧ｯ繝医Ν縺ｨ繝上・繝輔・繧ｯ繝医Ν縺後←繧後□縺台ｼｼ縺ｦ縺・ｋ縺九ｒ蜀・ｩ阪〒豎ゅａ繧・
    float dotLH = saturate(dot(L,H));
    // 蜈画ｺ舌↓蜷代°縺・・繧ｯ繝医Ν縺ｨ繝上・繝輔・繧ｯ繝医Ν縲∝・縺悟ｹｳ陦後↓蜈･蟆・＠縺溘→縺阪・諡｡謨｣蜿榊ｰ・㍼繧呈ｱゅａ縺ｦ縺・ｋ縲・
    float Fd90 = energyBias + 2.0 * dotLH * dotLH * roughness;
    
    // 豕慕ｷ壹→蜈画ｺ舌↓蜷代°縺・・繧ｯ繝医Ν・励ｒ蛻ｩ逕ｨ縺励※諡｡謨｣蜿榊ｰ・紫繧呈ｱゅａ縺ｦ縺・∪縺・
    float dotNL = saturate(dot(N,L));
    float FL = (1 + (Fd90 - 1) * pow(1 - dotNL, 5));

    
    // 豕慕ｷ壹→隕也せ縺ｫ蜷代°縺・・繧ｯ繝医Ν繧貞茜逕ｨ縺励※諡｡謨｣蜿榊ｰ・紫繧呈ｱゅａ縺ｦ縺・∪縺・
    float dotNV = saturate(dot(N,V));
    float FV =  (1 + (Fd90 - 1) * pow(1 - dotNV, 5));

    //豕慕ｷ壹→蜈画ｺ舌∈縺ｮ譁ｹ蜷代↓萓晏ｭ倥☆繧区僑謨｣蜿榊ｰ・紫縺ｨ縲∵ｳ慕ｷ壹→隕也せ繝吶け繝医Ν縺ｫ萓晏ｭ倥☆繧区僑謨｣蜿榊ｰ・紫繧・
    // 荵礼ｮ励＠縺ｦ譛邨ら噪縺ｪ諡｡謨｣蜿榊ｰ・紫繧呈ｱゅａ縺ｦ縺・ｋ縲１I縺ｧ髯､邂励＠縺ｦ縺・ｋ縺ｮ縺ｯ豁｣隕丞喧繧定｡後≧縺溘ａ
    return (FL*FV * energyFactor);
}



// 蜿榊ｰ・・繧定ｨ育ｮ励☆繧九・
float3 CalcLighting(
    float3 ligDir, 
    float3 ligColor, 
    float3 normal,
    float3 toEye, 
    float4 albedoColor,  
    float metaric, 
    float smooth, 
    float3 specColor
    )
{
    // 蠖ｱ縺瑚誠縺｡縺ｦ縺・↑縺・・縺ｧ繝ｩ繧､繝医・險育ｮ励ｒ陦後≧縲・
    // 繝・ぅ繧ｺ繝九・繝吶・繧ｹ縺ｮ諡｡謨｣蜿榊ｰ・ｒ螳溯｣・☆繧・
    // 繝輔Ξ繝阪Ν蜿榊ｰ・ｒ閠・・縺励◆諡｡謨｣蜿榊ｰ・ｒ險育ｮ・
    float diffuseFromFresnel = CalcDiffuseFromFresnel(
        normal, -ligDir, toEye, smooth);

    // 豁｣隕丞喧Lambert諡｡謨｣蜿榊ｰ・ｒ豎ゅａ繧・
    float NdotL = saturate(dot(normal, -ligDir));
    float3 lambertDiffuse = ligColor * NdotL / PI;

    // 譛邨ら噪縺ｪ諡｡謨｣蜿榊ｰ・・繧定ｨ育ｮ励☆繧・
    float3 diffuse = albedoColor * diffuseFromFresnel * lambertDiffuse;

    // 繧ｯ繝・け繝医Λ繝ｳ繧ｹ繝｢繝・Ν繧貞茜逕ｨ縺励◆髀｡髱｢蜿榊ｰ・紫繧定ｨ育ｮ励☆繧・
    // 繧ｯ繝・け繝医Λ繝ｳ繧ｹ繝｢繝・Ν縺ｮ髀｡髱｢蜿榊ｰ・紫繧定ｨ育ｮ励☆繧・
    float3 spec = CookTorranceSpecular(
        -ligDir, toEye, normal, smooth)
        * ligColor;

    // 驥大ｱ槫ｺｦ縺碁ｫ倥￠繧後・縲・升髱｢蜿榊ｰ・・繧ｹ繝壹く繝･繝ｩ繧ｫ繝ｩ繝ｼ縲∽ｽ弱￠繧後・逋ｽ
    // 繧ｹ繝壹く繝･繝ｩ繧ｫ繝ｩ繝ｼ縺ｮ蠑ｷ縺輔ｒ髀｡髱｢蜿榊ｰ・紫縺ｨ縺励※謇ｱ縺・

    spec *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, metaric);

    // 貊代ｉ縺九＆繧剃ｽｿ縺｣縺ｦ縲∵僑謨｣蜿榊ｰ・・縺ｨ髀｡髱｢蜿榊ｰ・・繧貞粋謌舌☆繧・
    return max( float3( 0.0f, 0.0f, 0.0f ), diffuse * (1.0f - smooth) + spec * smooth );   
}

#endif // _PBRLIGHTING_H_