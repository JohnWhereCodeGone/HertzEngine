#pragma once
#include <iostream>
#include <vector>
//square



enum Textureformat
{
	jpg,
	png,
	unknown
};
enum TextureType
{
	Diffuse,
	Specular,
	Normal,
	Height
};


enum MipMapSettings
{
	NEAREST_NEAREST,
	LINEAR_NEAREST,
	NEAREST_LINEAR,
	LINEAR_LINEAR //Trilinear filtering.
};

struct TextureSettings
{
	MipMapSettings MipMap;
	bool flip_on_load = true;

};


class HertzTexture
{
public:

	std::string type;
	HertzTexture(const char* tPath = nullptr, bool isPng = false, TextureType type = TextureType::Diffuse);
	void Use(); //not working
	void Use(unsigned int data); //not working
	TextureType texturetype;
	
	unsigned int& GetTexture();
	static TextureSettings* textureSettings;

private:
	void SetupMipMap(const MipMapSettings& setting);
	void UpdateMipMap(HertzTexture* text);
	unsigned int texture;
	

	
};

