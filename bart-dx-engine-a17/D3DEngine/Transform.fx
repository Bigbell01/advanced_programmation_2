uniform extern float4x4 gWVP;

struct OutputVS
{
	// Semantique
	float4 posH: POSITION0;
	float4 col: COLOR0;
};

// Fonction Vertex Shader
OutputVS TransformVS(float3 posL: POSITION0, float4 col: COLOR0)
{
	OutputVS outVS = (OutputVS)0;
	outVS.posH = mul(float4(posL, 1.0), gWVP);
	outVS.col = col;
	return outVS;
}

float4 TransformPS(float4 col: COLOR0): COLOR0
{
	return (float4)0;
}

technique TransformTech
{
	pass P0
	{
		vertexShader = compile vs_2_0 TransformVS();
		pixelShader = compile ps_2_0 TransformPS();

		CullMode = none;
	}
}