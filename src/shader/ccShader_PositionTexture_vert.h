/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

"														\n\
attribute vec2 a_position;								\n\
attribute vec2 a_texCoord;								\n\
														\n\
#ifdef GL_ES											\n\
varying mediump vec2 v_texCoord;						\n\
#else													\n\
varying vec2 v_texCoord;								\n\
#endif													\n\
														\n\
void main()												\n\
{														\n\
    gl_Position = CC_MVPMatrix * vec4(a_position,0.0,1.0);     	\n\
	v_texCoord = a_texCoord;							\n\
}														\n\
";
