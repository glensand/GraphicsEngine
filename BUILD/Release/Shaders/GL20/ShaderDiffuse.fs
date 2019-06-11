#version 330 core

struct Light
{
	vec4	type;		// тип источника
	vec4	position;	// позиция источника (есть у Point и Spot)
	vec4	direction;	// направление света
	vec4	color;		// (цвет.r, цвет.g, цвет.b, интенсивность)
};

// Shader parameters
uniform mat4 matWorldNormal;
uniform mat4 matWorldT;
uniform vec4 materialColor;
uniform vec4 lightsCount;
uniform vec4 cameraPos;
uniform Light lights[3];

varying vec3 localPosition;
varying vec3 localNormal;


vec3 calcDiffuse(vec4 lightCol, vec3 lightDir, vec3 vertexNormal)
{
	float diffuse = clamp( dot(-lightDir, vertexNormal), 0.0, 1.0 );

	// Цвет = diffuse * (цвет источника) * (интенсивность источника)
	vec3 color = diffuse * lightCol.rgb * lightCol.a;

	return color;
}

vec3 calcSpecular(vec4 lightCol, vec3 lightDir, vec3 vertexNormal, vec3 viewDir)
{
	float specularStrength = 1.0f;
	vec3 reflectDir = reflect(lightDir, vertexNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 200);
	vec3 specular = specularStrength * spec * lightCol.xyz * lightCol.a;

	return specular;
}

void main()
{
	vec3 col = vec3(0,0,0);

	// Переводим нормаль из локальной в глобальную систему координат
	vec3 vertexNormal = (vec4(localNormal, 0.0) * matWorldNormal).xyz;
	vertexNormal = normalize(vertexNormal);
	// Переводим позицию из локальной в глобальную систему координат
	// кажется это интереснее делать в вершинном шейдере
	vec3 vertexPos = (vec4(localPosition, 1.0) * matWorldT).xyz;
	vec3 viewDir = normalize(cameraPos.xyz - vertexPos);

	for (int i = 0; i < 3; ++i)
	{
		// Выходим, как только закончились источники освещения
        if (float(i) >= lightsCount.x) break;
		
		float type = lights[i].type.x;
		float epsilon = 0.001;
		
		vec4 lightCol = lights[i].color;
		vec3 lightDir = vec3(0,0,0);
	  
		float attenuation = 1.0;
		if (abs(type - 1.0) < epsilon){
		// Directional light
		lightDir = normalize(lights[i].direction.xyz).xyz;
		
		} else {
		// Point light
	
		float distance = length(lights[i].position.xyz - vertexPos);

		attenuation = 0.4 / (distance * distance);
		
		lightDir = normalize(vertexPos - lights[i].position.xyz).xyz;
		
		} 
		//Spot Light
		
		if(abs(type - 3.0) < epsilon){

		float theta = dot(-lightDir, normalize(-lights[i].direction.xyz));
		
		float outerCutOff =  cos(3.14/5);
		float cutOff = cos(3.14/20);

		float epsilon2 = cutOff - outerCutOff;
		float intensity = clamp((theta - outerCutOff) / epsilon2, 0.0, 1.0);
		//intensity = 1.0;
		attenuation *= intensity;
		}
		
		col += attenuation * materialColor.rgb * (calcDiffuse(lightCol, lightDir, vertexNormal) 
		+ calcSpecular(lightCol, lightDir, vertexNormal, viewDir));
	}
	
	gl_FragColor = vec4(col, 1.0);
    gl_FragColor.a = 1.0;
}
