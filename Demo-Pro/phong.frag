#version 460 core

#define MAX_LIGHTS 7	//光源上限，编译期常量

in vec3 worldPos;
in vec3 normal;

out vec4 FragColor;

//材质
struct Material 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

//光源
struct Light 
{
	vec3 position;
	vec3 color;
	float strength;
};

uniform Material material;
uniform Light lights[MAX_LIGHTS];
uniform int lightCount;
uniform vec3 viewPos;

void main()
{
	vec3 N = normalize(normal);
	vec3 V = normalize(viewPos - worldPos);

	vec3 diffuseSum  = vec3(0.0);
	vec3 specularSum = vec3(0.0);

	//环境光取所有光源的平均颜色
	vec3 avgColor = vec3(0.0);
	for (int i = 0; i < lightCount; i++)
	{
		avgColor += lights[i].color;
	}
	if (lightCount > 0)
	{
		avgColor /= float(lightCount);
	}

	vec3 ambientTotal = material.ambient * avgColor;

	//遍历所有光源，累加漫反射和镜面反射
	for (int i = 0; i < lightCount; i++)
	{
		vec3 L = normalize(lights[i].position - worldPos);
		vec3 H = normalize(L + V);

		//漫反射
		float diff = max(dot(N, L), 0.0);
		diffuseSum += material.diffuse * diff * lights[i].color * lights[i].strength;

		//镜面反射
		float spec = pow(max(dot(N, H), 0.0), material.shininess);
		specularSum += material.specular * spec * lights[i].color * lights[i].strength;
	}

	FragColor = vec4(ambientTotal + diffuseSum + specularSum, 1.0);
}