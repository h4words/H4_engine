# H4_engine
This is the engine I'm creating for my zombie survival game. 
The game will be relatively simple graphically, but it will require certain features that ready-made engines cannot provide, primarily modding
## How to build
1. install msys2
2. you may need to add C:\msys64\mingw64\bin to PATH
3. install git
4. clone (or download as .zip) project and in root directory run ```git submodule init``` and then ```git submodule update```
5. install gcc compiler with ```pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain```
6. install cmake with ```pacman -S mingw-w64-x86_64-cmake```
7. run MSYS2 MINGW64 and install some project dependencies:
   ```pacman -S mingw-w64-x86_64-SDL2```
   ```pacman -S mingw-w64-x86_64-freetype```
8. cmake build targets of engine are ```game``` and ```map_editor```
