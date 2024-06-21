#include "Application.hpp"

int main(int argc, char *argv[])
{
    H4_engine::Application app;
    app.start(1000, 800, "H4_engine");
    return 0;
}