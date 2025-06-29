#version 410 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 texCoor;
//layout (location = 2) in vec4 colorCoor;

out vec2 u_TexCoord;
//out vec4 v_ColorCoord;
uniform mat4 u_MVP;
void main()
{
   // gl_Position = vec4(aPos, 0.0, 1.0);
   gl_Position = u_MVP * vec4(aPos, 0.0f, 1.0f);
   u_TexCoord = texCoor;
   //v_ColorCoord = colorCoor;
}