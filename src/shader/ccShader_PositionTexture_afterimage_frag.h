/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

"																							\n\
																							\n\
																							\n\
varying vec2 v_texCoord;																	\n\
uniform sampler2D CC_Texture0;																\n\
																							\n\
uniform		float u_palinvertall;															\n\
uniform		float u_palcolor;																\n\
uniform		vec3 u_palbright;																\n\
uniform		vec3 u_palcontrast;																\n\
uniform		vec3 u_palpostbright;															\n\
																							\n\
uniform		int u_effectCount;																\n\
uniform		vec3 u_paladd;																	\n\
uniform		vec3 u_palmul;																	\n\
																							\n\
																							\n\
void main()																					\n\
{																							\n\
	vec4 temp =  texture2D(CC_Texture0, v_texCoord);										\n\
	if ((CC_IsDrawBack==0)&&( abs(temp.r-CC_BackColor.r)<0.01 && abs(temp.g-CC_BackColor.g)<0.01 && abs(temp.b-CC_BackColor.b)<0.01 && abs(temp.a-CC_BackColor.a)<0.01))							\n\
		discard;																			\n\
																							\n\
	float graycolor = (temp.r+temp.g+temp.b)*(1.0-u_palcolor)/3.0;							\n\
	temp.r = temp.r*u_palcolor + graycolor;													\n\
	temp.g = temp.g*u_palcolor + graycolor;													\n\
	temp.b = temp.b*u_palcolor + graycolor;													\n\
	if(u_palinvertall==1.0)																	\n\
		temp.rgb = vec3(1.0, 1.0, 1.0) - temp.rgb;											\n\
																							\n\
	temp.rgb = (temp.rgb + u_palbright) * u_palcontrast + u_palpostbright;					\n\
																							\n\
	for(int i=0;i<u_effectCount;i++)														\n\
	{																						\n\
		temp.rgb = (temp.rgb+u_paladd)*u_palmul;											\n\
	}																						\n\
																							\n\
																							\n\
																							\n\
	gl_FragColor = vec4(temp.rgb,temp.a*CC_Alpha);											\n\
																							\n\
}																							\n\
";