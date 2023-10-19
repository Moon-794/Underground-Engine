#ifndef TEXTURE
#define TEXTURE
#include <iostream>
class Texture
{
    public:
        unsigned int ID;
        Texture(std::string path);
        void Use();
};

#endif