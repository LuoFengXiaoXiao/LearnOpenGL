#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec4 ourPos;
out vec2 TexCoord;
out float lerp;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);

uniform float xOffset;

void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, -aPos.y, aPos.z, 1.0); // add the xOffset to the x position of the vertex position
    lerp = xOffset;
    ourColor = aColor;
    TexCoord = aTexCoord;
}