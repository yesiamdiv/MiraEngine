#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0); // Default white color for tinting

void main()
{
    // Sample the texture at the current texture coordinate
    vec4 texColor = texture(texture1, TexCoord);
    
    // Apply the color tint
    FragColor = texColor * color;
}
