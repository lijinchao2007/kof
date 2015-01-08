/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "ccGLStateCache.h"
#include "cocos/ccTypes.h"
#include "CCGLProgram.h"



void ccGLBindTexture2D(GLuint textureId)
{
    ccGLBindTexture2DN(0, textureId);
}

void ccGLBindTexture2DN(GLuint textureUnit, GLuint textureId)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureId);
}


void ccGLDeleteTexture(GLuint textureId)
{
    ccGLDeleteTextureN(0, textureId);
}

void ccGLDeleteTextureN(GLuint textureUnit, GLuint textureId)
{
	glDeleteTextures(1, &textureId);
}



void ccGLEnableVertexAttribs( unsigned int flags )
{
    
    /* Position */
    bool enablePosition = flags & kCCVertexAttribFlag_Position;

        if( enablePosition )
            glEnableVertexAttribArray( kCCVertexAttrib_Position );
        else
            glDisableVertexAttribArray( kCCVertexAttrib_Position );


    /* Color */
    bool enableColor = (flags & kCCVertexAttribFlag_Color) != 0 ? true : false;

        if( enableColor )
            glEnableVertexAttribArray( kCCVertexAttrib_Color );
        else
            glDisableVertexAttribArray( kCCVertexAttrib_Color );



    /* Tex Coords */
    bool enableTexCoords = (flags & kCCVertexAttribFlag_TexCoords) != 0 ? true : false;

    
        if( enableTexCoords )
            glEnableVertexAttribArray( kCCVertexAttrib_TexCoords );
        else
            glDisableVertexAttribArray( kCCVertexAttrib_TexCoords );

}


