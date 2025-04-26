/////////////////////////////////////////////////////
// PBR郢晢ｽｩ郢ｧ・､郢昴・縺・ｹ晢ｽｳ郢ｧ・ｰ邵ｺ・ｧ闖ｴ・ｿ邵ｺ繝ｻﾎ帷ｹｧ・､郢晁ご逡醍ｸｺ・ｮ陞ｳ螢ｽ辟夂ｹ晁・繝｣郢晁ｼ斐＜邵ｺ・ｮ闕ｳ・ｭ髴・ｽｫ邵ｲ繝ｻ/////////////////////////////////////////////////////

#ifndef _PBRLIGHTING_LIGHTCB_BODY_H_
#define _PBRLIGHTING_LIGHTCB_BODY_H_

DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];
PointLight pointLight[MAX_POINT_LIGHT];
SpotLight spotLight[MAX_SPOT_LIGHT];
float4x4 mViewProjInv;  // 郢晁侭ﾎ礼ｹ晢ｽｼ郢晏干ﾎ溽ｹｧ・ｸ郢ｧ・ｧ郢ｧ・ｯ郢ｧ・ｷ郢晢ｽｧ郢晢ｽｳ髯ｦ謔溘・邵ｺ・ｮ鬨ｾ繝ｻ・｡謔溘・
float3 eyePos;          // 郢ｧ・ｫ郢晢ｽ｡郢晢ｽｩ邵ｺ・ｮ髫穂ｹ溘○
int numPointLight;      // 郢晄亢縺・ｹ晢ｽｳ郢晏現ﾎ帷ｹｧ・､郢晏現繝ｻ隰ｨ・ｰ邵ｲ繝ｻ   
float3 ambientLight;    // 霑ｺ・ｰ陟・・繝ｻ
int numSpotLight;       // 郢ｧ・ｹ郢晄亢繝｣郢晏現ﾎ帷ｹｧ・､郢晏現繝ｻ隰ｨ・ｰ邵ｲ繝ｻfloat4x4 mlvp[NUM_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP];
float iblLuminance;     // IBL邵ｺ・ｮ隴丞ｼｱ・狗ｸｺ霈板繝ｻint isIBL;              // IBL郢ｧ螳夲ｽ｡蠕娯鴬邵ｲ繝ｻint isEnableRaytracing; // 郢晢ｽｬ郢ｧ・､郢晏現ﾎ樒ｸｺ譴ｧ諤剰怏・ｹ邵ｲ繝ｻ
#endif // _PBRLIGHTING_LIGHTCB_BODY_H_