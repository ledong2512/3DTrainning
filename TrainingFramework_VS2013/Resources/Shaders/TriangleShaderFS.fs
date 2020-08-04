precision mediump float;
varying vec3 v_pos;
varying vec2 v_uv;
varying vec3 v_nor;
uniform sampler2D u_texture;
varying float v_fogDepth;
const float u_fogNear=3.0;
const float u_fogFar=6.0;
const vec4 u_fogColor=vec4(0.8, 0.9, 1, 1.0);
void main()
{
	vec3 lightPos=vec3(2.0, 5.0, 3.0);
	vec3 lightColor=vec3(1.0, 1.0, 1.0);
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
	vec3 FragPos=v_pos;
	vec3 norm = normalize(v_nor);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
    vec3 viewDir = normalize( - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    vec3 specular = specularStrength  * lightColor;  

	vec3 result = (ambientStrength +specularStrength+ diffuse) * texture2D(u_texture,v_uv).xyz;
	vec4 color=vec4(result,1.0);
	float fogAmount = smoothstep(u_fogNear, u_fogFar, v_fogDepth);
	gl_FragColor =  mix(color, u_fogColor, fogAmount);  


}
