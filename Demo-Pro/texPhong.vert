#version 460 core

//输入
layout (location = 0) in vec3 aPos;         //位置
layout (location = 2) in vec2 aTexCoord;    //纹理坐标
layout (location = 3) in vec3 aNormal;      //法线

//输出
out vec3 worldPos;
out vec3 normal;
out vec2 texCoord;

//矩阵
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    worldPos = vec3(model * vec4(aPos, 1.0));

    normal = transpose(inverse(mat3(model))) * aNormal;

    texCoord = aTexCoord;

    gl_Position = projection * view * vec4(worldPos, 1.0);
}
