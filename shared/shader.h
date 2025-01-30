#ifndef OPENGL_LEARN_SHADER_H
#define OPENGL_LEARN_SHADER_H

unsigned int createShader( const char* shaderSource, int shaderType );
bool checkProgramLinkingSuccess( unsigned int program );

#endif //OPENGL_LEARN_SHADER_H
