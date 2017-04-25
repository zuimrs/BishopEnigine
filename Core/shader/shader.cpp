#include "shader.h"
#include "const.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string Shader::readFile(const char * filePath)
{
	string content;
	ifstream fileStream(filePath);

	if(!fileStream.is_open())
	{

#ifndef _EXCEPTION_H_
		cout << "Failed to read " << filePath << ". File does not exist." << endl;
#endif
		return "";
	}


	string line = "";
	while(!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::loadShader(const char * vertex_path,const char * fragment_path)
{
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Read shaders
    string vertShaderStr = ReadFile(vertex_path);
    string fragShaderStr = ReadFile(fragment_path);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // Compile vertex shader
#ifdef DEBUG
    cout << "Compiling vertex shader." << endl;
#endif
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    // Check vertex shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
#ifdef DEBUG
	cout << &vertShaderError[0] << endl;
#endif
    // Compile fragment shader
#ifdef DEBUG
    cout << "Compiling fragment shader." << endl;
#endif
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    // Check fragment shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    vector<GLchar> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
#ifdef DEBUG
	cout << &fragShaderError[0] << endl;
#endif

#ifdef DEBUG
    cout << "Linking program" << endl;
#endif
	GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    vector<char> programError( (logLength > 1) ? logLength : 1 );
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
#ifdef DEBUG
	cout << &programError[0] << endl;
#endif
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}