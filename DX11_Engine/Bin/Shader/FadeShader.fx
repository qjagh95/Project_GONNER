#include "Share.fx"

cbuffer Fade : register(b9)
{
    float4 g_Light;
    bool g_isStart;
    float g_Speed;
    bool g_isFadeIn;
    float Empty;
};

VS_OUTPUT_UV FadeVS(VS_INPUT_UV input)
{
    VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

    float3 vPos = input.vPos - g_Pivot * g_Length;

    output.vPos = mul(float4(vPos, 1.0f), g_WVP);
    output.vUV = input.vUV;

    return output;
}

PS_OUTPUT_SINGLE FadePS(VS_OUTPUT_UV input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

    output.vTarget0 = g_Light;

    return output;
}