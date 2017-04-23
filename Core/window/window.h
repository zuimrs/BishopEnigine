#ifndef _WINDOW_H_
#define _WINDOW_H_

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
using namespace std;

#include "const.h"


#ifndef _CONST_H_

#define DEFAULT_WINDOW_TITLE "Default"
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600
#define DEFAULT_WINDOW_FULL_SCREEN false
#define DEFAULT_WINDOW_POSX 0
#define DEFAULT_WINDOW_POSY 0
#define DEFAULT_WINDOW_FRAME_PER_SECOND 60
#define MAX_KEYS 1024
#define MAX_BUTTONS 32

#endif


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
class WindowSize
{
public:
    int windowHeight;
    int windowWidth;
};
class WindowPos
{
public:
    int windowPosX;
    int windowPosY;
};

class Window
{
// public methods
public:
    Window(
        const bool fullscreen = DEFAULT_WINDOW_FULL_SCREEN,
        const string title = DEFAULT_WINDOW_TITLE,
        const int width = DEFAULT_WINDOW_WIDTH,
        const int height = DEFAULT_WINDOW_HEIGHT);
    ~Window();

    // get
    GLFWwindow * getWindowInstance(){return this->_windowInstance;};
    WindowSize getWindowSize(){return this->_windowSize;};
    WindowPos getWindowPos(){return this->_windowPos;}
    string getWindowTitle(){return this->_windowTitle;}
    bool getWindowActive(){return this->_isWindowActive;}

    // set
    void setWindowTitle(const string title){glfwSetWindowTitle(this->_windowInstance,title.c_str());}
    void setWindowSize(const int width,const int height);
    void setWindowPos(
        const int posX = DEFAULT_WINDOW_POSX,
        const int posY = DEFAULT_WINDOW_POSY,
        const bool fullScreen = DEFAULT_WINDOW_FULL_SCREEN);

    // function call back
    void onStartFunctionCallback(void(*)(void));
    void onUpdateFunctionCallback(void(*)(void));
    // display control
    void initializeWindow();
    void showWindow();

 // private methods   
private:
    // glfwfunction init
    void glfwFunctionInit();
    // main loop
    void windowMainLoop();
    // display control
    void changeDisplayMode();
    // call back
    void windowMinisizeCallback();
    void windowDisplayModeChangeCallback(const int,const int);
    void startFunctionCallback();
    void updateFunctionCallback();

    // key & mouse
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
// private attributes
private:
    vector<void(*)(void)> _startFunctionSequence;
    vector<void(*)(void)> _updateFunctionSequence;
    string _windowTitle;
    WindowSize _windowSize;
    WindowPos _windowPos;
    bool _isFullScreen;
    bool _isWindowActive;
    GLFWwindow * _windowInstance;
    GLFWmonitor ** _pMonitor;
    int _monitorCount;
    int _screenX;
    int _screenY;
    // keys & mouse
    bool _keys[MAX_KEYS];
    bool _mouseButtons[MAX_BUTTONS];
    double _mouseX,_mouseY;
};


#endif