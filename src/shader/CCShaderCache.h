/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#ifndef __CCSHADERCACHE_H__
#define __CCSHADERCACHE_H__

#include "tool.h"

enum {
	kCCShaderType_Position_uColor,
	kCCShaderType_PositionTexture_afterimage,
	kCCShaderType_PositionTexture,

	kCCShaderType_MAX,
};

#define kCCShader_Position_uColor							"ShaderPosition_uColor"
#define kCCShader_PositionTexture_afterimage                 "ShaderPositionTexture_afterimage "
#define kCCShader_PositionTexture							"ShaderPositionTexture"



class CCGLProgram;

class CCShaderCache : public CObject 
{
public:
    CCShaderCache();
    virtual ~CCShaderCache();
    static CCShaderCache* sharedShaderCache();

    static void purgeSharedShaderCache();

    void loadDefaultShaders();
    
    CCGLProgram * programForKey(const char* key);

    void addProgram(CCGLProgram* program, const char* key);

private:
    bool init();
    void loadDefaultShader(CCGLProgram *program, int type);

    CDictionary* m_pPrograms;

};

#endif /* __CCSHADERCACHE_H__ */
