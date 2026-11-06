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
    while (!WindowShouldClose()){
        Memory mem = GetMemory();
        BeginDrawing();
        ClearBackground(WHITE);
        rlImGuiBegin();
        
        ImGuiViewport *vp = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(vp->Pos);
        ImGui::SetNextWindowSize(vp->Size);

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;
        
        ImGui::Begin("nabla-control", nullptr, flags);
        ImGui::Text(" memory total: %.2f GB", mem.memory_totalGB);    
        ImGui::Text(" memory_Avaliable: %.2f GB", mem.memory_AvaliableGB);
        ImGui::Text(" Memory Free: %.2f GB", mem.memory_freeGB);
        ImGui::End();

        rlImGuiEnd();
        EndDrawing();
    }
}
