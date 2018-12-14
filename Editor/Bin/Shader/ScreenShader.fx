#include "Share.fx"

cbuffer Wave : register(b9)
{
    float g_LiveTime;
    float3 g_Empty1233456;
}

VS_OUTPUT_UV ScreenVS(VS_INPUT_UV input)
{
    VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

    float3 TempPos = input.vPos - (g_Pivot * g_Length);
    output.vPos = mul(float4(TempPos, 1.0f), g_WVP);

    output.vUV = input.vUV;

    return output;
}
  
PS_OUTPUT_SINGLE ScreenPS(VS_OUTPUT_UV input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

    float2 UV = input.vUV;

    if (g_LiveTime > 0.0f)
    {
        float2 Fixed = float2(UV.x, UV.y - 1.0f);
   
        Fixed.x -= PlayerUV.x;
        Fixed.y += PlayerUV.y;

        float Lenth = sqrt(pow(Fixed.x, 2) + pow(Fixed.y, 2));
        float2 ResultUV = UV + (Fixed / Lenth) * cos(Lenth * 10.0f + g_PlusedDeltaTime * 10.0f) * 0.005f;

        if (Lenth < 0.3f)
        {
            float4 diffuse = Diffuse.Sample(DiffuseSampler, ResultUV);
            output.vTarget0 = diffuse;
    
            return output;
        }
        else
        {
            float4 diffuse = Diffuse.Sample(DiffuseSampler, input.vUV);
            output.vTarget0 = diffuse;
    
            return output;
        }
    }
    else
    {
        float4 diffuse = Diffuse.Sample(DiffuseSampler, input.vUV);
        output.vTarget0 = diffuse;
    
        return output;
    }
}

