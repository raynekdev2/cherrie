#include "cherrie.h"
#include <cstring>

// ====================
// Text systém
// ====================

static uint32_t* ch_font_bitmap = nullptr;
static int ch_font_tex_width = 0;
static int ch_font_tex_height = 0;
static int ch_glyph_width = 0;
static int ch_glyph_height = 0;
static bool ch_font_loaded = false;

bool ch_LoadFont(const char* path, int glyphW, int glyphH) {
    // TODO: skutočné načítanie bitmapy, teraz fake
    ch_font_tex_width = 256;
    ch_font_tex_height = 256;
    ch_glyph_width = glyphW;
    ch_glyph_height = glyphH;

    ch_font_bitmap = new uint32_t[ch_font_tex_width * ch_font_tex_height];
    memset(ch_font_bitmap, 255, ch_font_tex_width * ch_font_tex_height * sizeof(uint32_t)); // fake biely font

    ch_font_loaded = true;
    return true;
}

void ch_UnloadFont() {
    if (ch_font_bitmap) {
        delete[] ch_font_bitmap;
        ch_font_bitmap = nullptr;
    }
    ch_font_loaded = false;
}

void ch_DrawGlyph(int screen_x, int screen_y, char c, int r, int g, int b) {
    if (!ch_font_loaded) return;
    if (!ch_font_bitmap) return;

    uint32_t* fb = (uint32_t*)ch_GetFramebuffer();
    int fb_w = ch_GetFramebufferWidth();
    int fb_h = ch_GetFramebufferHeight();

    int gx = (c % 16) * ch_glyph_width;
    int gy = (c / 16) * ch_glyph_height;

    for (int y = 0; y < ch_glyph_height; ++y) {
        for (int x = 0; x < ch_glyph_width; ++x) {
            int font_idx = (gy + y) * ch_font_tex_width + (gx + x);
            uint32_t pixel = ch_font_bitmap[font_idx];

            if ((pixel & 0xFFFFFF) != 0xFFFFFF) { // nie je biely = kreslíme
                int draw_x = screen_x + x;
                int draw_y = screen_y + y;
                if (draw_x >= 0 && draw_y >= 0 && draw_x < fb_w && draw_y < fb_h) {
                    fb[draw_y * fb_w + draw_x] = (r << 16) | (g << 8) | b;
                }
            }
        }
    }
}

void ch_DrawText(const char* text, int x, int y, int r, int g, int b) {
    if (!ch_font_loaded) return;

    int cursor_x = x;
    int len = strlen(text);
    for (int i = 0; i < len; ++i) {
        ch_DrawGlyph(cursor_x, y, text[i], r, g, b);
        cursor_x += ch_glyph_width;
    }
}

int ch_TextWidth(const char* text) {
    if (!ch_font_loaded) return 0;
    return strlen(text) * ch_glyph_width;
}

int ch_TextHeight() {
    if (!ch_font_loaded) return 0;
    return ch_glyph_height;
}
