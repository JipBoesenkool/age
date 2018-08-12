#shader vertex
#version 330 core
layout (std140) uniform Matrices
{
    mat4 uProjection;
    mat4 uView;
};

layout(location = 0) in vec3 position;

uniform vec3 uPosition;
uniform mat4 uModelMatrix;
void main()
{
    gl_Position = uProjection * uView * uModelMatrix * vec4(position, 1.0);
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
uniform vec4 uColor;
void main()
{
    color = uColor;
}

