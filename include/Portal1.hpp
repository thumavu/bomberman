#ifndef PORTAL1_HPP
#define PORTAL1_HPP

#define STATIC_WALLS 64

#include "Player.hpp"

class Portal1{
public:
    Portal1();
    ~Portal1();
    void init();
    void draw();

private:
    GLuint VertexArrayID, destructibleTexture;
    GLuint programID, VAOs[STATIC_WALLS], VBOs[STATIC_WALLS], EBOs[STATIC_WALLS];

};
#endif
