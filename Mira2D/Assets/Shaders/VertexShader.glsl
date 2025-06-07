#version 330 core
layout (location = 0) in vec3 aPos;  // Vertex position
layout (location = 1) in vec2 aTexCoord; // Texture coordinates

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 model;      

void main()
{
    // The vertex position is transformed by the projection and model matrices
    gl_Position = projection * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}