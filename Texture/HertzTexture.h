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

struct TextureSettings //old, delete me
{
	MipMapSettings MipMap;
	bool flip_on_load = true;

};


class HertzTexture
{
public:

	std::string m_type;
	std::string m_path;
	

	HertzTexture(const char* tPath = nullptr, bool isPng = false, const TextureType &type = TextureType::Diffuse);
	void Use(); //not working
	void Use(unsigned int data); //not working
	TextureType m_texturetype;
	
	unsigned int& GetTexture();
	static TextureSettings* textureSettings; //old
	void SetMipMap(const MipMapSettings& setting);
	std::string& GetName();


private:
	static void UpdateMipMap(HertzTexture* text, const MipMapSettings& setting);
	unsigned int texture;
	std::string m_name;
	

	
};

