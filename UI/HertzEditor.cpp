#include "HertzEditor.h"
//#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"
#include "../Entity/Entity.h"
#include "HertzTexture.h"

#include "TextureManager.h"
#include "../Mesh/Meshmanager.h"
#include "../Shaders/ShaderManager.h"


#include "../Camera.h"
#include "../Entity/EntityManager.h"
#include "../Transform.h"
#include "../Shaders/HertzShader.h"
#include "../imgui_stdlib.h"
#include "../Mesh.h"
#include "../Lights/Lightmanager.h"

bool show_demo_window = true;
bool show_another_window = false;
glm::vec3 clear_color(1.0f, 0.0f, 1.0f);
int counter = 0.0f;
float f;

glm::vec3 postest;


static std::shared_ptr<Entity> entityToRename;


void HertzEditor::EditorUI(GLFWwindow* window)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("MipMap"))
        {
            if (ImGui::MenuItem("Point Sampling (low)"))
            {
                TextureManager::UpdateMipMap(MipMapSettings::NEAREST_NEAREST);
            }
            if (ImGui::MenuItem("Bilinear Filterning (balanced)"))
            {
                
                TextureManager::UpdateMipMap(MipMapSettings::LINEAR_NEAREST);

            }
            if (ImGui::MenuItem("Nearest Linear (abarrent)"))
            {
                TextureManager::UpdateMipMap(MipMapSettings::NEAREST_LINEAR);
                
            }
            if (ImGui::MenuItem("Trilinear (highest)"))
            {
                TextureManager::UpdateMipMap(MipMapSettings::LINEAR_LINEAR);
                
            }
            if (ImGui::MenuItem("Untitled"))
            {

            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    

    ImGui::SetNextWindowPos(ImVec2(0, 20));
    ImGui::SetNextWindowSize(ImVec2(350.f, ImGui::GetIO().DisplaySize.y));
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);                          
    ImGui::Separator();

    

         
    //When you continue tomorrow -> Continue rename -> cam rotation -> select mesh / shader for entity -> v nice

    


    if (ImGui::TreeNodeEx("Camera Settings", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Checkbox("Spotlight Enabled", &m_camRef->m_lightIsOn);
        ImGui::Text("Transform");
        ImGui::InputFloat("Transform X", &m_camRef->vPos.x, 1.f);
        ImGui::InputFloat("Transform Y", &m_camRef->vPos.y, 1.f);
        ImGui::InputFloat("Transform Z", &m_camRef->vPos.z, 1.f);
        ImGui::Separator();

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::InputFloat("Speed", &m_camRef->fCamSpeed);
        ImGui::InputFloat("Zoom", &m_camRef->fZoom);
        ImGui::InputFloat("Mouse Sense", &m_camRef->fMouseSensitivity);

        /*
        ImGui::Separator();

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        */

        //add rotation

        ImGui::TreePop();
    }
    if (!m_MeshManager)
    {
        std::cout << "NO MM!!" << std::endl;
    }
    if (m_MeshManager->GetCache().empty())
    {
        std::cout << "NO MESHES WTF" << std::endl;
    }
    /// LIGHTS  ///
    if (ImGui::TreeNodeEx("Lights"))
    {
        using DiffusePtr    = std::shared_ptr<DiffuseLight>;
        using PointPtr      = std::shared_ptr<PointLight>;
        using SpotPtr       = std::shared_ptr<Spotlight>;


        std::vector<std::shared_ptr<Light>> lightlist   = m_lightManager->GetLights();

        DiffusePtr   lightDiff   = nullptr;
        PointPtr     lightPoint  = nullptr;
        SpotPtr      lightSpot   = nullptr;

        std::string  name        = " " ;


        if (ImGui::Button("Create Light"))
        {
            ImGui::OpenPopup("Select Light");
        }

        if (ImGui::BeginPopup("Select Light"))
        {
            ImGui::Text("Light Type");
            std::vector<std::shared_ptr<HertzTexture>> textures = m_TextureManager->GetTextureList();

            if (ImGui::BeginListBox("Light Types..."))
            {

                

                if (ImGui::Selectable("Spot Light"))
                {
                    m_lightManager->CreateLight(LightType::Spotlighter);
                }
                if (ImGui::Selectable("Point Light"))
                {
                    m_lightManager->CreateLight(LightType::Pointlighter);
                }
                if (ImGui::Selectable("Diffuse Light"))
                {
                    m_lightManager->CreateLight(LightType::DiffuseLighter);
                }
                if (ImGui::Button("Close"))
                {
                    ImGui::CloseCurrentPopup();
                }


                ImGui::EndListBox();
            }

            ImGui::EndPopup();
        }


        for (std::shared_ptr<Light> light : lightlist)
        {

            switch (light->GetLightType())
            {
            case(DiffuseLighter):
                lightDiff = std::static_pointer_cast<DiffuseLight>(light);
                name = "Diffuse Light ";
                name.append(lightDiff->m_ID);
                break;

            case(Pointlighter):
                lightPoint = std::static_pointer_cast<PointLight>(light);
                name = "Point Light ";
                name.append(lightPoint->m_ID);
                break;

            case(Spotlighter):
                lightSpot = std::static_pointer_cast<Spotlight>(light);
                name = "Spot Light ";
                name.append(lightSpot->m_ID);
                break;
            }
            ImGui::PushID((void*)light.get());
            

            if (ImGui::TreeNodeEx(name.c_str()))
            {
                if (ImGui::Button("Delete Light"))
                {
                    m_lightManager->DeleteLight(light);
                }

                if (lightDiff && light->m_ID == lightDiff->m_ID)
                {

                    if (ImGui::Button("Diffuse Button"))
                    {

                    }

                    ImGui::DragFloat3("Diffuse XYZ",   glm::value_ptr(lightDiff->GetProperties().Diffuse),    0.5f, 0.f, 100.f);
                    ImGui::DragFloat3("Direction XYZ", glm::value_ptr(lightDiff->GetProperties().Direction),  0.5f, 0.f, 100.f);
                    ImGui::DragFloat3("Ambient XYZ",   glm::value_ptr(lightDiff->GetProperties().Ambient),    0.5f, 0.f, 100.f);
                    ImGui::DragFloat3("Specular XYZ",  glm::value_ptr(lightDiff->GetProperties().Specular),   0.5f, 0.f, 100.f);
                   

                }

                if (lightPoint && light->m_ID == lightPoint->m_ID)
                {

                    if (ImGui::Button("Point Button"))
                    {

                    }


                    ImGui::InputFloat("Pos X", &lightPoint->GetTransform()->GetPos().x);
                    ImGui::InputFloat("Pos Y", &lightPoint->GetTransform()->GetPos().y);
                    ImGui::InputFloat("Pos Z", &lightPoint->GetTransform()->GetPos().z);


                    ImGui::DragFloat3("Ambient XYZ",    glm::value_ptr(lightPoint->GetProperties().Ambient),    0.5f, 0.f, 100.f);
                    ImGui::DragFloat3("Diffuse XYZ",    glm::value_ptr(lightPoint->GetProperties().Diffuse),    0.5f, 0.f, 100.f);
                    ImGui::DragFloat3("Specular XYZ",   glm::value_ptr(lightPoint->GetProperties().Specular),   0.5f, 0.f, 100.f);
                    
                    ImGui::DragFloat("Constant XYZ",    &lightPoint->GetProperties().Constant,   0.5f, 0.f, 100.f);
                    ImGui::DragFloat("Linear XYZ",      &lightPoint->GetProperties().Linear,     0.5f, 0.f, 100.f);
                    ImGui::DragFloat("Quadratic XYZ",   &lightPoint->GetProperties().Quadratic,  0.5f, 0.f, 100.f);





                }
                if (lightSpot && light->m_ID == lightSpot->m_ID)
                {
                    if (ImGui::Button("Spot Button"))
                    {

                    }


                    ImGui::InputFloat("Pos X", &lightSpot->GetTrans()->GetPos().x);
                    ImGui::InputFloat("Pos Y", &lightSpot->GetTrans()->GetPos().y);
                    ImGui::InputFloat("Pos Z", &lightSpot->GetTrans()->GetPos().z);

                    ImGui::DragFloat3("Ambient XYZ",    glm::value_ptr(lightSpot->GetProperties().Ambient),     0.5f, 0.f, 100.f);
                    ImGui::DragFloat3("Diffuse XYZ",    glm::value_ptr(lightSpot->GetProperties().Diffuse),     0.5f, 0.f, 100.f);
                    ImGui::DragFloat3("Specular XYZ",   glm::value_ptr(lightSpot->GetProperties().Specular),    0.5f, 0.f, 100.f);

                    ImGui::DragFloat("Constant XYZ",    &lightSpot->GetProperties().Constant,   0.5f, 0.f, 100.f);
                    ImGui::DragFloat("Linear XYZ",      &lightSpot->GetProperties().Linear,     0.5f, 0.f, 100.f);
                    ImGui::DragFloat("Quadratic XYZ",   &lightSpot->GetProperties().Quadratic,  0.5f, 0.f, 100.f);
                }





                ImGui::TreePop();
            }
            ImGui::PopID();

            
        }

        ImGui::TreePop();
    }


    /// ENTITIES ///
    if (ImGui::TreeNodeEx("Entities", ImGuiTreeNodeFlags_DefaultOpen))
    {
            
            std::shared_ptr<Entity> entityToDelete;
            std::shared_ptr<Shader> selectedShad;
            
            std::shared_ptr<HertzTexture> selectedTexture;

            using EntityPtr = std::shared_ptr<Entity>;
            if (ImGui::Button("Create Entity"))
            {
                EntityPtr newEntity = m_EntityManager->CreateEntity();
                std::cout << "EDITOR : CREATED ENTITY!" << std::endl;
            }

        for (auto it = m_EntityManager->m_entityList.begin(); it != m_EntityManager->m_entityList.end(); it++)
        {
            
            EntityPtr en = *it;
            if (!en)
            {
                continue;
            }
            std::string* entityName = en->GetName();
            if (entityName == nullptr || *entityName == "" || *entityName == " ")
            {
                __debugbreak;
            }
            std::string uniqueIDstring = std::to_string(reinterpret_cast<uintptr_t>(en.get()));

            ImGui::PushID((void*)en.get());

            //std::cout << uniqueIDstring << "MEEMEMEMEMEMEMEMEM" << std::endl;


            std::string RenameID = "Renamenr##" + uniqueIDstring;
            std::string HandleMeshID = "HandleMeshnr##" + uniqueIDstring;
            std::string TreeID = *entityName + "##" + uniqueIDstring;
            std::string DiffuseID = "diffuse##" + uniqueIDstring;
            std::string SpecularID = "specular##" + uniqueIDstring;

            std::shared_ptr<HertzTexture> texDiffuse = en->GetDiffuseMap();
            std::shared_ptr<HertzTexture> texSpecular = en->GetSpecularMap();
            


            if (ImGui::TreeNodeEx(TreeID.c_str()))
            {
                
                if (ImGui::Button("Delete Entity"))
                {

                    entityToDelete = en;
                    
                }
                ImGui::SameLine();
                if (ImGui::Button("Rename"))
                {
                    entityToRename = en;
                    ImGui::OpenPopup(RenameID.c_str());
                }
                ImGui::Text("Transform");
                ImGui::InputFloat("Pos X", &en->GetTransform()->GetPos().x, 1.f);
                ImGui::InputFloat("Pos Y", &en->GetTransform()->GetPos().y, 1.f);
                ImGui::InputFloat("Pos Z", &en->GetTransform()->GetPos().z, 1.f);

                ImGui::Separator();

                ImGui::Text("Rotation");
                ImGui::DragFloat("Rot X", & en->GetTransform()->GetRot().x, 1.f, -360.f, 360.f);
                ImGui::DragFloat("Rot Y", & en->GetTransform()->GetRot().y, 1.f, -360.f, 360.f);
                ImGui::DragFloat("Rot Z", & en->GetTransform()->GetRot().z, 1.f, -360.f, 360.f);

                ImGui::Separator();

                ImGui::Text("Scale");
                ImGui::InputFloat("Scale X", &en->GetTransform()->GetScale().x, 1.f);
                ImGui::InputFloat("Scale Y", &en->GetTransform()->GetScale().y, 1.f);
                ImGui::InputFloat("Scale Z", &en->GetTransform()->GetScale().z, 1.f);
                
                ImGui::Separator();
                

                
                if (ImGui::BeginPopup(RenameID.c_str()))
                {
                    if (en->GetMesh())
                    {
                        std::string meshname = en->GetMesh()->GetName();
                    }
                    ImGui::Text("Enter new Entity name... ");
                    
                    ImGui::InputText("newname...", &m_stringBuffer);

                    

                    if (ImGui::Button("Confirm"))
                    {
                        if (entityToRename)
                        {
                            entityToRename->SetName(std::string(m_stringBuffer));

                        }

                    }

                    ImGui::SameLine();

                    if (ImGui::Button("Cancel"))
                    {
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::EndPopup();

                }


                if (ImGui::Button("Diffuse Texture"))
                {
                    ImGui::OpenPopup(DiffuseID.c_str());
                }

                if (texDiffuse)
                {

                    ImGui::SameLine();
                    ImGui::Text("%s", texDiffuse->GetName().c_str());
                }
                else
                {
                    ImGui::SameLine();
                    ImGui::Text("No Diffuse Set");
                }
                if (ImGui::Button("Specular Texture"))
                {
                    ImGui::OpenPopup(SpecularID.c_str());
                }
                if (texSpecular)
                {
                    ImGui::SameLine();
                    ImGui::Text("%s", texSpecular->GetName().c_str());

                }
                else
                {
                    ImGui::SameLine();
                    ImGui::Text("No Specular Set");
                }

                
                
                if (ImGui::Button("Handle Mesh"))
                {
                    ImGui::OpenPopup(HandleMeshID.c_str());
                    std::cout << "print" << std::endl;
                }

                
                if (ImGui::BeginPopup(DiffuseID.c_str()))
                {
                    ImGui::Text("Loaded Textures");
                    std::vector<std::shared_ptr<HertzTexture>> textures = m_TextureManager->GetTextureList();

                    if (ImGui::BeginListBox(DiffuseID.c_str()))
                    {
                        
                        for (auto& tex : textures)
                        {
                            bool isSelected = (tex == texDiffuse);

                            if (ImGui::Selectable(tex->GetName().c_str(), isSelected))
                            {
                                en->SetDiffuseMap(tex);
                                en->UpdateTextureTypes();
                            }
                            if (isSelected)
                            {
                                ImGui::SetItemDefaultFocus();
                            }


                        }
                        ImGui::EndListBox();
                    }

                    ImGui::EndPopup();
                }

                if (ImGui::BeginPopup(SpecularID.c_str()))
                {
                    ImGui::Text("Loaded Textures");
                    std::vector<std::shared_ptr<HertzTexture>> textures = m_TextureManager->GetTextureList();

                    if (ImGui::BeginListBox(SpecularID.c_str()))
                    {

                        for (auto& tex : textures)
                        {
                            bool isSelected = (tex == texSpecular);
                            

                            if (ImGui::Selectable(tex->GetName().c_str(), isSelected))
                            {
                                en->SetSpecularMap(tex);
                                en->UpdateTextureTypes();
                            }
                            if (isSelected)
                            {
                                ImGui::SetItemDefaultFocus();
                            }


                        }
                        ImGui::EndListBox();
                    }

                    ImGui::EndPopup();
                }
                

                ImGui::SameLine();
                std::string meshnamestring;
                if (en->GetMesh())
                {
                    meshnamestring = en->GetMesh()->GetName();
                }
                else
                {
                    meshnamestring = "no mesh selected";
                }
                ImGui::Text("%s", meshnamestring.c_str());



                if (ImGui::BeginPopup(HandleMeshID.c_str()))
                {
                    ImGui::Text("Loaded meshes:");
                    std::vector<std::shared_ptr<Mesh>> meshes = m_MeshManager->GetCache();

                    if (ImGui::BeginListBox(HandleMeshID.c_str(), ImVec2(100.f, 6 * ImGui::GetTextLineHeightWithSpacing())))
                    {
                        for (auto& mesh : meshes)
                        {
                            bool isSelected = (en->GetMesh() == mesh);

                            if (ImGui::Selectable(mesh->GetName().c_str(), isSelected))
                            {
                                en->SetMesh(mesh);
                                //std::cout << "Trying to set Mesh" << std::endl;
                            }
                            if (isSelected)
                            {
                                ImGui::SetItemDefaultFocus();
                            }

                        }
                        ImGui::EndListBox();
                    }

                    if (ImGui::Button("Clear Mesh"))
                    {
                        en->ClearMesh();
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::SameLine();

                    if (ImGui::Button("Close"))
                    {
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();
                }
                

                
                
                ImGui::TreePop();
            }

           
            ImGui::PopID();
        }

        if (entityToDelete)
        {
            m_EntityManager->DeleteEntity(entityToDelete);
            entityToDelete = nullptr;
        }

        //Rename Entity

        ImGui::TreePop();
    }
    

    ImGui::Separator();
    ImGui::ColorEdit3("clear color", (float* )&clear_color); 

    if (ImGui::Button("Button")) {
        
        counter++;
    }
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    
    ImGui::End();



    

}





