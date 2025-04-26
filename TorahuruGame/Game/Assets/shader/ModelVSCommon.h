//繝｢繝・Ν縺ｮ鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ髢｢菫ゅ・蜈ｱ騾壹・繝・ム繝ｼ



///////////////////////////////////////
// 螳壽焚繝舌ャ繝輔ぃ縲・
///////////////////////////////////////
// 繝｢繝・Ν逕ｨ縺ｮ螳壽焚繝舌ャ繝輔ぃ繝ｼ
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

////////////////////////////////////////////////
// 讒矩菴・
////////////////////////////////////////////////

// 鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｸ縺ｮ蜈･蜉・
struct SVSIn
{
    float4 pos : POSITION;          //鬆らせ蠎ｧ讓吶・
    float3 normal : NORMAL;         //豕慕ｷ壹・
    float2 uv : TEXCOORD0;          //UV蠎ｧ讓吶・
    float3 tangent  : TANGENT;      //謗･繝吶け繝医Ν縲・
    float3 biNormal : BINORMAL;     //蠕薙・繧ｯ繝医Ν縲・
    int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};

////////////////////////////////////////////////
// 繧ｰ繝ｭ繝ｼ繝舌Ν螟画焚縲・
////////////////////////////////////////////////
StructuredBuffer<float4x4> g_boneMatrix         : register(t3);	    //繝懊・繝ｳ陦悟・縲・
StructuredBuffer<float4x4> g_worldMatrixArray   : register(t10);	//繝ｯ繝ｼ繝ｫ繝芽｡悟・縺ｮ驟榊・縲ゅう繝ｳ繧ｹ繧ｿ繝ｳ繧ｷ繝ｳ繧ｰ謠冗判縺ｮ髫帙↓譛牙柑縲・

///////////////////////////////////////
// 髢｢謨ｰ螳｣險
///////////////////////////////////////
SPSIn VSMainCore(SVSIn vsIn, float4x4 mWorldLocal, uniform bool isUsePreComputedVertexBuffer);

////////////////////////////////////////////////
// 髢｢謨ｰ螳夂ｾｩ縲・
////////////////////////////////////////////////
/// <summary>
//繧ｹ繧ｭ繝ｳ陦悟・繧定ｨ育ｮ励☆繧九・
/// </summary>
float4x4 CalcSkinMatrix(SVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}
/// <summary>
/// 繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢薙・鬆らせ蠎ｧ讓吶ｒ險育ｮ励☆繧九・
/// </summary>
/// <param name="vertexPos">鬆らせ蠎ｧ讓・/param>
/// <param name="mWorld">繝ｯ繝ｼ繝ｫ繝芽｡悟・</param>
/// <param name="isUsePreComputedVertexBuffer">莠句燕險育ｮ玲ｸ医∩縺ｮ鬆らせ繝舌ャ繝輔ぃ繧貞茜逕ｨ縺励※縺・ｋ・・/param>
float4 CalcVertexPositionInWorldSpace(float4 vertexPos, float4x4 mWorld, uniform bool isUsePreComputedVertexBuffer)
{
    float4 pos;
    if(isUsePreComputedVertexBuffer){
        pos = vertexPos;
    }else{
        pos = mul(mWorld, vertexPos);  // 繝｢繝・Ν縺ｮ鬆らせ繧偵Ρ繝ｼ繝ｫ繝牙ｺｧ讓咏ｳｻ縺ｫ螟画鋤
    }

    return pos;
}
/// <summary>
/// 繧ｹ繧ｭ繝ｳ縺ｪ縺励Γ繝・す繝･逕ｨ縺ｮ鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ縲・
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, mWorld, false);
}
/// <summary>
/// 繧ｹ繧ｭ繝ｳ縺ｪ縺励Γ繝・す繝･逕ｨ縺ｮ鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ(繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｷ繝ｳ繧ｰ謠冗判逕ｨ)縲・
/// </summary>
SPSIn VSMainInstancing(SVSIn vsIn, uint instanceID : SV_InstanceID)
{
	return VSMainCore(vsIn, g_worldMatrixArray[instanceID], false);
}
/// <summary>
/// 繧ｹ繧ｭ繝ｳ縺ゅｊ繝｡繝・す繝･縺ｮ鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ縲・
/// </summary>
SPSIn VSMainSkin( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, CalcSkinMatrix(vsIn), false);
}
/// <summary>
/// 繧ｹ繧ｭ繝ｳ縺ゅｊ繝｡繝・す繝･縺ｮ鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ(繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｷ繝ｳ繧ｰ謠冗判逕ｨ縲・
/// </summary>
SPSIn VSMainSkinInstancing( SVSIn vsIn, uint instanceID : SV_InstanceID )
{
    float4x4 mWorldLocal = CalcSkinMatrix(vsIn);
    mWorldLocal = mul( g_worldMatrixArray[instanceID], mWorldLocal );
    return VSMainCore(vsIn, mWorldLocal, false);
}
/// <summary>
/// 莠句燕險育ｮ玲ｸ医∩縺ｮ鬆らせ繝舌ャ繝輔ぃ繧剃ｽｿ縺・らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ縲・
/// 繧ｹ繧ｭ繝ｳ繝｡繝・す繝･逕ｨ
/// </summary>
SPSIn VSMainSkinUsePreComputedVertexBuffer( SVSIn vsIn )
{
    return VSMainCore(vsIn, (float4x4)0, true);
}
/// <summary>
/// 莠句燕險育ｮ玲ｸ医∩縺ｮ鬆らせ繝舌ャ繝輔ぃ繧剃ｽｿ縺・らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ縲・
/// 繧ｹ繧ｭ繝ｳ縺ｪ縺励Γ繝・す繝･逕ｨ
/// </summary>
SPSIn VSMainUsePreComputedVertexBuffer( SVSIn vsIn )
{
    return VSMainCore(vsIn, (float4x4)0, true);
}
/// <summary>
/// 繝ｯ繝ｼ繝ｫ繝峨せ繝壹・繧ｹ縺ｮ豕慕ｷ壹∵磁繝吶け繝医Ν縲∝ｾ薙・繧ｯ繝医Ν繧定ｨ育ｮ励☆繧九・
/// </summary>
/// <param name="oNormal">豕慕ｷ壹・蜃ｺ蜉帛・</param>
/// <param name="oTangent">謗･繝吶け繝医Ν縺ｮ蜃ｺ蜉帛・</param>
/// <param name="oBiNormal">蠕薙・繧ｯ繝医Ν縺ｮ蜃ｺ蜉帛・</param>
/// <param name="mWorld">繝ｯ繝ｼ繝ｫ繝芽｡悟・</param>
/// <param name="iNormal">豕慕ｷ・/param>
/// <param name="iTanget">謗･繝吶け繝医Ν</param>
/// <param name="iBiNormal">蠕薙・繧ｯ繝医Ν</param>
/// <param name="isUsePreComputedVertexBuffer">莠句燕險育ｮ玲ｸ医∩鬆らせ繝舌ャ繝輔ぃ繧貞茜逕ｨ縺吶ｋ・・param>
void CalcVertexNormalTangentBiNormalInWorldSpace( 
    out float3 oNormal, 
    out float3 oTangent, 
    out float3 oBiNormal,
    float4x4 mWorld,
    float3 iNormal,
    float3 iTangent,
    float3 iBiNormal,
    uniform bool isUsePreComputedVertexBuffer
)
{
    if( isUsePreComputedVertexBuffer){
        // 莠句燕險育ｮ玲ｸ医∩鬆らせ繝舌ャ繝輔ぃ繧貞茜逕ｨ縺吶ｋ縲・
        oNormal = iNormal;
        oTangent = iTangent;
        oBiNormal = iBiNormal;
    }else{
        // 
        float3x3 m3x3 = (float3x3)mWorld;
	    oNormal = normalize(mul(m3x3, iNormal));
	    oTangent = normalize(mul(m3x3, iTangent));
	    oBiNormal = normalize(mul(m3x3, iBiNormal));
    }
}