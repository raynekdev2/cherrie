#include <windows.h>
#include "cherrie.h"

// === Interné ===
static HWND ch_hwnd;
static HDC ch_hdc;
static BITMAPINFO ch_bmi;
static uint32_t* ch_framebuffer;
static int ch_width;
static int ch_height;
static bool ch_running = true;

// === Window procedura ===
LRESULT CALLBACK ch_WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_DESTROY) {
        ch_running = false;
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// === Inicializácia ===
bool ch_InitGPU(int width, int height) {
    ch_width = width;
    ch_height = height;

    WNDCLASS wc = {};
    wc.lpfnWndProc = ch_WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "CherrieWindowClass";

    if (!RegisterClass(&wc)) return false;

    ch_hwnd = CreateWindowEx(
        0,
        "CherrieWindowClass",
        "Cherrie Engine",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    if (!ch_hwnd) return false;

    ch_hdc = GetDC(ch_hwnd);

    ZeroMemory(&ch_bmi, sizeof(ch_bmi));
    ch_bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    ch_bmi.bmiHeader.biWidth = width;
    ch_bmi.bmiHeader.biHeight = -height;
    ch_bmi.bmiHeader.biPlanes = 1;
    ch_bmi.bmiHeader.biBitCount = 32;
    ch_bmi.bmiHeader.biCompression = BI_RGB;

    ch_framebuffer = new uint32_t[width * height];
    ZeroMemory(ch_framebuffer, width * height * sizeof(uint32_t));

    return true;
}

// === Shutdown ===
void ch_ShutdownGPU() {
    delete[] ch_framebuffer;
    ReleaseDC(ch_hwnd, ch_hdc);
    DestroyWindow(ch_hwnd);
}

// === Frame management ===
void ch_BeginFrame() {
}

void ch_EndFrame() {
    StretchDIBits(
        ch_hdc,
        0, 0, ch_width, ch_height,
        0, 0, ch_width, ch_height,
        ch_framebuffer,
        &ch_bmi,
        DIB_RGB_COLORS,
        SRCCOPY
    );

    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// === Framebuffer access ===
uint32_t* ch_GetFramebuffer() {   // <-- TOTO JE DÔLEŽITÉ!
    return ch_framebuffer;
}

int ch_GetFramebufferWidth() {
    return ch_width;
}

int ch_GetFramebufferHeight() {
    return ch_height;
}
