#ifndef WINDOW_KEY_EVENTS_HPP
#define WINDOW_KEY_EVENTS_HPP

# include "Sound.class.hpp"
# include "Bomberman.class.hpp"

class WindowKeyEvents {
    public:
        WindowKeyEvents();
        ~WindowKeyEvents();
        void windowKeyEvents(GLFWwindow *win);
        void soundKeyEvents(GLFWwindow *win, Sound *sound);
        void keyEventsWrapper(GLFWwindow *win, Sound *s);
};

#endif