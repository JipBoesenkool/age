#shader vertex
#version 330 core
layout(location = 0) in vec3 position;

uniform vec3 uPosition;
void main()
{
    gl_Position = vec4(uPosition * position, 1.0f);
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
uniform vec4 uColor;
void main()
{
    color = uColor;
}

