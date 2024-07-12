//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

//
//	Textures
//
Texture2D		g_texture0 : register(t0);
Texture2D		g_texture1 : register(t1);
SamplerState	g_sampler0 : register(s0);
SamplerState	g_sampler1 : register(s1);

namespace s3d
{
	//
	//	VS Output / PS Input
	//
	struct PSInput
	{
		float4 position	: SV_POSITION;
		float4 color	: COLOR0;
		float2 uv		: TEXCOORD0;
	};
}

//
//	Constant Buffer
//
cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_sdfOutlineColor;
	float4 g_sdfShadowColor;
	float4 g_internal;
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
//	float4 texColor0 = g_texture0.Sample(g_sampler0, input.uv);
//	float4 texColor1 = g_texture1.Sample(g_sampler1, input.uv);
    float4 texColor0 = g_texture0.Sample(g_sampler0, input.uv.xy);
    float4 texColor1 = g_texture1.Sample(g_sampler1, input.uv.xy);
	
//	texColor0.rgb = (texColor0.rgb * 0.5 + texColor1.rgb * 0.5);
	texColor0.rgb = 1 - (1 - texColor0.rgb) * (1 - texColor1.rgb);
//    texColor0.rgba = texColor0.rgba * texColor1.rgba;
//	texColor1.rgb = 1 - (1 - texColor0.rgb) * (1 - texColor1.rgb);
//    texColor1.rgb = 1 - (1 - texColor0.rgb) * (1 - texColor1.rgb);

//    texColor1.a = texColor0.a + texColor1.a;
 //   texColor1.a = texColor0.a;
	
 //   float a = texColor0.a || texColor1.a;
//    float a = texColor1.a;
	
//	float4 ret = 1 - (1 - texColor0.rgb) * (1 - texColor1.rgb);
//    return float4(1.0, 1.0, 1.0, a);
//	return texColor0;
	
//	return (texColor1 * input.color) + g_colorAdd;
	return (texColor0 * input.color) + g_colorAdd;
}
