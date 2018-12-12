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
    float Lenth = input.vUV.x + input.vUV.y;
    float2 ResultUV = UV + cos(Lenth * 10.0f + g_UVSpeed * 2.0f) * 0.01f;
    //UVSpeed는 계속 늘려주기 위함. (시간 누적값이들어옴)

    float4 diffuse = Diffuse.Sample(DiffuseSampler, ResultUV); 
    output.vTarget0 = diffuse;
  
    return output;
}