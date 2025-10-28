#pragma once
#include <vector>
#include "HertzTexture.h"

class HertzTexture;

class TextureManager
{
	
public:

	TextureManager();
	std::shared_ptr<HertzTexture> GetTexture();

	static void UpdateMipMap(const MipMapSettings& setting);
	void RemoveTexture(std::shared_ptr<HertzTexture> textureToRemove);
	static std::shared_ptr<HertzTexture> LoadTexture(const char* tPath, const TextureType& type = Diffuse, bool isPng = false);

	static std::vector<std::shared_ptr<HertzTexture>> MakeDefaultTextures();

private:
	
	bool m_HasTextureList;
	static std::vector<std::shared_ptr<HertzTexture>> m_LoadedTexturesList;
	

};

