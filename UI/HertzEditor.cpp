#include "HertzEditor.h"
//#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"
#include "../Entity/Entity.h"
#include "HertzTexture.h"

#include "TextureManager.h"
#include "../Camera.h"
#include "../Entity/EntityManager.h"
#include "../Transform.h"
#include "../Shaders/HertzShader.h"
#include "../imgui_stdlib.h"

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
        ImGui::InputFloat("Transform X", &m_camRef->vPos.x);
        ImGui::InputFloat("Transform Y", &m_camRef->vPos.y);
        ImGui::InputFloat("Transform Z", &m_camRef->vPos.z);
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

    //Create, delete - Name, model, texture, position, rotation, scale.
    if (ImGui::TreeNodeEx("Entities", ImGuiTreeNodeFlags_DefaultOpen))
    {
            std::shared_ptr<Entity> entityToDelete;
            
            std::shared_ptr<Shader> selectedShad;

            using EntityPtr = std::shared_ptr<Entity>;
            if (ImGui::Button("Create Entity"))
            {
                EntityPtr newEntity = m_EntityManager->CreateEntity();
                std::cout << "EDITOR : CREATED ENTITY!" << std::endl;
            }

        for (auto it = m_EntityManager->m_entityList.begin(); it != m_EntityManager->m_entityList.end(); it++)
        {
            
            EntityPtr en = *it;
            std::string* entityName = en->GetName();
            
            
            

            if (ImGui::TreeNodeEx(entityName->c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                
                if (ImGui::Button("Delete Entity"))
                {

                    entityToDelete = en;
                    std::cout << "EDITOR DELETING ENTITY!";
                    
                }
                if (ImGui::Button("Rename"))
                {
                    entityToRename = en;
                    ImGui::OpenPopup("Rename Entry");
                    std::cout << "Selected Entity to rename is " << *entityName << std::endl;
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

                
                if (ImGui::BeginPopup("Rename Entry"))
                {
                    static char newName[256] = "";

                    ImGui::Text("Enter New Name:");
                    ImGui::InputText("newname...", newName, IM_ARRAYSIZE(newName));

                    if (ImGui::Button("Confirm"))
                    {
                        if (entityToRename)
                        {
                            entityToRename->SetName(std::string(newName));

                        }

                    }

                    ImGui::SameLine();

                    if (ImGui::Button("Cancel"))
                    {
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::EndPopup();

                }
                ImGui::TreePop();
            }

            
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





