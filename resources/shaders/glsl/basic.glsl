#shader vertex
#version 330 core
layout(location = 0) in vec2 position;
void main()
{
    gl_Position = vec4(position, 1.0f, 1.0f);
}


#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
uniform vec4 uColor;
void main()
{
    color = uColor;
}
