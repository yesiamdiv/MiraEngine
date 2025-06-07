#include <Graphics/Renderer.h>
#include <Utils/AssetPath.h>
#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <iostream>
#include <fstream>

namespace Mira
{
    namespace Graphics
    {
        Renderer::Renderer()
        {
        }

        Renderer::~Renderer()
        {
        }

        bool Renderer::Init(int width, int height, Backend::Window* window)
        {
            this->window = window;
            windowWidth = width;
            windowHeight = height;

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            
            glViewport(0, 0, width, height);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            Clear();

            Present();

            CreateGraphicsPipeline();

            // std::cout<<"Renderer Initialized\n";

            return true;
        }

        void Renderer::Clear()
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            glClear(GL_COLOR_BUFFER_BIT);
        }

        void Renderer::Present()
        {
            SDL_GL_SwapWindow(window->GetSDLWindow());
        }

        // Update this method to remove the shaderType parameter
        void Renderer::AddShaderProgram(std::string shaderName, std::string vertexShaderPath, std::string fragmentShaderPath)
        {
            this->shaderSources[shaderName] = ShaderSource{vertexShaderPath, fragmentShaderPath};
        }


        void Renderer::SetProjectionMatrix(glm::mat4 projectionMatrix)
        {
            // im setting the projection matrix here because i want to be able to change the projection matrix at any time and the program uses this by default

            this->projectionMatrix = projectionMatrix;
            this->projectionUniformLocation = GetUniformLocation(currentShaderProgram, "projection");

            // I do this to ensure that the projection matrix is updated when the projection matrix is changed, which is only changed here, probably
            SetUniformMatrix4fv(currentShaderProgram, "projection", projectionMatrix);
        }   

        // Private Functions

        void Renderer::CreateGraphicsPipeline()
        {
            std::string shaderName = "default_shader_program";

            AddShaderProgram(shaderName, GET_ASSET_PATH("Shaders/VertexShader.glsl"), GET_ASSET_PATH("Shaders/FragmentShader.glsl"));

            ShaderProgram shaderProgram = CreateShaderProgram(shaderName);

            shaderPrograms[shaderName] = shaderProgram;

            currentShaderProgram = shaderProgram.shaderProgram;

            currentVertexShader = shaderProgram.vertexShader;

            currentFragmentShader = shaderProgram.fragmentShader;

            glm::mat4 projectionMatrix = glm::ortho(0.0f, (float) windowWidth, (float)windowHeight , 0.0f, -1.0f, 1.0f);

            SetProjectionMatrix(projectionMatrix);

            glUseProgram(currentShaderProgram);

        }

        // Create Shader Program
        ShaderProgram Renderer::CreateShaderProgram(std::string shaderName)
        {
            GLuint shaderProgram = glCreateProgram(); // Initialize shader program
            GLuint vertexShader {0};
            GLuint fragmentShader {0};

            auto shaderSource = shaderSources[shaderName];

            vertexShader = CompileShader(LoadShaderAsString(shaderSource.vertexSource),GL_VERTEX_SHADER);
            fragmentShader = CompileShader(LoadShaderAsString(shaderSource.fragmentSource),GL_FRAGMENT_SHADER);

            glAttachShader(shaderProgram, vertexShader);

            glAttachShader(shaderProgram, fragmentShader);

            glLinkProgram(shaderProgram);

            glValidateProgram(shaderProgram);
            // TODO: Delete shaders after they are attached to the shader program and linked to the shader program

            return ShaderProgram{vertexShader, fragmentShader, shaderProgram};
        }

        // Compiles shader
        GLuint Renderer::CompileShader(std::string shaderSourceCode, GLenum shaderType)
        {
            GLuint shader {0};

            shader = glCreateShader(shaderType);
            
            const char* code =  shaderSourceCode.c_str();

            glShaderSource( shader, 1, &code, NULL);

            glCompileShader(shader);

            // Error checking

            int result;

            glGetShaderiv(shader,GL_COMPILE_STATUS, &result);

            if(result==GL_FALSE)
            {
                int length;
                glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&length);
                char* errorMessage = new char[length];
                glGetShaderInfoLog(shader,length,&length,errorMessage);

                if(shaderType == GL_VERTEX_SHADER)
                    std::cout<<"ERROR: GL_VERTEX_SHADER compilation failed!\n"<<errorMessage <<"\n";
                else if(shaderType == GL_FRAGMENT_SHADER)
                    std::cout<<"ERROR: GL_FRAGMENT_SHADER compilation failed!\n"<<errorMessage <<"\n";

                delete[] errorMessage;

                glDeleteShader(shader);
                return 0;
            }


            return shader;

        }

        // Gets the shader program from the file as a string
        std::string Renderer::LoadShaderAsString(std::string filePath)
        {
            std::string shaderSourceCode;
            std::ifstream shaderFile(filePath);

            if(shaderFile.is_open())
            {
                std::string line;
                while(std::getline(shaderFile,line))
                {
                    shaderSourceCode += line + "\n";
                }

                shaderFile.close();
            }
            return shaderSourceCode;
        }

        GLuint Renderer::GetUniformLocation(GLuint shaderProgram, std::string uniformName)
        {
            return glGetUniformLocation(shaderProgram, uniformName.c_str());
        }

        void Renderer::SetUniformMatrix4fv(GLuint shaderProgram, std::string uniformName, glm::mat4 matrix)
        {
            GLuint uniformLocation = GetUniformLocation(shaderProgram, uniformName);
            glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]);
        }

    }
}