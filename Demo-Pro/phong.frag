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
	int type;
	vec3 position;
	vec3 color;
	float strength;
	vec3 dir;
	float cutOff;
	float cutOffRatio;
	float quadratic;
	float linear;
	float constant;
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
		vec3 L;
		float atten;
		if(lights[i].type == 0)
		{
			L = normalize(-lights[i].dir);	//方向光的光照向量与位置无关
			atten = 1.0f;
		}
		else if(lights[i].type == 1)
		{
			L = normalize(lights[i].position - worldPos);
			float distance = length(lights[i].position - worldPos);
			//点光源的衰减系数
			atten = 1 / (lights[i].quadratic * pow(distance, 2.0f) + lights[i].linear * distance + lights[i].constant);
		}
		else if(lights[i].type == 2)
		{
			L = normalize(lights[i].position - worldPos);
			float distance = length(lights[i].position - worldPos);
			float outCut = radians(lights[i].cutOff);		//外切光弧度
			float inCut = lights[i].cutOffRatio * outCut;	//内切光弧度
			float angle = acos(dot(normalize(worldPos - lights[i].position), normalize(lights[i].dir)));	//实际弧度
			if(angle <= inCut)
			{
				atten = 1 / (lights[i].quadratic * pow(distance, 2.0f) + lights[i].linear * distance + lights[i].constant);
			}
			else if(angle <= outCut)
			{
				atten = 1 / (lights[i].quadratic * pow(distance, 2.0f) + lights[i].linear * distance + lights[i].constant);
				atten *= smoothstep(cos(outCut), cos(inCut), cos(angle));
			}
			else if(angle > outCut)
			{
				atten = 0.0f;
			}
		}

		vec3 H = normalize(L + V);

		//漫反射
		float diff = max(dot(N, L), 0.0);
		diffuseSum += material.diffuse * diff * lights[i].color * lights[i].strength * atten;

		//镜面反射
		float spec = pow(max(dot(N, H), 0.0), material.shininess);
		specularSum += material.specular * spec * lights[i].color * lights[i].strength * atten;
	}

	FragColor = vec4(ambientTotal + diffuseSum + specularSum, 1.0);
}