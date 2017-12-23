#pragma once

#include <map>
#include <cassert>

#include "D3DApp.h"
#include "D3DUtils.h"

struct ResourceInfo
{
	ResourceInfo()
	: texture(nullptr){ }

	D3DXIMAGE_INFO info;
	IDirect3DTexture9* texture;
};

class Resources
{
public:
	Resources();
	~Resources();

	ResourceInfo* GetTexture(std::wstring& fileName)
	{
		std::wcout << "GetTexture: " << fileName << std::endl;

		ResourceInfo* loadedResource = new ResourceInfo();

		if (resources.find(fileName) == resources.end())
		{
			std::wcout << "Loading: " << fileName << std::endl;

			//Load image at specified path
			HR(D3DXCreateTextureFromFileExW(gD3DDevice, (LPCWSTR)fileName.c_str(), 0, 0, 1, 0,
				D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE,
				D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), &loadedResource->info, NULL,
				&loadedResource->texture));

			auto inserted = resources.insert(std::make_pair(fileName, std::move(loadedResource)));

			assert(inserted.second);

			resources[fileName] = loadedResource;
		}
		else
		{
			std::wcout << "Already loaded: " << fileName << std::endl;
		}

		std::wcout << "Returning: " << fileName << std::endl << std::endl;
		return resources[fileName];
	}

private:
	void LoadTexture(const char* path, ResourceInfo& loadedResource) const;

	std::map<std::wstring, ResourceInfo*> resources;
};