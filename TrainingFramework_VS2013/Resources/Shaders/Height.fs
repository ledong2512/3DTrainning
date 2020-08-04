precision mediump float;
varying vec3 v_pos;
varying vec2 v_uv;
varying vec3 v_nor;
uniform sampler2D u_multi[4];
varying float v_fogDepth;
const float u_fogNear=3.0;
const float u_fogFar=6.0;
const vec4 u_fogColor=vec4(0.8, 0.9, 1, 1.0);
void main()
{
	vec4 blend_color = texture2D(u_multi[0],v_uv);
	vec4 color = (texture2D(u_multi[1],v_uv)*blend_color.r + texture2D(u_multi[2],v_uv)*blend_color.g + texture2D(u_multi[3],v_uv)*blend_color.b) / (blend_color.r+blend_color.g+blend_color.b) ;
	float fogAmount = smoothstep(u_fogNear, u_fogFar, v_fogDepth);
	gl_FragColor =  mix(color, u_fogColor, fogAmount);  
}
