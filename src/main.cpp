#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "../include/CPUCollector.hpp"
#include "../include/MemoryCollector.hpp"
#include <cstddef>


int main(){
    InitWindow(800, 650, "Nabla Control");
    SetTargetFPS(60);
    rlImGuiSetup(true);
    auto& style = ImGui::GetStyle();
    style.FrameRounding = 19.0f;
    CpuUsage cpu = CpuUsageCalculate();
    double lastcpu = 0.0;

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

        if (ImGui::GetTime() - lastcpu >= 1){lastcpu = ImGui::GetTime(); cpu = CpuUsageCalculate();}
        if (ImGui::CollapsingHeader("Memory", ImGuiTreeNodeFlags_DefaultOpen)){
            ImGui::Indent();
            ImGui::SeparatorText(" Memory used ");
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, {1, 0,0,1});
            ImGui::ProgressBar(usedGB / mem.memory_totalGB);
            ImGui::PopStyleColor();
            ImGui::Separator();
            ImGui::TextColored({1, 1, 0, 1}, "Memory Used: %.2fGb", usedGB);
            ImGui::SeparatorText(" Memory Available "); 
            ImGui::ProgressBar(mem.memory_AvaliableGB / mem.memory_totalGB);
            ImGui::Separator();
            ImGui::TextColored({1.0, 1.0, 0, 1}, "Memory Available: %.2fGB", mem.memory_AvaliableGB);
            ImGui::Unindent();
        } 
        if (ImGui::CollapsingHeader("CPU", ImGuiTreeNodeFlags_DefaultOpen)){
            ImGui::Indent();
            ImGui::SeparatorText("Cpu");
            ImGui::ProgressBar(cpu.cpu / 100.0f);
            for (std::size_t i=0; i < cpu.cpus.size(); i++){
                ImGui::Text("Cpu %zu", i);
                ImGui::SameLine();
                ImGui::ProgressBar(cpu.cpus[i] / 100.0f); 
            }
            ImGui::Unindent();
        }
    
        
        ImGui::End();
        
        
        
        rlImGuiEnd();
        EndDrawing();
    }
}
