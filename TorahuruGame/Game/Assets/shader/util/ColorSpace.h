/*!
 *@brief    濶ｲ遨ｺ髢馴未菫ゅ・繝倥ャ繝繝ｼ繝輔ぃ繧､繝ｫ縲・
 */

#ifndef _COLOR_SPACE_H_
#define _COLOR_SPACE_H_
////////////////////////////////////////////////////////
// RGB->HSV, HSV->RGB縺ｸ縺ｮ濶ｲ遨ｺ髢灘､画鋤髢｢騾｣縺ｮ髢｢謨ｰ髮・・
////////////////////////////////////////////////////////

/*!
 * @brief RGB邉ｻ縺九ｉHSV邉ｻ縺ｫ螟画鋤縺吶ｋ縲・
 */
float3 Rgb2Hsv(float3 c)
{
    float4 K = float4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    float4 p = lerp(float4(c.bg, K.wz), float4(c.gb, K.xy), step(c.b, c.g));
    float4 q = lerp(float4(p.xyw, c.r), float4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return float3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}
/*!
 * @brief RGB邉ｻ縺九ｉHSV縺ｮV(霈晏ｺｦ)繧呈ｱゅａ繧九・
 */
float Rgb2V( float3 rgb)
{
    return max(rgb.r, max(rgb.g, rgb.b));
}
/*!
 * @brief HSV邉ｻ縺九ｉRGB邉ｻ縺ｫ螟画鋤縺吶ｋ縲・
 */
float3 Hsv2Rgb(float3 c)
{
    float4 K = float4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    float3 p = abs(frac(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * lerp(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

#endif