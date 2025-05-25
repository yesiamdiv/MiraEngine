#pragma once

#include <string>
#include <glm.hpp>
//#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Mira
{   
    namespace Graphics
    {
        
        class MEShader {
        public:
            MEShader(const std::string& vertexSrc, const std::string& fragmentSrc);
            ~MEShader();
        
            void bind() const;
            void unbind() const;
        
            // Uniform setters
            void setInt(const std::string& name, int value) const;
            void setFloat(const std::string& name, float value) const;
            void setVec4(const std::string& name, const glm::vec4& value) const;
            void setMat4(const std::string& name, const glm::mat4& value) const;
        
            GLuint getID() const { return programID; }
        
        private:
            GLuint programID;
        
            GLint getUniformLocation(const std::string& name) const;
            GLuint compileShader(GLenum type, const std::string& source);
        };
    }
}