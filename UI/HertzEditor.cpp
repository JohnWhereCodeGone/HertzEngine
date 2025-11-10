#include "HertzEditor.h"
#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"
#include "../Entity/Entity.h"
#include "HertzTexture.h"

#include "TextureManager.h"
#include "../Camera.h"


bool show_demo_window = true;
bool show_another_window = false;
glm::vec3 clear_color(1.0f, 0.0f, 1.0f);
int counter = 0.0f;
float f;

glm::vec3 postest;



HertzEditor::HertzEditor()
{
   
}

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
    

    ImGuiViewport *port = ImGui::GetMainViewport();
    ImVec2 topleftpos = ImVec2(port->Pos.x - 10.f, port->Pos.y);


    //ImGui::SetNextWindowPos()
    ImGui::Begin("Camera Editor");                          


    ImGui::Text("This is some useful text.");               
    ImGui::Checkbox("checkbox", &show_demo_window);      
    ImGui::Checkbox("checkbox", &show_another_window);


    
    ImGui::InputFloat("Camera X", &camRef->vPos.x);
    ImGui::InputFloat("Camera Y", &camRef->vPos.y);
    ImGui::InputFloat("Camera Z", &camRef->vPos.z);


    ImGui::ColorEdit3("clear color", (float*)&clear_color); 

    if (ImGui::Button("Button")) {
        
        counter++;
    }
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    
    ImGui::End();



    

}

void HertzEditor::InitUI(std::shared_ptr<Camera> cam)
{
    this->camRef = cam;
}



