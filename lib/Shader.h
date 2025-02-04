#ifndef OL_SHADER_H
#define OL_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

public:
    unsigned int id;

    Shader( const char* vertexPath, const char* fragmentPath );

    void use() const;

    void setBool( const std::string &name, bool value ) const;
    void setInt( const std::string &name, int value ) const;
    void setFloat( const std::string &name, float value ) const;
};


#endif //OL_SHADER_H