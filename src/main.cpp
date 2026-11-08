#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "core/SystemSnapshot.hpp"
#include "../include/MemoryCollector.hpp"


int main(){
    Systemsnapshot sys;
    InitWindow(800, 650, "Nabla Control");
    SetTargetFPS(60);
    rlImGuiSetup(true);
    auto& style = ImGui::GetStyle();
    style.FrameRounding = 19.0f;

    while (!WindowShouldClose()){
        Memory mem = GetMemory();
        BeginDrawing();
        ClearBackground(WHITE);
        rlImGuiBegin();
        float usedGB = mem.memory_totalGB - mem.memory_AvaliableGB;
        ImGuiViewport *vp = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(vp->Pos);
        ImGui::SetNextWindowSize(vp->Size);

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;
        
        ImGui::Begin("nabla-control", nullptr, flags);
        if (ImGui::CollapsingHeader("Memory", ImGuiTreeNodeFlags_DefaultOpen)){
            ImGui::Indent();
            ImGui::SeparatorText(" Memory used ");
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, {1, 0,0,1});
            ImGui::ProgressBar(usedGB / mem.memory_totalGB);
            ImGui::PopStyleColor();
            ImGui::SeparatorText(" Memory Available "); 
            ImGui::ProgressBar(mem.memory_AvaliableGB / mem.memory_totalGB);
            ImGui::Separator();
            ImGui::TextColored({1.0, 2.0, 0, 1.9}, "Memory Available: %.2fGB", mem.memory_AvaliableGB);
            ImGui::Unindent();
        }
        ImGui::End();

        rlImGuiEnd();
        EndDrawing();
    }
}
