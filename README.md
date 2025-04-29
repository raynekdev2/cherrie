# 🍒 Cherrie 2.0

**Cherrie** is a **modern, lightweight, and powerful** C++ graphics library designed for **2D**, **3D rendering**, **raytracing**, **textures**, and **system utilities** — without relying on OpenGL, Vulkan, or DirectX.  
Built from scratch with a respect for tradition and a hunger for innovation.

---

## ✨ Features

- 2D and 3D rendering
- Raytracing engine (basic and advanced)
- Texture loading and rendering
- Custom font support
- Math utilities (vectors, matrices, transforms)
- Input handling (keyboard, mouse)
- Image export (PNG, BMP, JPG)
- Video export (basic)
- Windows (.dll) and Linux (.so) support
- (Upcoming) macOS support

---

## 📜 Philosophy

We believe in:

- **Clarity over complexity**  
- **Performance over trendiness**  
- **Craftsmanship over shortcuts**

Cherrie is built to **respect your time, your CPU, and your passion**.

---

## 📦 Installation

> _Instructions coming soon!_

Manual build with CMake and MSYS2/MinGW64 on Windows or GCC/Clang on Linux.

---

## 🔥 Quick Example

```cpp
#include "cherrie.h"

int main() {
    ch_Init3D(); // Initialize Cherrie's 3D engine

    while (ch_AppRunning()) {
        ch_UpdateFramebuffer();  // Refresh framebuffer pointer
        ch_ClearZBuffer();        // Clear depth buffer

        ChVertex v0 = { -0.5f, -0.5f, 0.5f, 255, 0, 0 };
        ChVertex v1 = {  0.5f, -0.5f, 0.5f, 0, 255, 0 };
        ChVertex v2 = {  0.0f,  0.5f, 0.5f, 0, 0, 255 };

        ch_DrawTriangle3D(v0, v1, v2);

        ch_PresentFramebuffer();  // Display to screen
    }

    ch_Shutdown3D(); // Free resources
    return 0;
}
