#include "camera.h"

Camera::Camera(Window * window):
    _deltaTime(0.0f),
    _yaw(-90.0f),
    _pitch(0.0f),
    _pfov(DEFAULT_CAMERA_PFOV),
    _pnear(DEFAULT_CAMERA_PNEAR),
    _pfar(DEFAULT_CAMERA_PFAR),
    _cameraSpeed(DEFAULT_CAMERA_SPEED),
    _sensitivity(DEFAULT_CAMERA_SENSITIVITY)
{
    // window
    this->_window = window;
    // 长宽比例
    GLfloat width = this->_window->getWindowSize().windowWidth;
    GLfloat height = this->_window->getWindowSize().windowHeight;    
    this->_pratio = width/height;
    // camera参数
    this->_cameraPos = glm::vec3(0,0,0);
    this->_cameraFront = glm::vec3(0,0,0);
    this->_cameraUp = glm::vec3(0,1,0);
}
void Camera::cameraUpdate()
{
    // 窗口比例改变对应透视投影比例改变
    this->frameSizeChangeCallback();
    // 获取每帧间隔时间
    this->_deltaTime = this->_window->getDeltaTime();
    // 窗口键盘事件响应
    this->keyCallback();
    // 光标位置响应
    this->cursorCallback();
    // 鼠标点击事件响应
    this->mouseButtonCallback();
    // 更新view和prospective矩阵
    this->_viewMatrix = glm::lookAt(
        getGlobalCamPos(),
        getGlobalCamTarget(),
        getGlobalUpVector());
    this->_projectionMatrix = glm::perspective(
        this->_pfov,
        this->_pratio,
        this->_pnear,
        this->_pfar
    );
}
void Camera::keyCallback()
{
    GLfloat distance = this->_cameraSpeed * this->_deltaTime;
    if (this->_window->getKeys(GLFW_KEY_W))
        moveForward(distance);
    if (this->_window->getKeys(GLFW_KEY_S))
        moveBackward(distance);
    if (this->_window->getKeys(GLFW_KEY_A))
        moveLeft(distance);
    if (this->_window->getKeys(GLFW_KEY_D))
        moveRight(distance);
}
void Camera::cursorCallback()
{
    GLfloat offsetX,offsetY;
    offsetX = this->_window->cursorOffsetX * this->_sensitivity;
    offsetY = this->_window->cursorOffsetY * this->_sensitivity;
    this->_yaw += offsetX;
    this->_pitch += offsetY;
    this->rotate();
}
void Camera::mouseButtonCallback()
{

}
void Camera::frameSizeChangeCallback()
{
    GLfloat width = this->_window->getWindowSize().windowWidth;
    GLfloat height = this->_window->getWindowSize().windowHeight;    
    this->_pratio = width/height;
}