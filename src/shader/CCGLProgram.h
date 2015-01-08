/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __CCGLPROGRAM_H__
#define __CCGLPROGRAM_H__

#include "define.h"
#include "tool.h"
#include "cocos/ccTypes.h"

enum {
	kCCVertexAttrib_Position,
	kCCVertexAttrib_Color,
	kCCVertexAttrib_TexCoords,

	kCCVertexAttrib_MAX,
};

enum {
	kCCUniformAlpha,
	kCCUniformIsDrawBack,
	kCCUniformBackColor,
	kCCUniformMVPMatrix,
	kCCUniformSampler,

	kCCUniform_MAX,
};
// uniform names
#define kCCUniformAlpha_s			"CC_Alpha"
#define kCCUniformIsDrawBack_s			"CC_IsDrawBack"
#define kCCUniformBackColor_s			"CC_BackColor"
#define kCCUniformMVPMatrix_s			"CC_MVPMatrix"
#define kCCUniformSampler_s				"CC_Texture0"

// Attribute names
#define    kCCAttributeNameColor           "a_color"
#define    kCCAttributeNamePosition        "a_position"
#define    kCCAttributeNameTexCoord        "a_texCoord"


typedef struct _hashUniformEntry
{
	GLvoid*         value;       // value
	unsigned int    location;    // Key
	UT_hash_handle  hh;          // hash entry
} tHashUniformEntry;


/** CCGLProgram
 Class that implements a glProgram
 
 
 @since v2.0.0
 */
class CCGLProgram : public CObject
{
public:
    CCGLProgram(const char* name=NULL);
    virtual ~CCGLProgram();
    bool initWithVertexShaderByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);

    void addAttribute(const char* attributeName, GLuint index);
    bool link();
    void use();
    void updateUniforms();
    GLint getUniformLocationForName(const char* name);
    void setUniformLocationWith1i(GLint location, GLint i1);
    void setUniformLocationWith2i(GLint location, GLint i1, GLint i2);
    void setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3);
    void setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4);
    void setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays);
    void setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays);
    void setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays);
    void setUniformLocationWith1f(GLint location, GLfloat f1);
    void setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2);
    void setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3);
    void setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);
    void setUniformLocationWith2fv(GLint location, GLfloat* floats, unsigned int numberOfArrays);
    void setUniformLocationWith3fv(GLint location, GLfloat* floats, unsigned int numberOfArrays);
    void setUniformLocationWith4fv(GLint location, GLfloat* floats, unsigned int numberOfArrays);
    void setUniformLocationWithMatrix4fv(GLint location, GLfloat* matrixArray, unsigned int numberOfMatrices);

	void setUniformsForBuiltins();
    void reset();
    inline const GLuint getProgram() { return m_uProgram; }

private:
    bool updateUniformLocation(GLint location, GLvoid* data, unsigned int bytes);
    bool compileShader(GLuint * shader, GLenum type, const GLchar* source);

private:
	char			  m_shaderName[MAX_PATH];
	GLuint            m_uProgram;
    GLuint            m_uVertShader;
    GLuint            m_uFragShader;
	GLint             m_uUniforms[kCCUniform_MAX];
    struct _hashUniformEntry* m_pHashForUniforms;
};

#endif /* __CCGLPROGRAM_H__ */
