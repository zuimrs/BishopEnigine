#include "window.h"
#include <iostream>
using namespace std;

Window::Window(
		const bool fullscreen,
        const string title,
        const GLfloat width,
        const GLfloat height)
{
#ifdef DEBUG
	cout << "Begin Window()" << endl;
	cout << endl;
#endif
	// 初始化opengl库
	glfwFunctionInit();
	// 初始化是否全屏
	this-> _isFullScreen = fullscreen;
	// 初始化窗口信息
	this->_windowSize.windowHeight = height;
	this->_windowSize.windowWidth = width;
	this->_windowTitle = title;
	// 重置键盘数组
	for(int i = 0 ; i < MAX_KEYS; ++i)
	{
		this->_keys[i] = false;
	}
	for(int i = 0 ; i < MAX_BUTTONS; ++i)
	{
		this->_mouseButtons[i] = false;
	}
	// 初始化当前屏幕指针数组
	this-> _pMonitor = glfwGetMonitors(&this->_monitorCount);
	GLFWmonitor * pMonitor = this->_pMonitor[0];
	// 初始化屏幕分辨率
	const GLFWvidmode * mode = glfwGetVideoMode(pMonitor);	
	this->_screenX = mode->width;
	this->_screenY = mode->height;
	// 激活窗口
	this->_isWindowActive = true;

	// 初始化窗口
	initializeWindow();

#ifdef DEBUG
	cout << "End Window()" <<endl;
	cout << endl;
#endif
}

void Window::initializeWindow()
{
	GLFWmonitor * pMonitor = this->_isFullScreen ? this->_pMonitor[0]: NULL;
	GLfloat width = this->_isFullScreen ? this->_screenX : getWindowSize().windowWidth;
	GLfloat height = this->_isFullScreen ? this->_screenY : getWindowSize().windowHeight;
	
	this->_windowInstance = 
			glfwCreateWindow(width,height,getWindowTitle().c_str(),pMonitor,NULL);	

	// 创建失败
#ifndef _EXCEPTION_H_
	if(!this->_windowInstance)
	{
		cout << "Failed in initialize window instance in Function Window::Window()" << endl;
		return;
	}
#endif
	// 当前窗口
	glfwMakeContextCurrent(this->_windowInstance);
	// 创建用户指针
	glfwSetWindowUserPointer(this->_windowInstance,this);
	// 键盘回调函数
	glfwSetKeyCallback(this->_windowInstance, key_callback);
	// 鼠标回调函数
	glfwSetMouseButtonCallback(this->_windowInstance,mouse_button_callback);
	glfwSetCursorPosCallback(this->_windowInstance,cursor_position_callback);
	glfwSetInputMode(this->_windowInstance,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
	// 初始化glew
	glewExperimental = GL_TRUE;
	GLenum glewinit = glewInit();
	if (glewinit != GLEW_OK) 
	{
#ifndef _EXCEPTION_H_
		cout << "Glew not okay! " << glewinit;
#endif
	}

	// resize callback
	windowDisplayModeChangeCallback(width,height);
	
#ifdef DEBUG
	cout << "initializeWindow() done" << endl;
#endif

}


void Window::glfwFunctionInit()
{
#ifndef _EXCEPTION_H_
	if(!glfwInit())
	{
		cout << "Failed to initialize GLFW " << endl;
	}
#endif
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}
void Window::setWindowSize(const GLfloat width,const GLfloat height)
{
    this->_windowSize.windowHeight = height;
    this->_windowSize.windowWidth = width;
    glfwSetWindowSize(this->_windowInstance,width,height);
    windowDisplayModeChangeCallback(width,height);

}

void Window::setWindowPos(const GLfloat posX,const GLfloat posY,const bool fullScreen)
{
    if(fullScreen == true)
    {
        // add fullscreen operations
        return;
    }
    this->_windowPos.windowPosX = posX;
    this->_windowPos.windowPosY = posY;
    glfwSetWindowPos(this->_windowInstance,posX,posY);
}
void Window::windowMainLoop()
{

	// on start
	this->startFunctionCallback();

    do{
		// glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		// update on every loop
		this->updateFunctionCallback();

		glfwPollEvents();
		glfwSwapBuffers(this->_windowInstance);
		//glfwWaitEventsTimeout(1.0/DEFAULT_WINDOW_FRAME_PER_SECOND);
	} while(glfwWindowShouldClose(this->_windowInstance) == 0 );
	glfwTerminate();
}

void Window::onStartFunctionCallback(void(*pF)(void) )
{
    this->_startFunctionSequence.push_back(pF);
#ifdef DEBUG
	cout << "Add an Start function to mainloop" << endl;
#endif
}
void Window::onUpdateFunctionCallback(void(*pF)(void) )
{
    this->_updateFunctionSequence.push_back(pF);
#ifdef DEBUG
	cout << "Add an Update function to mainloop" << endl;
#endif
}
void Window::startFunctionCallback()
{
	for(int i = 0 ; i < this->_startFunctionSequence.size(); i++)
	{
		this->_startFunctionSequence[i]();
	}
}
void Window::updateFunctionCallback()
{
	for(int i = 0 ; i < this->_updateFunctionSequence.size();i++)
	{
		this->_updateFunctionSequence[i]();
	}
}
void Window::showWindow()
{
	// 主循环开始
	windowMainLoop();
}

void Window::changeDisplayMode()
{
	if(this->_isWindowActive == false)
		return;
	if(this->_isFullScreen == true)
		this->_isFullScreen = false;
	else
		this->_isFullScreen = true;
	// 销毁原窗口
	glfwDestroyWindow(this->_windowInstance);

#ifdef DEBUG
	cout << "old window destroyed" << endl;
#endif

	// 创建新窗口
	initializeWindow();

#ifdef DEBUG
	cout << "new window created" << endl;
#endif
}
void Window::windowDisplayModeChangeCallback(const GLfloat width,const GLfloat height)
{
    // 设置视口为窗口的大小
    glViewport(0, 0, width, height);
	
#ifdef DEBUG
		cout << "windowDisplayModeChangeCallback() done" <<endl;
#endif
}

void Window::windowMinisizeCallback()
{
	if(this->_isWindowActive == false)
		return;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Window * win = (Window *) glfwGetWindowUserPointer(window);

#ifdef DEBUG
	cout <<"key:" << key <<" is pressed!" << endl;
#endif

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
		win->_keys[key] = action != GLFW_RELEASE;
    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
	Window * win = (Window *) glfwGetWindowUserPointer(window);
#ifdef DEBUG
	cout <<"mousebutton:" << button <<" is pressed at ";
	cout <<"("<<win->cursorX<<","<<win->cursorY<<")"<<endl;
#endif
	win->_mouseButtons[button] = action != GLFW_RELEASE;
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Window * win = (Window *) glfwGetWindowUserPointer(window);
	win->cursorOffsetX = xpos - win->cursorX;
	win->cursorOffsetY = win->cursorY - ypos;
	win->cursorX = xpos;
	win->cursorY = ypos;	
}