#include "cherrie.h"
#include <cmath>
#include <algorithm> // Dôležité pre min/max

static uint32_t* ch_fb = nullptr;
static int ch_fb_width = 0;
static int ch_fb_height = 0;

static void ch_UpdateFramebuffer() {
    ch_fb = (uint32_t*)ch_GetFramebuffer();
    ch_fb_width = ch_GetFramebufferWidth();
    ch_fb_height = ch_GetFramebufferHeight();
}

static float* ch_zbuffer = nullptr;

extern uint32_t* ch_GetFramebuffer();
extern int ch_GetFramebufferWidth();
extern int ch_GetFramebufferHeight();

void ch_Init3D() {
    int w = ch_GetFramebufferWidth();
    int h = ch_GetFramebufferHeight();
    ch_zbuffer = new float[w * h];
}

void ch_ClearZBuffer() {
    int w = ch_GetFramebufferWidth();
    int h = ch_GetFramebufferHeight();
    for (int i = 0; i < w * h; ++i) ch_zbuffer[i] = 1e30f;
}

void ch_Shutdown3D() {
    delete[] ch_zbuffer;
}

void ch_DrawTriangle3D(ChVertex v0, ChVertex v1, ChVertex v2) {
    int w = ch_GetFramebufferWidth();
    int h = ch_GetFramebufferHeight();
    uint32_t* fb = ch_GetFramebuffer();

    auto transform = [w, h](float x, float y) -> std::pair<int, int> {
        int sx = (int)((x + 1.0f) * 0.5f * w);
        int sy = (int)((1.0f - (y + 1.0f) * 0.5f) * h);
        return { sx, sy };
    };

    auto [x0, y0] = transform(v0.x, v0.y);
    auto [x1, y1] = transform(v1.x, v1.y);
    auto [x2, y2] = transform(v2.x, v2.y);

    int min_y = std::min(std::min(y0, y1), y2);
    int max_y = std::max(std::max(y0, y1), y2);
    int min_x = std::min(std::min(x0, x1), x2);
    int max_x = std::max(std::max(x0, x1), x2);

    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            float denom = (float)((y1 - y2)*(x0 - x2) + (x2 - x1)*(y0 - y2));
            if (denom == 0.0f) continue;
            float a = ((y1 - y2)*(x - x2) + (x2 - x1)*(y - y2)) / denom;
            float b = ((y2 - y0)*(x - x2) + (x0 - x2)*(y - y2)) / denom;
            float c = 1.0f - a - b;
            if (a >= 0 && b >= 0 && c >= 0) {
                float z = a*v0.z + b*v1.z + c*v2.z;
                int idx = y * w + x;
                if (idx >= 0 && idx < w * h) {
                    if (z < ch_zbuffer[idx]) {
                        ch_zbuffer[idx] = z;
                        uint8_t r = (uint8_t)(a*v0.r + b*v1.r + c*v2.r);
                        uint8_t g = (uint8_t)(a*v0.g + b*v1.g + c*v2.g);
                        uint8_t b_ = (uint8_t)(a*v0.b + b*v1.b + c*v2.b);
                        fb[idx] = (r << 16) | (g << 8) | (b_);
                    }
                }
            }
        }
    }
}
