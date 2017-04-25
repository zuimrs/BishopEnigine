#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>
#include <string>
class Shader
{
public:
    Shader(const char * vertex_path,const char * fragment_path)
    {
        this->_programID = loadShader(vertex_path,fragment_path);
    }
    void useShader(){glUseProgram(this->_programID);}
    GLuint getProgramID(){return this->_programID;}
private:
    std::string readFile(const char *);
    GLuint loadShader(const char *,const char *);
private:
    GLuint _programID;
};


#endif