#include <Graphics/MEShader.h>
#include <iostream>
namespace Mira
{
    
    namespace Graphics
    {
        
        
        MEShader::MEShader(const std::string& vertexSrc, const std::string& fragmentSrc) {
            GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
            GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);
        
            programID = glCreateProgram();
            glAttachShader(programID, vertexShader);
            glAttachShader(programID, fragmentShader);
            glLinkProgram(programID);
        
            GLint success;
            glGetProgramiv(programID, GL_LINK_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetProgramInfoLog(programID, 512, nullptr, infoLog);
                std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            }
        
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }
        
        MEShader::~MEShader() {
            glDeleteProgram(programID);
        }
        
        void MEShader::bind() const {
            glUseProgram(programID);
        }
        
        void MEShader::unbind() const {
            glUseProgram(0);
        }
        
        void MEShader::setInt(const std::string& name, int value) const {
            glUniform1i(getUniformLocation(name), value);
        }
        
        void MEShader::setFloat(const std::string& name, float value) const {
            glUniform1f(getUniformLocation(name), value);
        }
        
        void MEShader::setVec4(const std::string& name, const glm::vec4& value) const {
            glUniform4fv(getUniformLocation(name), 1, &value[0]);
        }
        
        void MEShader::setMat4(const std::string& name, const glm::mat4& value) const {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
        }
        
        GLint MEShader::getUniformLocation(const std::string& name) const {
            return glGetUniformLocation(programID, name.c_str());
        }
        
        GLuint MEShader::compileShader(GLenum type, const std::string& source) {
            GLuint shader = glCreateShader(type);
            const char* src = source.c_str();
            glShaderSource(shader, 1, &src, nullptr);
            glCompileShader(shader);
        
            GLint success;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetShaderInfoLog(shader, 512, nullptr, infoLog);
                std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            return shader;
        }
    } 
}