#include "cherrie.h"
#include <vector>
#include <cmath>

// ============================
// Štruktúry scény
// ============================

struct RaySphere {
    Vec3 center;
    float radius;
    Vec3 color;
};

static std::vector<RaySphere> ch_spheres;

// Framebuffer
static uint32_t* ch_fb = nullptr;
static int ch_fb_width = 0;
static int ch_fb_height = 0;

static void ch_UpdateFramebuffer() {
    ch_fb = (uint32_t*)ch_GetFramebuffer();
    ch_fb_width = ch_GetFramebufferWidth();
    ch_fb_height = ch_GetFramebufferHeight();
}

// ============================
// Funkcie pre raytracer
// ============================

bool ch_EnableRayTracing() {
    return true; // Raytracing je aktivovaný
}

void ch_AddRaySphere(float x, float y, float z, float radius, int r, int g, int b) {
    ch_spheres.push_back({ch_Vec3(x, y, z), radius, ch_Vec3(r / 255.0f, g / 255.0f, b / 255.0f)});
}

void ch_ClearRayScene() {
    ch_spheres.clear();
}

bool ch_RayIntersectSphere(const Vec3& origin, const Vec3& dir, const RaySphere& sphere, float& t) {
    Vec3 oc = {origin.x - sphere.center.x, origin.y - sphere.center.y, origin.z - sphere.center.z};
    float a = ch_Dot(dir, dir);
    float b = 2.0f * ch_Dot(oc, dir);
    float c = ch_Dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return false;
    else {
        t = (-b - sqrtf(discriminant)) / (2.0f * a);
        return t > 0;
    }
}

void ch_RenderRayScene() {
    if (!ch_fb) ch_UpdateFramebuffer();

    for (int y = 0; y < ch_fb_height; ++y) {
        for (int x = 0; x < ch_fb_width; ++x) {
            Vec3 ray_origin = {0, 0, -5};
            Vec3 ray_dir = {
                (x - ch_fb_width / 2) / (float)ch_fb_width,
                (ch_fb_height / 2 - y) / (float)ch_fb_height,
                1.0f
            };
            ray_dir = ch_Normalize(ray_dir);

            Vec3 color = {0.0f, 0.0f, 0.0f}; // Background black
            float closest_t = 1e9;

            for (const auto& sphere : ch_spheres) {
                float t;
                if (ch_RayIntersectSphere(ray_origin, ray_dir, sphere, t)) {
                    if (t < closest_t) {
                        closest_t = t;
                        color = sphere.color;
                    }
                }
            }

            int idx = y * ch_fb_width + x;
            ch_fb[idx] = ((int)(color.x * 255) << 16) |
                         ((int)(color.y * 255) << 8) |
                         ((int)(color.z * 255));
        }
    }
}
