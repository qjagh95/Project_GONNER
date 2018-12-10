#include "Share.fx"

cbuffer AlphaBat : register(b9)
{
    float4 g_Light;
    float g_RangeX;
    float g_RangeY;
    float2 Empty;
};


VS_OUTPUT_UV AlphaBatVS(VS_INPUT_UV input)
{
    VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

    float3 vPos = input.vPos - g_Pivot * g_Length;

    output.vPos = mul(float4(vPos, 1.0f), g_WVP);
    output.vUV = input.vUV;

    return output;
}

PS_OUTPUT_SINGLE AlphaBatPS(VS_OUTPUT_UV input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

    output.vTarget0 = Diffuse.Sample(DiffuseSampler, input.vUV) * g_Light;


    if (input.vUV.x >= g_RangeX)
    {
        if (input.vUV.y >= g_RangeY)
            output.vTarget0.a = 0.0f;
    }

    return output;
}