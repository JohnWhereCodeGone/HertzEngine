#include "HertzTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Dependencies/stb_image/stb_image.h"
#include "glad/glad.h"
#include "../Dependencies/glm/glm.hpp"
#include <iostream>

TextureSettings* HertzTexture::textureSettings = nullptr;


HertzTexture::HertzTexture(const char* tPath, bool isPng, TextureType type)
{
	if (!textureSettings)
	{
		textureSettings = new TextureSettings;
		textureSettings->MipMap = MipMapSettings::LINEAR_LINEAR;
	}

	stbi_set_flip_vertically_on_load(true);
	unsigned int tTexture;
	glGenTextures(1, &tTexture);
	glBindTexture(GL_TEXTURE_2D, tTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	SetupMipMap(textureSettings->MipMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	

	int width, height, nrChannels;


	unsigned char* data = stbi_load(tPath, &width, &height, &nrChannels, 0);

	if (!data)
	{
		std::cerr << "TEXTURE FAILED TO LOAD: " << tPath << std::endl;
		std::cerr << "Reason: " << stbi_failure_reason() << std::endl;
	}

	if (data && !isPng)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else if (data && isPng)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "TEXTURE ERROR: DATA WAS NULL" << std::endl;
	}
	texture = tTexture;
	this->texturetype = type;
	stbi_image_free(data);




}





void HertzTexture::Use()
{
	if (texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
}

void HertzTexture::Use(unsigned int specular)
{
	if (texture && specular)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular);
	}
}

unsigned int& HertzTexture::GetTexture()
{
	return texture;
}


//ToDO: Update me to work in runtime.
void HertzTexture::SetupMipMap(const MipMapSettings& setting)
{
	switch (setting)
	{
	case MipMapSettings::NEAREST_NEAREST:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		break;
	case MipMapSettings::LINEAR_NEAREST:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	case MipMapSettings::NEAREST_LINEAR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		break;
	case MipMapSettings::LINEAR_LINEAR: //Trifiltering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	
	}
}

void HertzTexture::UpdateMipMap(HertzTexture* text)
{
	unsigned int tData = text->GetTexture();

}

