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

#include <iostream>

int main()
{
    std::cout << "Hello, world!" << "\n";
    return 0;
}