#include "Share.fx"

cbuffer AtlasOne : register(b9)
{
    float2 LeftTopUV;
    float2 RightBottomUV;
}

VS_OUTPUT_UV AtlasOneVS(VS_INPUT_UV input)
{
    VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

    float3 TempPos = input.vPos - (g_Pivot * g_Length);

    output.vPos = mul(float4(TempPos, 1.0f), g_WVP);

    if (input.vUV.x == 0.0f)
        output.vUV.x = LeftTopUV.x;
    else
        output.vUV.x = RightBottomUV.x;

    if (input.vUV.y == 0.0f)
        output.vUV.y = LeftTopUV.y;
    else
        output.vUV.y = RightBottomUV.y;

    return output;
}

PS_OUTPUT_SINGLE AtlasOnePS(VS_OUTPUT_UV input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

    output.vTarget0 = Diffuse.Sample(DiffuseSampler, input.vUV);

    return output;
}