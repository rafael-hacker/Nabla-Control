#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include <string>
#include <vector>
#include "../include/CPUCollector.hpp"
#include "../include/MemoryCollector.hpp"
#include "../include/DiskCollector.hpp"
#include "../include/Temperature.hpp"
#include "../include/ProcessCollector.hpp"
#include "../include/KillProcess.hpp"
#include <cstddef>


int main(){
    InitWindow(800, 650, "Nabla Control");
    SetTargetFPS(60);
    rlImGuiSetup(true);
    ImGui::StyleColorsDark();
    auto& style = ImGui::GetStyle();
    
    style.FrameRounding = 6.0f;
    style.WindowRounding = 12.0f;
    style.ItemSpacing = {12.0f, 10.0f};
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.07f, 0.09f, 0.95f);
    style.Colors[ImGuiCol_Header] = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0,0,0,0);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0,0,0,0);
    style.Colors[ImGuiCol_Border] = ImVec4(0.3f, 0.8f, 0.9f, 0.5f);
    style.WindowBorderSize = 1.5f;
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f,0.12f,0.16f,1);
    
    CpuUsage cpu = CpuUsageCalculate();
    double lastcpu = 0.0;

    while (!WindowShouldClose()){
        Memory mem = GetMemory();
        DiskSpace disk = GetDiskSpace();
        Temperature temperature = GetTemp();  
        std::vector<ProcessInfo> processes = ReadProcess();

        BeginDrawing();
        ClearBackground(Color({15,17,21,255}));
        rlImGuiBegin();
        float Used_disk_gb = disk.total - disk.avaliable;
        float usedGB = mem.memory_totalGB - mem.memory_AvaliableGB;
        ImGuiViewport *vp = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(vp->Pos);
        ImGui::SetNextWindowSize(vp->Size);

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse;
        
        ImGui::Begin("nabla-control", nullptr, flags);
        ImGui::TextColored({0.3f, 0.8f, 0.9f, 1}, "∇ Nabla Control ");
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::GetTime() - lastcpu >= 1){lastcpu = ImGui::GetTime(); cpu = CpuUsageCalculate();}
        if (ImGui::CollapsingHeader("Memory", ImGuiTreeNodeFlags_DefaultOpen)){
            ImGui::Indent();
            ImGui::SeparatorText(" Memory used ");
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, {0.9f, 0.3f, 0.3f, 1.0f});
            ImGui::ProgressBar(usedGB / mem.memory_totalGB);
            ImGui::PopStyleColor();
            ImGui::Separator();
            ImGui::TextColored({0.9f, 0.3f, 0.3f, 1.0f}, "Memory Used: %.2fGB", usedGB);
            ImGui::SeparatorText(" Memory Available "); 
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, {1.00f, 1.00f, 0.40f, 1.0f});
            ImGui::ProgressBar(mem.memory_AvaliableGB / mem.memory_totalGB);
            ImGui::PopStyleColor();
            ImGui::Separator();
            ImGui::TextColored({0.55f, 0.95f, 0.60f, 1.0f}, "Memory Available: %.2fGB", mem.memory_AvaliableGB);
            ImGui::Unindent();
        } 
        if (ImGui::CollapsingHeader("CPU", ImGuiTreeNodeFlags_DefaultOpen)){
            ImGui::Indent();
            ImGui::SeparatorText("Cpu");
            ImGui::ProgressBar(cpu.cpu / 100.0f);
            ImGui::SeparatorText("Cpus core");
            if (ImGui::CollapsingHeader("Cpus")){
                for (std::size_t i=0; i < cpu.cpus.size(); i++){
                    ImGui::Indent();
                    ImGui::Text("Cpu %zu", i);
                    ImGui::SameLine();
                    ImGui::ProgressBar(cpu.cpus[i] / 100.0f); 
                    ImGui::Unindent();
                }
            }
            ImGui::Unindent();
        }
        
        if (ImGui::CollapsingHeader("Disk", ImGuiTreeNodeFlags_DefaultOpen)){
            ImGui::Indent();
            ImGui::SeparatorText("Disk usage");
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, {0.9f, 0.3f, 0.3f, 1.0f});
            ImGui::ProgressBar(disk.percent_usage / 100.0f);
            ImGui::PopStyleColor();            

            ImGui::Separator();
            ImGui::TextColored({1, 0, 0, 1}, "Disk Usage %.2fGB", Used_disk_gb);
            ImGui::SeparatorText("Disk Available");
            
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, {0.3f, 0.85f, 0.4f, 1.0f});
            ImGui::ProgressBar(disk.percent_available / 100.0f);
            ImGui::PopStyleColor()
;
            ImGui::Separator();
            ImGui::TextColored({0, 1, 0, 1}, "Disk Available %.2fGB", disk.avaliable);
            ImGui::Unindent();
        }
    
        if (ImGui::CollapsingHeader("Temperature")){
            ImGui::Indent();
            ImGui::TextColored({1, 0,0, 0.6f}, "%s", temperature.type.c_str());
            ImGui::Separator();
            ImGui::Spacing();
            ImGui::TextColored({1, 0, 0, 1}, "%.2f°C", temperature.temperature_celsius);
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Process")){
            ImGui::Indent();
            if (ImGui::BeginTable("process table", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)){
                ImGui::TableSetupColumn("PID");
                ImGui::TableSetupColumn("Name");
                ImGui::TableHeadersRow();

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                for (std::size_t i=0; i < processes.size(); i++){
                    ImGui::TextColored({0.95f, 0.45f, 0.45f, 1.0f} ,"%d", processes[i].pid);
                    ImGui::SameLine();
                    std::string bnt_button = "Kill##" + std::to_string(processes[i].pid);
                    if (ImGui::SmallButton(bnt_button.c_str())){
                        kill_process(processes[i].pid);
                    }
                }

                ImGui::TableSetColumnIndex(1);
                
                for (std::size_t i=0; i < processes.size(); i++){
                    ImGui::TextColored({0.45f, 0.85f, 0.55f, 1.0f}, "%s", processes[i].name.c_str());
                }
                
                ImGui::EndTable();              
            }
            ImGui::Unindent();
        }

        ImGui::End();
        
        
        
        rlImGuiEnd();
        EndDrawing();
    }
}
