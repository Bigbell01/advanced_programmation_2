#include "Shader.h"

Shader::Shader(std::string path)
{
	HR(D3DXCreateEffectFromFile(gD3DDevice, (LPCWSTR)path.c_str(), 0, 0, D3DXSHADER_DEBUG, 0, &fx, &errors));
	
	hTech = fx->GetTechniqueByName("VertexColorTech");
	HR(fx->SetTechnique(hTech));
}

Shader::Shader(std::string path, std::string techName)
{
	HR(D3DXCreateEffectFromFile(gD3DDevice, (LPCWSTR)path.c_str(), 0, 0, D3DXSHADER_DEBUG, 0, &fx, &errors));

	hTech = fx->GetTechniqueByName(techName.c_str());
	HR(fx->SetTechnique(hTech));
}

Shader::~Shader()
{
}
