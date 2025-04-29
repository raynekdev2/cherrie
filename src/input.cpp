#include "cherrie.h"
#include <windows.h>

static bool ch_keys[256] = { false };
static bool ch_mouse_buttons[5] = { false };
static POINT ch_mouse_pos = {0};
static int ch_mouse_scroll = 0;

void ch_PollEvents() {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            ch_RequestQuit();
        }
        else if (msg.message == WM_MOUSEWHEEL) {
            ch_mouse_scroll += GET_WHEEL_DELTA_WPARAM(msg.wParam) / WHEEL_DELTA;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Update mouse position
    GetCursorPos(&ch_mouse_pos);
    ScreenToClient(GetConsoleWindow(), &ch_mouse_pos);

    // Update mouse buttons
    ch_mouse_buttons[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
    ch_mouse_buttons[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000);
    ch_mouse_buttons[2] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000);

    // Update keys
    for (int i = 0; i < 256; ++i) {
        ch_keys[i] = (GetAsyncKeyState(i) & 0x8000);
    }
}

bool ch_KeyDown(int keycode) {
    return ch_keys[keycode];
}

bool ch_MouseDown(int button) {
    if (button < 0 || button >= 5) return false;
    return ch_mouse_buttons[button];
}

int ch_GetMouseX() {
    return ch_mouse_pos.x;
}

int ch_GetMouseY() {
    return ch_mouse_pos.y;
}

int ch_GetMouseScroll() {
    int scroll = ch_mouse_scroll;
    ch_mouse_scroll = 0; // Reset after reading
    return scroll;
}

void ch_RequestQuit() {
    PostQuitMessage(0);
}
