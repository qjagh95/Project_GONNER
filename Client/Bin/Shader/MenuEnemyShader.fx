#include "Share.fx"
//fx파일은 버텍스와 픽셀쉐이더 두개 동시에 처리가 가능하다.

cbuffer Animation2D : register(b10)
{
    float2 g_LeftTopUV;
    float2 g_RightBottomUV;
    int g_isRight;
    float3 g_Empty1234;
}

cbuffer MenuEnemy : register(b9)
{
    float4 Color;
};

VS_OUTPUT_UV MenuEnemyVS(VS_INPUT_UV input)
{
    VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

    float3 TempPos = input.vPos - (g_Pivot * g_Length);
    output.vPos = mul(float4(TempPos, 1.0f), g_WVP);

    if (g_Animation2DEnable == 1)
    {
        if (g_isRight == 0)
            input.vUV.x = 1.0f - input.vUV.x;

        if (input.vUV.x == 0.0f)
            output.vUV.x = g_LeftTopUV.x;
        else
            output.vUV.x = g_RightBottomUV.x;

        if (input.vUV.y == 0.0f)
            output.vUV.y = g_LeftTopUV.y;
        else
            output.vUV.y = g_RightBottomUV.y;
      
    }
    else
        output.vUV = input.vUV;

    return output;
}
  
PS_OUTPUT_SINGLE MenuEnemyPS(VS_OUTPUT_UV input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

    output.vTarget0 = Diffuse.Sample(DiffuseSampler, input.vUV) * g_MaterialDiffuse * Color;

    return output;
}

