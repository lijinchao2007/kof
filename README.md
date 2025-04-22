# The King of Fighters (SDL-based)

A cross-platform implementation of **The King of Fighters**, using **SDL2**.  
Character configuration follows the **M.U.G.E.N** format.

> ⚠️ This project dates back to around **2015**, and may not run correctly on modern systems. Use at your own risk!


## ✨ Features

- Multi-platform support (Linux, macOS)
- Character format based on MUGEN
- Built using SDL2 and OpenGL
- Includes sound, graphics, font rendering, and input handling


## 🔧 Dependencies

### Ubuntu
```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-gfx-dev \
libsdl2-ttf-dev libsdl2-mixer-dev libglew-dev libgles2-mesa-dev
```

### macOS (via Homebrew)
```bash
brew install sdl2 sdl2_image sdl2_gfx sdl2_ttf sdl2_mixer glew
```

## 🛠️ Build Instructions

```bash
cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## ▶️ Run the Game

```bash
cd Resource
../build/kof
```

## 📸 Preview


https://github.com/user-attachments/assets/ff53fe0a-7dff-4ddb-a5e2-b58a183c7d64




Feel free to open issues or contribute improvements. Happy fighting! 🥋🔥
