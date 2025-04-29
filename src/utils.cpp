#include "cherrie.h"
#include <windows.h>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std::chrono;

static auto ch_start_time = steady_clock::now();

double ch_GetTime() {
    auto now = steady_clock::now();
    return duration_cast<duration<double>>(now - ch_start_time).count();
}

void ch_Sleep(int ms) {
    std::this_thread::sleep_for(milliseconds(ms));
}

void ch_Log(const char* msg) {
    std::cout << "[ch] " << msg << std::endl;
}

void ch_SetFPSLimit(int fps) {
    // TODO
}

void ch_ShowPerformanceOverlay(bool show) {
    // TODO
}
