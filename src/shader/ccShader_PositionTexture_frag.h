/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

"																		\n\
																		\n\
varying vec2 v_texCoord;												\n\
uniform sampler2D CC_Texture0;											\n\
void main()																\n\
{																		\n\
	vec4 temp = texture2D(CC_Texture0, v_texCoord);						\n\
	if ((CC_IsDrawBack==0) && abs(temp.r-CC_BackColor.r)<0.01 && abs(temp.g-CC_BackColor.g)<0.01 && abs(temp.b-CC_BackColor.b)<0.01 && abs(temp.a-CC_BackColor.a)<0.01 )		\n\
		discard;														\n\
	gl_FragColor =  temp;												\n\
	gl_FragColor.a = temp.a*CC_Alpha;												\n\
}																		\n\
";
