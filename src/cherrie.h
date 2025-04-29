#pragma once

#include <stdint.h>

// == CORE (GPU správa) ==
bool ch_InitGPU(int width, int height);
void ch_ShutdownGPU();
void ch_BeginFrame();
void ch_EndFrame();
uint32_t* ch_GetFramebuffer();
int ch_GetFramebufferWidth();
int ch_GetFramebufferHeight();
void ch_Sleep(int ms);

// == 2D kreslenie ==
void ch_DrawPixel(int x, int y, int r, int g, int b);
void ch_DrawLine(int x0, int y0, int x1, int y1, int r, int g, int b);
void ch_DrawRect(int x, int y, int w, int h, int r, int g, int b);
void ch_FillRect(int x, int y, int w, int h, int r, int g, int b);

// == 3D kreslenie ==
void ch_DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int r, int g, int b);

// == INPUT ==
void ch_PollEvents();
bool ch_KeyDown(int keycode);
bool ch_MouseDown(int button);
int ch_GetMouseX();
int ch_GetMouseY();
int ch_GetMouseScroll();
void ch_RequestQuit();

// == MATH ==
struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct Mat4 { float m[4][4]; };

Vec2 ch_Vec2(float x, float y);
Vec3 ch_Vec3(float x, float y, float z);
Vec4 ch_Vec4(float x, float y, float z, float w);

Vec3 ch_Normalize(Vec3 v);
float ch_Dot(Vec3 a, Vec3 b);
Vec3 ch_Cross(Vec3 a, Vec3 b);

Mat4 ch_Identity();
Mat4 ch_Translate(Vec3 v);
Mat4 ch_RotateY(float angle);
Mat4 ch_Perspective(float fov, float aspect, float znear, float zfar);

// == RAYTRACER ==
bool ch_EnableRayTracing();
void ch_AddRaySphere(float x, float y, float z, float radius, int r, int g, int b);
void ch_ClearRayScene();
void ch_RenderRayScene();

// == TEXT ==
bool ch_LoadFont(const char* path, int glyphW, int glyphH);
void ch_UnloadFont();
void ch_DrawText(const char* text, int x, int y, int r, int g, int b);
int ch_TextWidth(const char* text);
int ch_TextHeight();

// == TEXTURE ==
struct ChTexture;
ChTexture* ch_CreateTexture(int width, int height);
void ch_DestroyTexture(ChTexture* tex);
bool ch_UploadTexture(ChTexture* tex, const void* data, int size);
void ch_DrawTexture(ChTexture* tex, int dst_x, int dst_y);

// == UTIL ==
void ch_Log(const char* msg);
double ch_GetTime();

bool ch_InitGPU(int width, int height);
void ch_ShutdownGPU();
void ch_BeginFrame();
void ch_EndFrame();
uint32_t* ch_GetFramebuffer(); // nie void*
int ch_GetFramebufferWidth();
int ch_GetFramebufferHeight();
struct ChVertex {
    float x, y, z;
    uint8_t r, g, b;
};

// 3D API
void ch_Init3D();
void ch_ClearZBuffer();
void ch_DrawTriangle3D(ChVertex v0, ChVertex v1, ChVertex v2);
void ch_Shutdown3D();

void ch_Clear(int r, int g, int b);
void ch_DrawPixel(int x, int y, int r, int g, int b);
void ch_DrawLine(int x0, int y0, int x1, int y1, int r, int g, int b);
void ch_DrawRect(int x, int y, int w, int h, int r, int g, int b);
void ch_FillRect(int x, int y, int w, int h, int r, int g, int b);
