#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Backend/Window.h>


namespace Mira
{
    namespace Graphics
    {
        struct ShaderSource
        {
            std::string vertexSource;
            std::string fragmentSource;
            // Removed shaderType as it's not being used
        };

        struct ShaderProgram
        {
            GLuint vertexShader {0};
            GLuint fragmentShader {0};
            GLuint shaderProgram {0};
        };

        class Renderer
        {
        public:
            Renderer();
            ~Renderer();

            //Initializes the renderer
            bool Init(int width, int height, Backend::Window* window);

            //Clears the screen to the given color
            void Clear();

            //Swaps the back buffer with the front buffer
            void Present(); 

            // Updated method signature - removed shaderType parameter
            void AddShaderProgram(std::string shaderName, std::string vertexShaderPath, std::string fragmentShaderPath);

            // Sets the projection matrix for the current shader program
            void SetProjectionMatrix(glm::mat4 projectionMatrix);


        private:
            // Creates graphics pipeline
            void CreateGraphicsPipeline();

            // Create Shader Program
            ShaderProgram CreateShaderProgram(std::string shaderName);

            // // Compiles all the shaders
            // void CompileAllShaders();

            // Compiles shader
            GLuint CompileShader(std::string shaderSourceCode, GLenum shaderType);

            // Gets the shader program from the file as a string 
            std::string LoadShaderAsString(std::string filePath);

            // Gets the uniform location
            GLuint GetUniformLocation(GLuint shaderProgram, std::string uniformName);

            // Sets the uniform matrix 4fv
            void SetUniformMatrix4fv(GLuint shaderProgram, std::string uniformName, glm::mat4 matrix);

        private:
            int windowWidth {0};
            int windowHeight {0};
            Backend::Window* window {nullptr};

            GLuint currentShaderProgram {0};
            GLuint currentVertexShader {0};
            GLuint currentFragmentShader {0};

            glm::mat4 projectionMatrix;
            GLuint projectionUniformLocation; 

            std::unordered_map<std::string, ShaderProgram> shaderPrograms;
            std::unordered_map<std::string, ShaderSource> shaderSources;

            GLuint VAO {0};
            GLuint VBO {0};
            GLuint EBO {0};
        };
    }
}