#include "Share.fx"

cbuffer TileImage : register(b10)
{
    float4 g_Light;
    float4 g_ColorPercent;
}

VS_OUTPUT_UV TileImageVS(VS_INPUT_UV input)
{
    VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

    float3 vPos = input.vPos - g_Pivot * g_Length;

    output.vPos = mul(float4(vPos, 1.0f), g_WVP);
    output.vUV = input.vUV;

    return output;
}

PS_OUTPUT_SINGLE TileImagePS(VS_OUTPUT_UV input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

    output.vTarget0 = Diffuse.Sample(DiffuseSampler, input.vUV) * g_MaterialDiffuse * g_Light * g_ColorPercent;
    
    return output;
}