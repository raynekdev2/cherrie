#include "cherrie.h"
#include <cmath>

// ===================
// Vektory
// ===================

Vec2 ch_Vec2(float x, float y) {
    Vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

Vec3 ch_Vec3(float x, float y, float z) {
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

Vec4 ch_Vec4(float x, float y, float z, float w) {
    Vec4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

// ===================
// Operácie s vektormi
// ===================

Vec3 ch_Normalize(Vec3 v) {
    float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    if (len == 0.0f) return {0, 0, 0};
    return {v.x / len, v.y / len, v.z / len};
}

float ch_Dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 ch_Cross(Vec3 a, Vec3 b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// ===================
// Matice
// ===================

Mat4 ch_Identity() {
    Mat4 m = {};
    for (int i = 0; i < 4; ++i) {
        m.m[i][i] = 1.0f;
    }
    return m;
}

Mat4 ch_Translate(Vec3 v) {
    Mat4 m = ch_Identity();
    m.m[0][3] = v.x;
    m.m[1][3] = v.y;
    m.m[2][3] = v.z;
    return m;
}

Mat4 ch_RotateY(float angle) {
    Mat4 m = ch_Identity();
    float c = cosf(angle);
    float s = sinf(angle);
    m.m[0][0] =  c;
    m.m[0][2] =  s;
    m.m[2][0] = -s;
    m.m[2][2] =  c;
    return m;
}

Mat4 ch_Perspective(float fov, float aspect, float znear, float zfar) {
    Mat4 m = {};
    float tanHalfFov = tanf(fov / 2.0f);
    m.m[0][0] = 1.0f / (aspect * tanHalfFov);
    m.m[1][1] = 1.0f / tanHalfFov;
    m.m[2][2] = -(zfar + znear) / (zfar - znear);
    m.m[2][3] = -(2.0f * zfar * znear) / (zfar - znear);
    m.m[3][2] = -1.0f;
    return m;
}
