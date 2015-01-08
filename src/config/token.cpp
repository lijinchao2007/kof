/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include <ctype.h>
#include "token.h"
#include "tokenizer.h"
#include "tool.h"

extern char sTokDefaultCommentChars[];
extern char sTokDefaultOperators[][3];
extern int skTokDefaultOperatorCount;

extern "C"
{
extern char *yytext;
extern int yyleng;
extern int yylineno;
extern void backtoken(int);
extern int yylex (void);
extern int yylex_destroy (void );
struct yy_buffer_state;
extern yy_buffer_state* yy_scan_string (const char*);
}

CToken::CToken()
	:m_tokenType(1)
	,m_AtEndOfFile(false)
{
	m_IsCaseSensitive = true;
}

CToken::~CToken()
{
}

bool CToken::OpenFile( const char* filename )
{
	SDL_RWops* file = SDL_RWFromFile(filename, "rb");
	if( !file )
	{
		return false;
	}
	// set file name
	SDL_strlcpy(m_Filename, filename, MAX_PATH);
	int filesize = SDL_RWsize( file );
	if( !filesize )
		return false;

	char* fileBuffer = new char[filesize+1];
	SDL_RWseek(file, 0, RW_SEEK_SET);
	SDL_RWread(file, fileBuffer, 1,  filesize);
	SDL_RWclose(file);
	fileBuffer[filesize] = '\0';
	yy_scan_string(fileBuffer);
	GetToken();
	delete fileBuffer;

	return true;
}

bool CToken::CloseFile()
{
	yylex_destroy();
	return true;
}

bool CToken::AtEndOfLine()
{
	return m_AtEndOfLine;
}

bool CToken::AtEndOfFile()
{
	return m_AtEndOfFile;
}

bool CToken::AtEnd()
{
	return m_AtEndOfLine || m_AtEndOfFile;
}

bool CToken::IsSection()
{
	return m_tokenType == TOKEN_SECTION;
}

const char* CToken::GetCurToken()
{
	return yytext;
}

const char* CToken::GetToken()
{
	m_buffersize = yyleng;
	SDL_strlcpy(m_buffer, yytext, yyleng+1);
	m_AtEndOfLine = false;
	if (m_AtEndOfFile)
	{
		return m_buffer;
	}
	do 
	{
		m_tokenType=yylex();
		m_nextbuffer=yytext;
		if (m_tokenType == TOKEN_ERRORCHAR&&yytext[0]>0)
		{
			throw(CError("get TOKEN_ERRORCHAR %s, filename:%s, lineno:%d,",yytext, GetFileName(),GetLineNumber()));
		}
		if (m_tokenType == TOKEN_NEWLINE)
		{
			m_AtEndOfLine = true;
		}
		if (m_tokenType == 0)
		{
			PrintMessage("end tok");
			m_AtEndOfFile = true;
			break;
		}
	} while (m_tokenType == TOKEN_NEWLINE||m_tokenType == TOKEN_ERRORCHAR);
	return m_buffer;
}

int CToken::GetLineNumber()
{
	return yylineno;
}

bool CToken::GetToken( char* destString, int maxLength )
{
	 
	SDL_strlcpy(destString, yytext, maxLength > yyleng+1 ? yyleng+1 : maxLength );
	GetToken();
	return true;
}


bool CToken::CheckToken( const char* stringToLookFor, bool consumeIfMatch )
{
	bool result = m_IsCaseSensitive ? ( SDL_strcmp( stringToLookFor, yytext ) == 0 ) : ( SDL_strcasecmp( stringToLookFor, yytext ) == 0 );
	if (result&&consumeIfMatch)
	{
		GetToken();
	}
	return result;    
}


float CToken::GetFloat()
{
	float ret;
	if(m_tokenType == TOKEN_FCON)
	{
		ret = atof(yytext);
	}else
	{
		ret = 0.0;
	}
	GetToken();
	return ret;
}

int CToken::GetInt()
{
	int ret;
	if(m_tokenType == TOKEN_ICON)
	{
		ret = atoi(yytext);
	}else
	{
		ret = 0;
	}
	GetToken();
	return ret;
}
