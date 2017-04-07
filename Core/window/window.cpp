#include "window.h"
#include <iostream>
using namespace std;
bool Window::glFuncInit()
{
    return glfwInit()&&glewInit();
}

Window::Window(
        const string title,
        const int width,
        const int height)
{
    if(!glFuncInit())
    {
        #ifndef _EXCEPTION_H_
        cout << "glfw init failure" << endl;
        #else

        #endif
        
        return;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->_windowInstance = glfwCreateWindow(width,height,title.c_str(),NULL,NULL);
    glfwMakeContextCurrent(this->_windowInstance);
    this->setWindowTitle(title);
    this->setWindowSize(width,height);
    this->windowMainLoop();
}

void Window::setWindowSize(const int width,const int height)
{
    this->_windowSize.height = height;
    this->_windowSize.width = width;
    glfwSetWindowSize(this->_windowInstance,width,height);
}

void Window::setWindowPos(const int posX,const int posY,const bool fullScreen)
{
    if(fullScreen == true)
    {
        // add fullscreen operations
        return;
    }
    this->_windowPos.window_posX = posX;
    this->_windowPos.window_posY = posY;
    glfwSetWindowPos(this->_windowInstance,posX,posY);
}
void Window::windowMainLoop()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    do{
        for(int i = 0 ; i < this->_windowFuncSequence.size(); i++)
        {
            this->_windowFuncSequence[i]();
        }

		glfwSwapBuffers(this->_windowInstance);
		glfwWaitEventsTimeout(1.0/30.0);
	} while(glfwGetKey(this->_windowInstance, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(this->_windowInstance) == 0 );
	glfwTerminate();
}

void Window::pushFunctionCallback(void(*pF)(void) )
{
    this->_windowFuncSequence.push_back(pF);
}

