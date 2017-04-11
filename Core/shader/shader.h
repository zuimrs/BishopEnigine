#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>
#include <string>
std::string ReadFile(const char *);
GLuint LoadShader(const char *,const char *);


#endif