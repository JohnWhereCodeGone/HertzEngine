#include "HertzEditor.h"
#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"
#include "../Entity/Entity.h"
#include "HertzTexture.h"

#include "TextureManager.h"


bool show_demo_window = true;
bool show_another_window = false;
glm::vec3 clear_color(1.0f, 0.0f, 1.0f);
int counter = 0.0f;
float f;



void HertzEditor::EditorUI(GLFWwindow* window)
{
    

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.


    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);


    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button")) {
        // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    }
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    //top bar

    //todo - iterate through all textures, set them all to the corresponding mipmap level.

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

    ImGui::End();

    

}

void HertzEditor::InitUI(MessagingQueue &queue)
{
    //this->m_messagequeue = queue;
}



