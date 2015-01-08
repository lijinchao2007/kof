/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __TOKEN__
#define __TOKEN__

#include <map>
#include <string>
#include "define.h"

#define  NOT_USE_PARSE_MAIN 1
#ifndef __TOKEN_TYPE_
#define TOKEN_SECTION 193
#define TOKEN_ID 194
#define TOKEN_ICON 195
#define TOKEN_FCON 196
#define TOKEN_STRING 197
#define TOKEN_NEWLINE 198
#define TOKEN_OP 199
#define TOKEN_ERRORCHAR 300

#define __TOKEN_TYPE_
#endif // __TOKEN_TYPE_




class CToken
{
public:
    CToken();
    ~CToken();
    
    bool OpenFile( const char* filename ); // false if already open file or on fail
    bool CloseFile();                      // false if no file open
    
    bool AtEndOfFile();
	bool AtEndOfLine();
	bool AtEnd();
	bool IsSection();

	const char* GetCurToken();
	const char* GetToken();
    bool        GetToken( char* destString, int maxLength );
    bool        CheckToken( const char* stringToLookFor, bool consumeIfMatch = true );
    
    int         GetInt();
    float       GetFloat();
    
    const char* GetFileName()       { return m_Filename; }
    int         GetLineNumber();

	void        SetIsCaseSensitive( bool b )  { m_IsCaseSensitive = b; }

public:    
	char*  m_nextbuffer;
	bool m_AtEndOfLine;
	bool m_AtEndOfFile;
	char   m_buffer[MAX_PATH];
	int		m_buffersize;
    char    m_Filename[MAX_PATH];
	int     m_tokenType;
	bool    m_IsCaseSensitive;
};


#endif
