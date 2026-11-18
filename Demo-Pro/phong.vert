#version 460 core

// ‰»Î
layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aNormal;

// ‰≥ˆ
out vec3 worldPos;
out vec3 normal;

//æÿ’Û
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    worldPos = vec3(model * vec4(aPos, 1.0f));
    normal = transpose(inverse(mat3(model))) * aNormal;

    gl_Position = projection * view * vec4(worldPos, 1.0);
}