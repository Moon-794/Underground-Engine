//Editor Application for creating games using the Underground Engine.
//Target platforms: Windows

//Ok so first things first the user would need to select a game to work on.
//Games arent simple, thus we need a custom folder structure that defines the source for the game application

//..
    //projectName.project <- holds various configuration settings
    //Scenes/
        //scene1.scene <- contains the structure for the objects and components
        //scene2.scene
    //Assets/
        //Models/
        //Textures/
        //Materials/
        //Components/

//Will probably change later but good enough for now.
//
//Ok so, the primary purpose of the editor is to provide a set of tools to allow the developer to construct
//a game by building scenes full of gameobjects with components.
//While the game is in development, it will have the folder structure above, and changes made in the editor are
//saved to file.

//The editor can even preview the game, and finally build the game with the assets nicely secured
//The building part will require using a terminal in code which sounds fun

#include <iostream>
#include "engine.h"
#include "ProjectLoader.h"

int main()
{
    std::cout << "Underground Editor - VA_2" << "\n";
    engine ue;
    return 0;
}