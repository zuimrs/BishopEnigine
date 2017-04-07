#ifndef _WINDOW_H_
#define _WINDOW_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
using namespace std;

#ifndef _CONST_H_

#define DEFAULT_WINDOW_TITLE "Default"
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600
#define DEFAULT_WINDOW_FULL_SCREEN false
#define DEFAULT_WINDOW_POSX 0
#define DEFAULT_WINDOW_POSY 0


#endif




class WindowSize
{
public:
    int height;
    int width;
};
class WindowPos
{
public:
    int window_posX;
    int window_posY;
};

class Window
{

private:
    vector<void(*)(void)> _windowFuncSequence;
    string _windowTitle;
    WindowSize _windowSize;
    WindowPos _windowPos;
    bool _isFullScreen;
    GLFWwindow * _windowInstance;
public:
    Window(
        const string title = DEFAULT_WINDOW_TITLE,
        const int width = DEFAULT_WINDOW_WIDTH,
        const int height = DEFAULT_WINDOW_HEIGHT);
    ~Window();
    GLFWwindow * getWindowInstance(){return this->_windowInstance;};
    string getWindowTitle(){return this->_windowTitle;}
    WindowSize getWindowSize(){return this->_windowSize;};
    WindowPos getWindowPos(){return this->_windowPos;}
    void setWindowTitle(const string title){glfwSetWindowTitle(this->_windowInstance,title.c_str());}
    void setWindowSize(const int width,const int height);
    void setWindowPos(
        const int posX = DEFAULT_WINDOW_POSX,
        const int posY = DEFAULT_WINDOW_POSY,
        const bool fullScreen = DEFAULT_WINDOW_FULL_SCREEN);
    void pushFunctionCallback(void(*)(void));
private:
    bool glFuncInit();
    void windowMainLoop();

};


#endif