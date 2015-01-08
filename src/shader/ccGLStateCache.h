/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __CCGLSTATE_H__
#define __CCGLSTATE_H__

#include "define.h"
#include "tool.h"


class CCGLProgram;

/** vertex attrib flags */
enum {
    kCCVertexAttribFlag_None        = 0,

    kCCVertexAttribFlag_Position    = 1 << 0,
    kCCVertexAttribFlag_Color       = 1 << 1,
    kCCVertexAttribFlag_TexCoords   = 1 << 2,

    kCCVertexAttribFlag_PosColorTex = ( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color | kCCVertexAttribFlag_TexCoords ),
};



void  ccGLEnableVertexAttribs(unsigned int flags);

void  ccGLBindTexture2D(GLuint textureId);

void  ccGLBindTexture2DN(GLuint textureUnit, GLuint textureId);

void  ccGLDeleteTexture(GLuint textureId);

void  ccGLDeleteTextureN(GLuint textureUnit, GLuint textureId);

    

#endif /* __CCGLSTATE_H__ */
