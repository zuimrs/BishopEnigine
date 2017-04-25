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
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
class WindowSize
{
public:
    GLfloat windowHeight;
    GLfloat windowWidth;
};
class WindowPos
{
public:
    GLfloat windowPosX;
    GLfloat windowPosY;
};

class Window
{
// public methods
public:
    Window(
        const bool fullscreen = DEFAULT_WINDOW_FULL_SCREEN,
        const string title = DEFAULT_WINDOW_TITLE,
        const GLfloat width = DEFAULT_WINDOW_WIDTH,
        const GLfloat height = DEFAULT_WINDOW_HEIGHT);
    ~Window();

    // get
    GLFWwindow * getWindowInstance(){return this->_windowInstance;};
    WindowSize getWindowSize(){return this->_windowSize;};
    WindowPos getWindowPos(){return this->_windowPos;}
    string getWindowTitle(){return this->_windowTitle;}
    bool getWindowActive(){return this->_isWindowActive;}
    bool getKeys(int index)
    {
        if(index >=0 && index <MAX_KEYS)
            return this->_keys[index];
        return false;
    }
    GLfloat getDeltaTime(){return this->_deltaTime;}
    // set
    void setWindowTitle(const string title){glfwSetWindowTitle(this->_windowInstance,title.c_str());}
    void setWindowSize(const GLfloat width,const GLfloat height);
    void setWindowPos(
        const GLfloat posX = DEFAULT_WINDOW_POSX,
        const GLfloat posY = DEFAULT_WINDOW_POSY,
        const bool fullScreen = DEFAULT_WINDOW_FULL_SCREEN);
    void setWindowCursorPos(double x,double y)
    {
        glfwSetCursorPos(this->_windowInstance,x,y);
    }
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
    void windowDisplayModeChangeCallback(const GLfloat,const GLfloat);
    void startFunctionCallback();
    void updateFunctionCallback();


    // key & mouse
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
    friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    void resetCursorOffset(){this->cursorOffsetX = 0.0f;this->cursorOffsetY = 0.0f;}
// private attributes
private:
    GLFWwindow * _windowInstance;
    GLFWmonitor ** _pMonitor;
    vector<void(*)(void)> _startFunctionSequence, _updateFunctionSequence;
    string _windowTitle; WindowSize _windowSize; WindowPos _windowPos;
    bool _isFullScreen,_isWindowActive;
    int _monitorCount;
    int _screenX,_screenY;
    // frame time
    GLfloat _deltaTime;
    GLfloat _lastFrame;
    // keys & mouse
    bool _keys[MAX_KEYS];
    bool _mouseButtons[MAX_BUTTONS];

public:
    GLfloat cursorX,cursorY;
    GLfloat cursorOffsetX,cursorOffsetY;
    
};


#endif