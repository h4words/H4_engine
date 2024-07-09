#include "Application.hpp"
#include "mapeditor/MapEditor.hpp"

int main(int argc, char *argv[])
{
#ifdef MAP_EDITOR
    H4_engine::MapEditor editor;
    editor.start(500, 700);    
#else
    H4_engine::Application app;
    app.start(1000, 800, "H4_engine");
#endif
    return 0;
}