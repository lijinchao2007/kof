/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "CCGLProgram.h"
#include "ccGLStateCache.h"
#include "driver/glesext.h"


CCGLProgram::CCGLProgram(const char* name)
: m_uProgram(0)
, m_uVertShader(0)
, m_uFragShader(0)
, m_pHashForUniforms(NULL)
{
	if (name)
	{
		SDL_strlcpy(m_shaderName, name, MAX_PATH);
	}
	
}

CCGLProgram::~CCGLProgram()
{
    PrintMessage("cocos2d: %s %d deallocing 0x%X", __FUNCTION__, __LINE__, this);

    // there is no need to delete the shaders. They should have been already deleted.
    CAssert(m_uVertShader == 0, "Vertex Shaders should have been already deleted");
    CAssert(m_uFragShader == 0, "Fragment Shaders should have been already deleted");

    if (m_uProgram) 
    {
        glDeleteProgram( m_uProgram );
    }

    tHashUniformEntry *current_element, *tmp;

    // Purge uniform hash
    HASH_ITER(hh, m_pHashForUniforms, current_element, tmp)
    {
        HASH_DEL(m_pHashForUniforms, current_element);
        free(current_element->value);
        free(current_element);
    }
}

bool CCGLProgram::initWithVertexShaderByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray)
{
    
	m_uProgram = glCreateProgram();
	CHECK_GL_ERROR_DEBUG();
	m_uVertShader = m_uFragShader = 0;
  
    if (vShaderByteArray)
    {
        if (!compileShader(&m_uVertShader, GL_VERTEX_SHADER, vShaderByteArray))
        {
            PrintMessage("cocos2d: ERROR: Failed to compile vertex shader");
 			return false;
       }
    }

    // Create and compile fragment shader
    if (fShaderByteArray)
    {
        if (!compileShader(&m_uFragShader, GL_FRAGMENT_SHADER, fShaderByteArray))
        {
            PrintMessage("cocos2d: ERROR: Failed to compile fragment shader");
            CHECK_GL_ERROR_DEBUG();
			return false;
        }
    }


    if (m_uVertShader)
    {
        glAttachShader(m_uProgram, m_uVertShader);
    }
    CHECK_GL_ERROR_DEBUG();

    if (m_uFragShader)
    {
         glAttachShader(m_uProgram, m_uFragShader);
    }
    m_pHashForUniforms = NULL;
    
    CHECK_GL_ERROR_DEBUG();

    return true;
}



bool CCGLProgram::compileShader(GLuint * shader, GLenum type, const GLchar* source)
{
    GLint status;
 
    if (!source)
    {
        return false;
    }
    
    const GLchar *sources[] = {
        "#ifdef GL_ES\n"
        "precision lowp float;\n"
        "#endif\n"
		"uniform float CC_Alpha;\n"
		"uniform int CC_IsDrawBack;\n"
		"uniform vec4 CC_BackColor;\n"
        "uniform mat4 CC_MVPMatrix;\n"
        "//CC INCLUDES END\n\n",
        source,
    };

    *shader = glCreateShader(type);
	 CHECK_GL_ERROR_DEBUG();
    glShaderSource(*shader, sizeof(sources)/sizeof(*sources), sources, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);

    if (! status)
    {
        GLint infoLen = 0;
        glGetShaderiv (*shader, GL_INFO_LOG_LENGTH, &infoLen );
        
        if ( infoLen > 1 )
        {
            GLchar* infoLog = (GLchar *)malloc(sizeof(GLchar) * infoLen);
            glGetShaderInfoLog(*shader, infoLen, NULL, infoLog );
            PrintMessage( "Error compiling shader:\n%s\n", infoLog );
            free ( infoLog );
            CAssert(false, "shader compiled failed");
        }
        
        return false;
    }
    return (status == GL_TRUE);
}

void CCGLProgram::addAttribute(const char* attributeName, GLuint index)
{
    glBindAttribLocation(m_uProgram, index, attributeName);
	CHECK_GL_ERROR_DEBUG();
}

void CCGLProgram::updateUniforms()
{
	m_uUniforms[kCCUniformAlpha] = glGetUniformLocation(m_uProgram, kCCUniformAlpha_s);
	m_uUniforms[kCCUniformIsDrawBack] = glGetUniformLocation(m_uProgram, kCCUniformIsDrawBack_s);
	m_uUniforms[kCCUniformBackColor] = glGetUniformLocation(m_uProgram, kCCUniformBackColor_s);
	m_uUniforms[kCCUniformMVPMatrix] = glGetUniformLocation(m_uProgram, kCCUniformMVPMatrix_s);

    m_uUniforms[kCCUniformSampler] = glGetUniformLocation(m_uProgram, kCCUniformSampler_s);

    this->use();
    
    // Since sample most probably won't change, set it to 0 now.
    this->setUniformLocationWith1i(m_uUniforms[kCCUniformSampler], 0);

	CHECK_GL_ERROR_DEBUG();
}

bool CCGLProgram::link()
{
    CAssert(m_uProgram != 0, "Cannot link invalid program");
 
    GLint status = GL_TRUE;
    
    glLinkProgram(m_uProgram);
	CHECK_GL_ERROR_DEBUG();
    if (m_uVertShader)
    {
        glDeleteShader(m_uVertShader);
    }
    
    if (m_uFragShader)
    {
        glDeleteShader(m_uFragShader);
    }
    
    m_uVertShader = m_uFragShader = 0;
	
    return (status == GL_TRUE);
}

void CCGLProgram::use()
{
    glUseProgram(m_uProgram);
}


bool CCGLProgram::updateUniformLocation(GLint location, GLvoid* data, unsigned int bytes)
{
    if (location < 0)
    {
        return false;
    }
    
    bool updated = true;
    tHashUniformEntry *element = NULL;
    HASH_FIND_INT(m_pHashForUniforms, &location, element);

    if (! element)
    {
        element = (tHashUniformEntry*)malloc( sizeof(*element) );

        // key
        element->location = location;

        // value
        element->value = malloc( bytes );
        memcpy(element->value, data, bytes );

        HASH_ADD_INT(m_pHashForUniforms, location, element);
    }
    else
    {
        if (memcmp(element->value, data, bytes) == 0)
        {
            updated = false;
        }
        else
        {
            memcpy(element->value, data, bytes);
        }
    }

    return updated;
}

GLint CCGLProgram::getUniformLocationForName(const char* name)
{
    CAssert(name != NULL, "Invalid uniform name" );
    CAssert(m_uProgram != 0, "Invalid operation. Cannot get uniform location when program is not initialized");
    
    return glGetUniformLocation(m_uProgram, name);
}

void CCGLProgram::setUniformLocationWith1i(GLint location, GLint i1)
{
	bool updated =  updateUniformLocation(location, &i1, sizeof(i1)*1);

	if( updated )
	{
		glUniform1i( (GLint)location, i1);
	}
}

void CCGLProgram::setUniformLocationWith2i(GLint location, GLint i1, GLint i2)
{
	GLint ints[2] = {i1,i2};
	bool updated =  updateUniformLocation(location, ints, sizeof(ints));

	if( updated )
	{
		glUniform2i( (GLint)location, i1, i2);
	}
}

void CCGLProgram::setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3)
{
	GLint ints[3] = {i1,i2,i3};
	bool updated =  updateUniformLocation(location, ints, sizeof(ints));

	if( updated )
	{
		glUniform3i( (GLint)location, i1, i2, i3);
	}
}

void CCGLProgram::setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4)
{
	GLint ints[4] = {i1,i2,i3,i4};
	bool updated =  updateUniformLocation(location, ints, sizeof(ints));

	if( updated )
	{
		glUniform4i( (GLint)location, i1, i2, i3, i4);
	}
}

void CCGLProgram::setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
	bool updated =  updateUniformLocation(location, ints, sizeof(int)*2*numberOfArrays);

	if( updated )
	{
		glUniform2iv( (GLint)location, (GLsizei)numberOfArrays, ints );
	}
}

void CCGLProgram::setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
	bool updated =  updateUniformLocation(location, ints, sizeof(int)*3*numberOfArrays);

	if( updated )
	{
		glUniform3iv( (GLint)location, (GLsizei)numberOfArrays, ints );
	}
}

void CCGLProgram::setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
	bool updated =  updateUniformLocation(location, ints, sizeof(int)*4*numberOfArrays);

	if( updated )
	{
		glUniform4iv( (GLint)location, (GLsizei)numberOfArrays, ints );
	}
}

void CCGLProgram::setUniformLocationWith1f(GLint location, GLfloat f1)
{
	bool updated =  updateUniformLocation(location, &f1, sizeof(f1)*1);

	if( updated )
	{
		glUniform1f( (GLint)location, f1);
	}
}

void CCGLProgram::setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2)
{
	GLfloat floats[2] = {f1,f2};
	bool updated =  updateUniformLocation(location, floats, sizeof(floats));

	if( updated )
	{
		glUniform2f( (GLint)location, f1, f2);
	}
}

void CCGLProgram::setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3)
{
	GLfloat floats[3] = {f1,f2,f3};
	bool updated =  updateUniformLocation(location, floats, sizeof(floats));

	if( updated )
	{
		glUniform3f( (GLint)location, f1, f2, f3);
	}
}

void CCGLProgram::setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
	GLfloat floats[4] = {f1,f2,f3,f4};
	bool updated =  updateUniformLocation(location, floats, sizeof(floats));

	if( updated )
	{
		glUniform4f( (GLint)location, f1, f2, f3,f4);
	}
}

void CCGLProgram::setUniformLocationWith2fv(GLint location, GLfloat* floats, unsigned int numberOfArrays)
{
	bool updated =  updateUniformLocation(location, floats, sizeof(float)*2*numberOfArrays);

	if( updated )
	{
		glUniform2fv( (GLint)location, (GLsizei)numberOfArrays, floats );
	}
}

void CCGLProgram::setUniformLocationWith3fv(GLint location, GLfloat* floats, unsigned int numberOfArrays)
{
	bool updated =  updateUniformLocation(location, floats, sizeof(float)*3*numberOfArrays);

	if( updated )
	{
		glUniform3fv( (GLint)location, (GLsizei)numberOfArrays, floats );
	}
}

void CCGLProgram::setUniformLocationWith4fv(GLint location, GLfloat* floats, unsigned int numberOfArrays)
{
	bool updated =  updateUniformLocation(location, floats, sizeof(float)*4*numberOfArrays);

	if( updated )
	{
		glUniform4fv( (GLint)location, (GLsizei)numberOfArrays, floats );
	}
}


void CCGLProgram::setUniformLocationWithMatrix4fv(GLint location, GLfloat* matrixArray, unsigned int numberOfMatrices)
{
    bool updated =  updateUniformLocation(location, matrixArray, sizeof(float)*16*numberOfMatrices);

    if( updated )
    {
        glUniformMatrix4fv( (GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
    }
}

void CCGLProgram::setUniformsForBuiltins()
{

	GLfloat projection[4][4];
	/* Prepare an orthographic projection */
	Sint32 designeW = Common_GetDesiginWidth();
	Sint32 designeH = Common_GetDesiginHeight();
	projection[0][0] = 2.0f / designeW;
	projection[0][1] = 0.0f;
	projection[0][2] = 0.0f;
	projection[0][3] = 0.0f;

	projection[1][0] = 0.0f;
	projection[1][1] = -2.0f / designeH;
	projection[1][2] = 0.0f;
	projection[1][3] = 0.0f;

	projection[2][0] = 0.0f;
	projection[2][1] = 0.0f;
	projection[2][2] = 1.0f;
	projection[2][3] = 0.0f;

	projection[3][0] = -1.0f;
	projection[3][1] = 1.0f;
	projection[3][2] = 0.0f;
	projection[3][3] = 1.0f;
	setUniformLocationWithMatrix4fv(m_uUniforms[kCCUniformMVPMatrix], (GLfloat*)projection, 1);

}

void CCGLProgram::reset()
{
    m_uVertShader = m_uFragShader = 0;
    memset(m_uUniforms, 0, sizeof(m_uUniforms));

    m_uProgram = 0;

    
    tHashUniformEntry *current_element, *tmp;
    
    // Purge uniform hash
    HASH_ITER(hh, m_pHashForUniforms, current_element, tmp) 
    {
        HASH_DEL(m_pHashForUniforms, current_element);
        free(current_element->value);
        free(current_element);
    }
    m_pHashForUniforms = NULL;
}

