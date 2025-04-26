////////////////////////////////////////////////
// IBL髢｢菫ゅ・蜃ｦ逅・
////////////////////////////////////////////////

#ifndef _IBL_H_
#define _IBL_H_

#include "Sampler.h"

/// <summary>
/// IBL繧ｫ繝ｩ繝ｼ繧偵せ繧ｫ繧､繧ｭ繝･繝ｼ繝悶・繝・・縺九ｉ繧ｵ繝ｳ繝励Μ繝ｳ繧ｰ
/// </summary>
/// <remark>
/// 縺薙・髢｢謨ｰ縺ｧ縺ｯ繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺ｮ貊代ｉ縺九＆繧剃ｽｿ縺｣縺ｦ縲・
/// 繧ｵ繝ｳ繝励Μ繝ｳ繧ｰ縺吶ｋ繧ｹ繧ｫ繧､繧ｭ繝･繝ｼ繝悶・繝・・縺ｮmipmap繝ｬ繝吶Ν繧定ｨ育ｮ励＠縺ｦ縺・∪縺吶・
/// 繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺梧ｻ代ｉ縺九〒縺ゅｌ縺ｰ縲・ｫ倩ｧ｣蜒丞ｺｦ縺ｮ繧ｹ繧ｫ繧､繧ｭ繝･繝ｼ繝悶・繝・・縲・
/// 貊代ｉ縺九＆縺御ｽ弱￠繧後・縲∽ｽ手ｧ｣蜒丞ｺｦ縺ｮ繧ｹ繧ｫ繧､繧ｭ繝･繝ｼ繝悶・繝・・縺九ｉIBL繧ｫ繝ｩ繝ｼ縺後し繝ｳ繝励Μ繝ｳ繧ｰ縺輔ｌ縺ｾ縺吶・
/// 縺薙・繧医≧縺ｫ縺吶ｋ縺薙→縺ｧ貊代ｉ縺九↑繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺ｧ縺ゅｌ縺ｰ縲∫ｶｺ鮗励↑譏繧願ｾｼ縺ｿ縺檎匱逕溘＠縲・
/// 邊励＞繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺ｧ縺ゅｌ縺ｰ縲∵僑謨｣縺励◆譏繧願ｾｼ縺ｿ縺檎匱逕溘☆繧九ｈ縺・↓縺ｪ繧翫∪縺吶・
/// </remark>
/// <param name="skyCubeMap">繧ｹ繧ｫ繧､繧ｭ繝･繝ｼ繝悶・繝・・</param>
/// <param name="reflection">蜿榊ｰ・・繧ｯ繝医Ν縲・/param>
/// <param name="smooth">繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺ｮ貊代ｉ縺九＆(0.0・・.0)</param>
/// <param name="iblIntencity">IBL縺ｮ蠑ｷ蠎ｦ縲・/param>
float4 SampleIBLColorFromSkyCube( 
    TextureCube<float4> skyCubeMap, 
    float3 reflection, 
    float smooth,
    float iblIntencity
)
{
    int level = lerp(0, 12, 1 - smooth);
    return skyCubeMap.SampleLevel(Sampler, reflection, level) * iblIntencity;
}
/// <summary>
/// IBL繧ｫ繝ｩ繝ｼ繧偵せ繧ｫ繧､繧ｭ繝･繝ｼ繝悶・繝・・縺九ｉ繧ｵ繝ｳ繝励Μ繝ｳ繧ｰ
/// </summary>
/// <remark>
/// 繧｢繝ｫ繧ｴ繝ｪ繧ｺ繝縺ｯ蜷後§縺ｪ縺ｮ縺ｧ逵∫払縲・
/// </remark>
/// <param name="skyCubeMap">繧ｹ繧ｫ繧､繧ｭ繝･繝ｼ繝悶・繝・・</param>
/// <param name="samper">繧ｵ繝ｳ繝励Λ</param>
/// <param name="toEye">隕也せ縺ｸ縺ｮ豁｣隕丞喧縺輔ｌ縺溘・繧ｯ繝医Ν</param>
/// <param name="normal">繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺ｮ豕慕ｷ・/param>
/// <param name="smooth">繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺ｮ貊代ｉ縺九＆(0.0・・.0)</param>
/// <param name="iblIntencity">IBL縺ｮ蠑ｷ蠎ｦ縲・/param>
float4 SampleIBLColorFromSkyCube( 
    TextureCube<float4> skyCubeMap,
    float3 toEye, 
    float3 normal, 
    float smooth,
    float iblIntencity
)
{
    // 蜿榊ｰ・・繧ｯ繝医Ν繧定ｨ育ｮ励☆繧九・
    float3 v = reflect(toEye * -1.0f, normal);
    return SampleIBLColorFromSkyCube(skyCubeMap, v, smooth, iblIntencity);
}

#endif // _IBL_H_
