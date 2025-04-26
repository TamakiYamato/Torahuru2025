///////////////////////////////////////
// PBR繝吶・繧ｹ縺ｮ繝・ぅ繝輔ぃ繝ｼ繝峨Λ繧､繝・ぅ繝ｳ繧ｰ縺ｮCAV繝ｬ繧ｸ繧ｹ繧ｿ險ｭ螳・
///////////////////////////////////////


#ifndef _DEFERREDLIGHTING_CAV_REGISTER_H_
#define _DEFERREDLIGHTING_CAV_REGISTER_H_

//蜈ｱ騾壼ｮ壽焚繝舌ャ繝輔ぃ
cbuffer cb : register(b0)
{
    float4x4 mvp; 
    float4 mulColor;
    float4 screenParam;
};

#endif // _DEFERREDLIGHTING_CAV_REGISTER_H_