#include "cherrie.h"
#include <cmath>
#include <stdint.h>

static uint32_t* ch_fb = nullptr;
static int ch_fb_width = 0;
static int ch_fb_height = 0;

static void ch_UpdateFramebuffer() {
    ch_fb = ch_GetFramebuffer();
    ch_fb_width = ch_GetFramebufferWidth();
    ch_fb_height = ch_GetFramebufferHeight();
}

void ch_Clear(int r, int g, int b) {
    if (!ch_fb) ch_UpdateFramebuffer();
    uint32_t color = (r << 16) | (g << 8) | b;
    for (int i = 0; i < ch_fb_width * ch_fb_height; ++i) {
        ch_fb[i] = color;
    }
}

void ch_DrawPixel(int x, int y, int r, int g, int b) {
    if (!ch_fb) ch_UpdateFramebuffer();
    if (x < 0 || y < 0 || x >= ch_fb_width || y >= ch_fb_height) return;
    ch_fb[y * ch_fb_width + x] = (r << 16) | (g << 8) | b;
}

void ch_DrawLine(int x0, int y0, int x1, int y1, int r, int g, int b) {
    if (!ch_fb) ch_UpdateFramebuffer();
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        ch_DrawPixel(x0, y0, r, g, b);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void ch_DrawRect(int x, int y, int w, int h, int r, int g, int b) {
    if (!ch_fb) ch_UpdateFramebuffer();
    ch_DrawLine(x, y, x + w, y, r, g, b);
    ch_DrawLine(x + w, y, x + w, y + h, r, g, b);
    ch_DrawLine(x + w, y + h, x, y + h, r, g, b);
    ch_DrawLine(x, y + h, x, y, r, g, b);
}

void ch_FillRect(int x, int y, int w, int h, int r, int g, int b) {
    if (!ch_fb) ch_UpdateFramebuffer();
    for (int i = 0; i < h; ++i) {
        ch_DrawLine(x, y + i, x + w, y + i, r, g, b);
    }
}

