attribute vec3 a_posL;
uniform mat4 u_W,u_V,u_P;
varying float v_fogDepth;
varying vec3 v_pos;
void main(void)
{
vec4 posL =vec4(a_posL, 1.0);
vec4 worldPos=u_W*posL;
vec4 distanceToCam=u_V*worldPos;
gl_Position =u_P* distanceToCam;
v_fogDepth = -distanceToCam.z;
 v_pos =a_posL;
}