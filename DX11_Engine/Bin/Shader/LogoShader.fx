#include "Share.fx"

Texture2D NoiseMap : register(t1);

cbuffer Logo : register(b9)
{
    float4 g_Light;
    float g_UVSpeed;
    float3 g_Empty46456;
};

VS_OUTPUT_UV LogoVS(VS_INPUT_UV input)
{
    VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

    float3 vPos = input.vPos - g_Pivot * g_Length;

    output.vPos = mul(float4(vPos, 1.0f), g_WVP);
    output.vUV = input.vUV;

    return output;
}

PS_OUTPUT_SINGLE LogoPS(VS_OUTPUT_UV input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

    float2 UV = input.vUV;
    float2 MultiyUV = UV * 2.0f;
    float Lenth = MultiyUV.x + MultiyUV.y;
    float2 ResultUV = cos(Lenth * 10.0 - g_UVSpeed * 5.0f) * 0.01f;

    float4 diffuse = Diffuse.Sample(DiffuseSampler, ResultUV);

    output.vTarget0 = diffuse;
    
    return output;
}

/*

*/