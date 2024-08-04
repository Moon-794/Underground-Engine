#include <iostream>
#include "engine.h"

int main(int argc, char** args)
{
    engine e;
    e.Init(800, 600);

    while(!glfwWindowShouldClose(e.window.get()))
    {
        glClearColor(0.12f, 0.16f, 0.26f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        e.Tick();
        e.Render();
    }

    return 0;
}