attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
varying vec3 v_pos;
attribute vec3 a_nor;
varying vec3 v_nor;
uniform mat4 u_W,u_V,u_P;
varying float v_fogDepth;
void main()

{
vec4 posL =vec4(a_posL, 1.0);
vec4 worldPos=u_W*posL;
vec4 distanceToCam=u_V*worldPos;
gl_Position =u_P* distanceToCam;
v_fogDepth = -distanceToCam.z;
v_uv=a_uv;
v_nor=a_nor;
v_pos=a_posL;
}
   