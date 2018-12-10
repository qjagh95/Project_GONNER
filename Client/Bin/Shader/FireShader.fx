//#include "Share.fx"

//cbuffer Fire : register(b9)
//{
//    float4 g_Light;
//    float g_UVSpeed;
//    float3 g_Empty46456;
//};

//Texture2D NoiseMap : register(t1);

//VS_OUTPUT_UV FireVS(VS_INPUT_UV input)
//{
//    VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

//    float3 vPos = input.vPos - g_Pivot * g_Length;

//    output.vPos = mul(float4(vPos, 1.0f), g_WVP);
//    output.vUV = input.vUV;

//    return output;
//}

//PS_OUTPUT_SINGLE FirePS(VS_OUTPUT_UV input)
//{
//    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

//    output.vTarget0 = Diffuse.Sample(DiffuseSampler, input.vUV) * g_Light;

//    return output;
//}