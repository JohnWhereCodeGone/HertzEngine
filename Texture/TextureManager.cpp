#include "TextureManager.h"

std::vector<std::shared_ptr<HertzTexture>> TextureManager::m_LoadedTexturesList;

TextureManager::TextureManager()
{



}

std::shared_ptr<HertzTexture> TextureManager::GetTexture()
{
    if (!m_HasTextureList)
    {
        m_LoadedTexturesList = {};
        m_HasTextureList = true;
    }
    
    return std::make_shared<HertzTexture>();
}



void TextureManager::UpdateMipMap(const MipMapSettings& setting)
{
    if (m_LoadedTexturesList.empty())
        return;
    
    for (std::shared_ptr<HertzTexture>& tex : m_LoadedTexturesList)
    {
        tex->Use();
        tex->SetMipMap(setting);
        std::cout << "TextureManager::UpdateMipMap - Updated mip map settings!" << std::endl;
    }
}

void TextureManager::RemoveTexture(std::shared_ptr<HertzTexture> textureToRemove)
{
    if (!textureToRemove)
    {
        std::cout << "TextureManager::RemoveTexture - texture to remove is already nullptr." << std::endl;
        return;
    }
    
    auto it = std::find(m_LoadedTexturesList.begin(), m_LoadedTexturesList.end(), textureToRemove);

    

    if (it != m_LoadedTexturesList.end())
    {
        m_LoadedTexturesList.erase(it);
    }

}

std::shared_ptr<HertzTexture> TextureManager::LoadTexture(const char* tPath, const TextureType& type, bool isPng)
{

    for (std::shared_ptr<HertzTexture> tex : m_LoadedTexturesList)
    {
        if (tPath == tex->m_path)
        {
            std::cout << "Texture loaded using path " << tPath << "already exists." << std::endl;
            return tex;
        }


    }
    std::shared_ptr<HertzTexture> texload = std::make_shared<HertzTexture>(tPath, isPng, type);
    if (!texload)
    {
        std::cout << "TextureManager::LoadTexture returned nullptr." << std::endl;
        return nullptr;
    }

    texload->m_path = tPath;
    m_LoadedTexturesList.push_back(texload);
    return texload;



}

std::vector<std::shared_ptr<HertzTexture>> TextureManager::MakeDefaultTextures()
{
    std::vector<std::shared_ptr<HertzTexture>> textures;

    std::shared_ptr<HertzTexture> diffuse = TextureManager::LoadTexture("./texture./container2.png", TextureType::Diffuse, true);
    std::shared_ptr<HertzTexture> specular = TextureManager::LoadTexture("./texture./container2_specular.png", TextureType::Specular, true);


    diffuse->m_type = "texture_diffuse";
    specular->m_type = "texture_specular";

    diffuse->m_texturetype = TextureType::Diffuse;
    specular->m_texturetype = TextureType::Specular;

    textures.push_back(diffuse);
    textures.push_back(specular);

    return textures;
}
