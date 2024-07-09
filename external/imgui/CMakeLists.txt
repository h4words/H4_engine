project(imgui)
add_library(
        imgui STATIC
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_internal.h
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_opengl3_loader.h
        imgui/backends/imgui_impl_opengl3.h
        imgui/backends/imgui_impl_sdl2.cpp
        imgui/backends/imgui_impl_sdl2.h
        imgui/misc/cpp/imgui_stdlib.cpp
)
target_include_directories(
        imgui
        PUBLIC
        imgui
        imgui/backends
        ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(imgui PUBLIC ${SDL2_LIBRARIES} glad)
