#include "cherrie.h"
#include <cstring>

// ====================
// Textúrový systém
// ====================

struct ChTexture {
    uint32_t* pixels;
    int width;
    int height;
};

ChTexture* ch_CreateTexture(int width, int height) {
    ChTexture* tex = new ChTexture;
    tex->width = width;
    tex->height = height;
    tex->pixels = new uint32_t[width * height];
    memset(tex->pixels, 255, width * height * sizeof(uint32_t)); // default biela
    return tex;
}

void ch_DestroyTexture(ChTexture* tex) {
    if (!tex) return;
    if (tex->pixels) delete[] tex->pixels;
    delete tex;
}

bool ch_UploadTexture(ChTexture* tex, const void* data, int size) {
    if (!tex || !tex->pixels) return false;
    if (size != tex->width * tex->height * 4) return false; // 4 bajty na pixel (RGBA 8:8:8:8)

    memcpy(tex->pixels, data, size);
    return true;
}

void ch_DrawTexture(ChTexture* tex, int dst_x, int dst_y) {
    if (!tex || !tex->pixels) return;

    uint32_t* fb = (uint32_t*)ch_GetFramebuffer();
    int fb_w = ch_GetFramebufferWidth();
    int fb_h = ch_GetFramebufferHeight();

    for (int y = 0; y < tex->height; ++y) {
        for (int x = 0; x < tex->width; ++x) {
            int tex_idx = y * tex->width + x;
            int fb_x = dst_x + x;
            int fb_y = dst_y + y;

            if (fb_x >= 0 && fb_y >= 0 && fb_x < fb_w && fb_y < fb_h) {
                uint32_t color = tex->pixels[tex_idx];

                if ((color & 0xFF000000) != 0x00000000) { // Alpha > 0 → kreslíme
                    fb[fb_y * fb_w + fb_x] = color;
                }
            }
        }
    }
}
