#pragma once

class EditorWindow
{
    //We will have lots of these, will need an init and a draw function
    //Init is mostly for weird ones like scene/game views
    //Draw is universal, everything will need imgui stuff drawn every frame
public:
    EditorWindow();

    void InitWindow();
    void Draw();
};

class EditorInterface
{
    //What do we want you to have
    //
};

