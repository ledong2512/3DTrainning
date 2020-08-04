precision mediump float;
uniform samplerCube cubemap;
varying vec3 v_pos;
varying float v_fogDepth;
const float u_fogNear=3.0;
const float u_fogFar=6.0;
const vec4 u_fogColor=vec4(0.8, 0.9, 1, 1.0);
void main(void)
{
 vec4 color = textureCube(cubemap, v_pos);
 float fogAmount = smoothstep(u_fogNear, u_fogFar, v_fogDepth);
gl_FragColor =  mix(color, u_fogColor, fogAmount);  
}