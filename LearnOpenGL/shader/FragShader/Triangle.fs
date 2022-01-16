#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec4 ourPos;
in vec2 TexCoord;
in float lerp;

uniform sampler2D Texture1;
uniform sampler2D Texture2;


//*vec4(ourPos.x+0.5,ourPos.y+0.5,ourPos.z+0.5, 1.0)

void main()
{
    FragColor = mix(texture(Texture1, TexCoord),texture(Texture2, vec2(1-TexCoord.x,TexCoord.y)),lerp);
}