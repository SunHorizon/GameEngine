#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

out vec4 color;

 struct Light
 {
 	vec3 lighPostion;
 	float ambient;
 	float diffuse;
 	vec3 lightColor;
 };

  struct Material
 {
	sampler2D diffuceMap;
	float shininess; //NS
	float transparency; //D

	vec3 ambient; //Ka
	vec3 diffuse; //Kd
	vec3 specular; //Ks
 };


uniform Material material;

uniform vec3 CameraPosition;
uniform Light light;

void main()
{
	color = texture(material.diffuceMap, TexCoords);
	
	vec3 ambient = light.ambient * material.ambient * texture(material.diffuceMap, TexCoords).rgb * light.lightColor;

	vec3 norm = normalize(Normal);
	vec3 lighDir = normalize(light.lighPostion - FragPosition);
	float diff = max(dot(norm, lighDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuceMap, TexCoords).rgb * light.lightColor;


    float specularStrength = 0.5;
	vec3 viewDir = normalize(CameraPosition - FragPosition);
	vec3 reflectDir = reflect(-lighDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * light.lightColor;

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);

}
