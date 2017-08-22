#include "Sound.hpp"
#include "WindowKeyEvents.hpp"

WindowKeyEvents::WindowKeyEvents(){
}

WindowKeyEvents::~WindowKeyEvents(){
}

/***********************************
** performs window logic onKeyEvents
** i.e: closing window
************************************/
void WindowKeyEvents::windowKeyEvents(GLFWwindow *win)
{
    if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win, GLFW_TRUE);
}

/**********************************
** loads/ plays effects onKeyEvents
***********************************/
void WindowKeyEvents::soundKeyEvents(GLFWwindow *win, Sound *s)
{
    if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS   || glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS ||
        glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS )
        s->playEffectOnce(EFFECT_WALK);
}

/**************************************************
** wrappers function: handles all key events,
** by calling specific key events function handlers
***************************************************/
void WindowKeyEvents::keyEventsWrapper(GLFWwindow *win, Sound *s)
{
    this->windowKeyEvents(win);
    this->soundKeyEvents(win, s);
}