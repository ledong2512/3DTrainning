precision mediump float;
varying vec3 v_pos;
varying vec2 v_uv;
varying vec3 v_nor;
uniform sampler2D u_multi[3];
uniform float u_time;
void main()
{
	float dMax=0.1;
	vec2 disp = texture2D(u_multi[1], vec2(v_uv.r, v_uv.g + u_time)).rg;
	vec2 offset = (2.0 * disp - 1.0) * dMax;
	vec2 Tex_coords_displaced =v_uv+offset;
	vec4 fire_color = texture2D (u_multi[0], Tex_coords_displaced);
	vec4 AlphaValue = texture2D(u_multi[2], v_uv);
	vec4 vColor=fire_color * (1.0, 1.0, 1.0, AlphaValue.r);
	vColor.r = vColor.r * vColor.a;
	vColor.g = vColor.g * vColor.a;
	vColor.b = vColor.b * vColor.a;
	gl_FragColor = vColor;

}
