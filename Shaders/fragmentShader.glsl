#version 330 core
in vec2 TexCoord;

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float transition;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform bool isLight;
uniform vec3 lightPos;

uniform vec3 viewPos;

struct Material
{
    sampler2D diffuse1;
    sampler2D diffuse2;
    sampler2D diffuse3;
    
    sampler2D specular1;
    sampler2D specular2;
    sampler2D specular3;

    sampler2D normal1;
    sampler2D normal2;
    sampler2D normal3;
    float shine;
};

struct Light
{
    vec4 lightVec4; // pos & direction
    vec3 ambient;
    vec3 direction;
    vec3 diffuse;
    vec3 specular;

    // flashlight
    float cutOff;

    // attenuation
    float constant;
    float linear;
    float quadratic;
};

struct DirLight
{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;


    float constant;
    float linear;
    float quadratic;
};


struct SpotLight
{
    vec3 pos;
    vec3 lightDir;
    vec3 spotDir;
    float cutOff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

#define NR_SPOT_LIGHTS 8
#define NR_POINT_LIGHTS 1

uniform SpotLight spotLights[NR_SPOT_LIGHTS];
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirlight;

vec3 DirectionalLighter(DirLight light, vec3 normal, vec3 viewDir);
vec3 PointLighter(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 SpotLighter(SpotLight light, vec3 normal, vec3 viewDir);

uniform Material material;
uniform Light light;

void main()
{
    if (isLight)
    {
        FragColor = vec4(1.0);
    }
    else
    {
        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(viewPos - FragPos);

        vec3 result = DirectionalLighter(dirlight, norm, viewDir); //working




        for (int i = 0; i < NR_POINT_LIGHTS; i++)
        {
            result += PointLighter(pointLights[i], norm, FragPos, viewDir); //works
        }
        for (int i = 0; i < NR_SPOT_LIGHTS; i++)
        {
        }
        result += SpotLighter(spotLights[0], norm, viewDir); // working
        
        //vec3 debugcolor = vec3(0.0, 1.0, 0.0);

        vec3 debugtexture = vec3(texture(material.diffuse1, TexCoord));

        FragColor = vec4(debugtexture, 1.0);

        //FragColor = vec4(TexCoord, 0.0, 1.0);
    }
}

// Function definitions must be placed outside of main

vec3 DirectionalLighter(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse1, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse1, TexCoord));
    
    vec3 specular = light.specular * spec * vec3(texture(material.specular1, TexCoord));
    return (ambient + diffuse + specular);
}

vec3 PointLighter(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectionDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectionDir), 0.0), material.shine);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * vec3(texture(material.diffuse1, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse1, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular1, TexCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 SpotLighter(SpotLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.pos - FragPos);
    float theta = dot(lightDir, normalize(-light.lightDir));

    if (theta > light.cutOff)
    {
        vec3 ambient = light.ambient * texture(material.diffuse1, TexCoord).rgb;

        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * texture(material.diffuse1, TexCoord).rgb;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
        vec3 specular = light.specular * spec * texture(material.specular1, TexCoord).rgb;

        float distance = length(light.pos - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        diffuse *= attenuation;
        specular *= attenuation;

        return (ambient + diffuse + specular);
    }
    else
    {
        return light.ambient * texture(material.diffuse1, TexCoord).rgb;
    }
}