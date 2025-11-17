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
    //Create, delete - Name, model, texture, position, rotation, scale. ---TODO Model / texture / shader
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
            

            std::cout << TreeID << std::endl;

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

                if (ImGui::Button("Specular Texture"))
                {
                    ImGui::OpenPopup(SpecularID.c_str());
                }


                
                
                if (ImGui::Button("Handle Mesh"))
                {
                    ImGui::OpenPopup(HandleMeshID.c_str());
                }

                
                if (ImGui::BeginPopup(DiffuseID.c_str()))
                {
                    ImGui::Text("Loaded Textures");
                    std::vector<std::shared_ptr<HertzTexture>> textures = m_TextureManager->GetTextureList();

                    if (ImGui::BeginListBox(DiffuseID.c_str()))
                    {
                        
                        for (auto& tex : textures)
                        {

                            if (ImGui::Selectable("name", true))
                            {

                            }
                            if (bool isElected = true)
                            {

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

                    if (ImGui::BeginListBox(DiffuseID.c_str()))
                    {

                        for (auto& tex : textures)
                        {
                            bool isSelected;
                            

                            if (ImGui::Selectable("name", true))
                            {

                            }
                            if (bool isElected = true)
                            {

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
                                std::cout << "Trying to set Mesh" << std::endl;
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





