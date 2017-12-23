#pragma once

#include "Engine.h"

class Shader
{
public:
	Shader(std::string path);
	Shader(std::string path, std::string techName);
	~Shader();

	ID3DXEffect* GetFx() { return fx; }

	// -- TODO -- Implementer un Resource ici en templatant le Ressource.h
	template <class T>
	void SetParameter(std::string paramName, T value)
	{
		if (parameters.find(paramName) == parameters.end())
		{
			D3DXHANDLE hParam = fx->GetParameterByName(0, paramName.c_str());

			auto inserted = parameters.insert(
				std::make_pair(paramName, std::move(hParam)));
			assert(inserted.second);
		}
		fx->SetValue(parameters[paramName], &value, sizeof(T));
	}

private:
	Shader() {}

	ID3DXEffect* fx;
	ID3DXBuffer* errors;

	// TODO - Integration d'un transform
	std::map<std::string, D3DXHANDLE> parameters;

	D3DXHANDLE hTech;
};

