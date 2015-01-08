/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include <ctype.h>
#include "tokenizer.h"
#include "tool.h"

char sTokDefaultCommentChars[] = ";";
char sTokDefaultOperators[][3] =
{
	"**",
	">=",
	"<=",
	":=",
	"!=",
	"&&",
	"||",
	"~",
	"!",
	"-",
	"*",
	"/",
	"%",
	"+",
	">",
	"<",
	"=",
	"[",
	"]",
	"(",
	")",
	"/",
	"&",
	"^",
	"|",
	",",
	"$",
};
int skTokDefaultOperatorCount = sizeof(sTokDefaultOperators)/sizeof(sTokDefaultOperators[0]);

void ParseWarning(CTokenizer &tok, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	char *message;
	message = SDL_stack_alloc(char, SDL_MAX_LOG_MESSAGE);
	if (!message) {
		return;
	}
	SDL_vsnprintf(message, SDL_MAX_LOG_MESSAGE, fmt, ap);
	va_end(ap);

	char *messageall;
	messageall = SDL_stack_alloc(char, SDL_MAX_LOG_MESSAGE);
	if (!messageall) {
		return;
	}
	SDL_snprintf(messageall, SDL_MAX_LOG_MESSAGE, "Parser error:in file %s at line %i:token:%s error:%s",
		tok.GetFileName()
		,tok.GetLineNumber()
		,tok.GetPartToken()
		,message);

	PrintWaring(messageall);
	SDL_stack_free(message);
	SDL_stack_free(messageall);

}


bool Common_ParseSection(CTokenizer &tok, std::map<std::string, std::string>& dict)
{
	char sectionName[MAX_PATH] = {0};
	char keyName[MAX_PATH] = {0};
	char keyNameExtr[MAX_PATH] = {0};
	SDL_snprintf(sectionName, MAX_PATH, "%s", tok.GetToken());
	if(!tok.CheckToken("]"))
		throw CError("ParseSection:Expected ]");
	while(!tok.AtEndOfFile())
	{
		keyName[0] = 0;
		if(tok.CheckToken("[", false))
			break;
		SDL_snprintf(keyName, MAX_PATH, "%s.%s", sectionName, tok.GetToken());
		/*if (0==SDL_strcasecmp("Info.name", keyName))
		{
			PrintMessage("");
		}*/
		if(!tok.CheckToken("="))
		{
			PrintWaring("ParseSection keyName%s :Expected =", keyName);
			GET_ALL_LINE_TOKEN(tok);
		}
		PrintMessage("Common_ParseSection keyName %s ", keyName);
		if (tok.AtEndOfLine()||tok.AtEndOfFile())
		{
			continue;
		}
		char value1[MAX_PATH];
		tok.GetToken(value1,MAX_PATH);
				
		/*if (SDL_strcasecmp("Velocity.jump.neu", keyName)==0)
		{
		PrintMessage("");
		}*/
		if (tok.AtEndOfLine()||tok.AtEndOfFile())
		{
			dict.insert(std::pair<std::string, std::string>(SDL_strlwr(keyName), value1));
		}else{
			if (!tok.CheckToken(","))
			{
				//Error("arg error,need , ", tok);
				ParseWarning(tok, "arg error,need ,");
				GET_ALL_LINE_TOKEN(tok);
				continue;
			}
			const char* value2 = tok.GetToken();
			if (!tok.AtEndOfLine())
			{
				// parseSpecial
				if (SDL_strcasecmp("intpersistindex", keyName)==0)
				{
				}
				ParseWarning(tok, "arg is too much!");
				GET_ALL_LINE_TOKEN(tok);
				continue;
			}
			if (SDL_strcasecmp(keyName, "Velocity.jump.neu")==0)
			{
				dict.insert(std::pair<std::string, std::string>("velocity.jump.x", value1));
				dict.insert(std::pair<std::string, std::string>("velocity.jump.y", value2));
			}
			SDL_snprintf(keyNameExtr, MAX_PATH, "%s.x", keyName);
			dict.insert(std::pair<std::string, std::string>(SDL_strlwr(keyNameExtr), value1));
			SDL_snprintf(keyNameExtr, MAX_PATH, "%s.y", keyName);
			dict.insert(std::pair<std::string, std::string>(SDL_strlwr(keyNameExtr), value2));
		}
				
	}
	return true;
}


CTokenizer::CTokenizer( int bufferSize)
{
	//    Assert(( bufferSize > 0 ) && ( bufferSize < ( 1 << 30 ) );
	m_BufferSize = bufferSize;        
	m_Buffer = new char[ bufferSize ];

	m_NumOperatorCharsRead = 0;

	m_Filename[0] = 0;
	m_FileBuffer = NULL;
	m_FileSize = 0;
	m_CurrFilePos = 0;
	m_CurrFileLine = 0;
	m_LastLinePos = 0;

	m_BufferIsNextToken = false;
	m_AtEndOfLine = false;
	m_AtEndOfFile = false;

	m_ReturnNegativeSeperatelyFromNumber = false;
	m_IsCaseSensitive = true;

	m_LastTokenWasQuotedString = false;
}

CTokenizer::~CTokenizer()
{
	if( m_FileBuffer )
		delete m_FileBuffer;
	delete m_Buffer;
}

bool CTokenizer::OpenFile( const char* filename )
{
	if( m_FileBuffer )
		return false;

	SDL_RWops* file = SDL_RWFromFile(filename, "rb");
	if( !file )
	{
		return false;
	}
	// set file name
	SDL_strlcpy(m_Filename, filename, MAX_PATH);
	m_FileSize = SDL_RWsize( file );
	if( !m_FileSize )
		return false;
	 
	m_FileBuffer =  new char[ m_FileSize ];

	SDL_RWseek( file, 0, RW_SEEK_SET );
	SDL_RWread(file, m_FileBuffer, 1,  m_FileSize);

	SDL_RWclose(file);

	m_CurrFilePos = 0;
	m_CurrFileLine = 0;
	m_LastLinePos = 0;

	m_BufferIsNextToken = false;
	m_AtEndOfLine = false;
	m_AtEndOfFile = false;

	return true;
}

bool CTokenizer::CloseFile()
{
	if( !m_FileBuffer )
		return false;

	delete m_FileBuffer;
	m_FileSize = 0;
	m_Filename[0] = 0;
	m_FileBuffer = NULL;
	m_FileSize = 0;
	m_CurrFilePos = 0;
	m_CurrFileLine = 0;
	m_LastLinePos = 0;

	m_BufferIsNextToken = false;
	m_AtEndOfLine = false;
	m_AtEndOfFile = false;

	return true;
}

bool CTokenizer::AtEndOfLine()
{
	return m_AtEndOfLine;
}

bool CTokenizer::AtEndOfFile()
{
	return m_AtEndOfFile;
}

bool CTokenizer::AtEnd()
{
	return m_AtEndOfFile||m_AtEndOfLine;
}


bool CTokenizer::IsHitComment(char c)
{
	bool hitCommentChar = false;
	int commentCharCount = sTokDefaultCommentChars ? strlen( sTokDefaultCommentChars ) : 0;
	for( int a = 0; a < commentCharCount; a++ )
	{
		if( c == sTokDefaultCommentChars[ a ] )
		{
			hitCommentChar = true;

			while( 1 )
			{
				c = m_FileBuffer[ m_CurrFilePos++ ];
				if( m_CurrFilePos >= m_FileSize )
				{
					m_AtEndOfFile = true;                        
					break;
				}                  
				if( c == '\n' )
				{
					m_CurrFileLine++;
					m_LastLinePos = m_CurrFilePos;

					m_AtEndOfLine = true;
					break;
				} 
			}
		}
	}      
	return hitCommentChar;
}

void CTokenizer::DealQuote(char** buf, char c)
{
	// if there is something already in buffer, backup and return what is already there
	if( *buf > m_Buffer )                 
	{
		// rewind file pointer by one
		m_CurrFilePos--;
	}
	else
	{
		while(1)
		{
			c = m_FileBuffer[ m_CurrFilePos++ ];                        

			if( m_CurrFilePos >= m_FileSize )
			{
				m_AtEndOfFile = true;
				break;
			}

			if( c == '\"' )
			{
				// check for end of line/end of file
				while( 1 )
				{
					c = m_FileBuffer[ m_CurrFilePos++ ];

					if( m_CurrFilePos >= m_FileSize )
					{
						m_AtEndOfFile = true;
						break;
					}

					bool hitCommentChar = IsHitComment(c);
					if( hitCommentChar )
					{
						if( *buf > m_Buffer )
							break;
					}
					else if( !isspace( c ) )
					{
						// rewind file pointer by one
						m_CurrFilePos--;
						break;
					}else{
						if( c == '\n' )
						{
							m_AtEndOfLine = true;
							m_CurrFileLine++;
							m_LastLinePos = m_CurrFilePos;
						}
					}
				}
				m_LastTokenWasQuotedString = true;
				break;
			}
			(**buf) = c;
			(*buf)++;
		}
	}
}

bool CTokenizer::DealChar(char** buf, char c)
{
	// check for operators and return them as seperate strings from other things, even if no whitespace between
	bool hitOperator = false, breakToReturnToken = false, negativeNumber = false;

	if( ( c == '-' ) && !m_ReturnNegativeSeperatelyFromNumber )
	{ 
		char nextC = m_FileBuffer[ m_CurrFilePos ];
		if( isdigit( nextC ) || ( nextC == '.' ) )
		{
			negativeNumber = true;
		}
	}

	if( !negativeNumber )
	{
		for( int a = 0; a < skTokDefaultOperatorCount; a++ )
		{
			bool prevCharsMatched = ( strlen( sTokDefaultOperators[ a ] ) > m_NumOperatorCharsRead );
			for( int b = 0; prevCharsMatched && ( b < m_NumOperatorCharsRead ); b++ )
			{
				if( m_Buffer[ b ] != ( sTokDefaultOperators[ a ] )[ b ] )
					prevCharsMatched = false;
			}

			if( prevCharsMatched && ( c == ( sTokDefaultOperators[ a ] )[ m_NumOperatorCharsRead ] ))
			{
				hitOperator = true;
				// if there is something already in buffer, backup and return what is already there
				if( !m_NumOperatorCharsRead && ( *buf > m_Buffer ))
				{
					// rewind file pointer by one
					m_CurrFilePos--;
					breakToReturnToken = true;
				}
				else
				{
					(**buf) = c;
					(*buf)++;  
					m_NumOperatorCharsRead++;                                  
				}
				break;
			}
		}
	}

	if( breakToReturnToken )
		return true;

	if( !hitOperator )
	{
		// we want to check whitespace after token to see if end of line/file bits should be set
		if( !m_NumOperatorCharsRead && !haveHitSecondWhitespace )
		{
			(**buf) = c;
			(*buf)++;
		}
		else
		{
			// rewind file pointer by one
			m_CurrFilePos--;
			return true;
		}
	}
	return false;
}

void CTokenizer::BackToken()
{
	m_CurrFilePos = m_LastFilePos;
}

const char* CTokenizer::GetToken()
{
	if( !m_BufferIsNextToken )
	{
		m_LastFilePos = m_CurrFilePos;
		if( m_AtEndOfFile || !m_FileBuffer )
			return NULL;

		m_LastTokenWasQuotedString = false;

		m_AtEndOfLine = false;
		haveHitSecondWhitespace = false;

		char* buf = m_Buffer;
		while( !m_AtEndOfFile && ( buf - m_Buffer < m_BufferSize ))
		{
			char c = m_FileBuffer[ m_CurrFilePos++ ];

			if( m_CurrFilePos >= m_FileSize )
			{
				m_AtEndOfFile = true;
				break;
			}

			// read quoted strings in literally with no processing
			if( c == '\"' )
			{
				DealQuote(&buf, c);
				break;
			}

			// skip chars after comment chars till end of line
			bool hitCommentChar = IsHitComment(c);
			if( hitCommentChar )
			{
				if( buf > m_Buffer )
					break;
			}
			else if( !isspace( c ) )
			{                
				if(DealChar(&buf, c)){
					break;
				}else{
					continue;
				}
			}
			else
			{
				if( c == '\n' )
				{
					m_AtEndOfLine = true;
					m_CurrFileLine++;
					m_LastLinePos = m_CurrFilePos;
				}
				haveHitSecondWhitespace = ( buf > m_Buffer );
			}
		}
		*buf = 0;
		m_NumOperatorCharsRead = 0;
	}

	m_BufferIsNextToken = false;
	return m_Buffer;
}

char* CTokenizer::GetPartToken()
{
	if( !GetToken() )
		return NULL;
	extern char globalStr[];
	int maxLength = 99;
	SDL_strlcpy(globalStr, m_Buffer, maxLength > m_BufferSize ? m_BufferSize : maxLength );
	globalStr[maxLength]='\0';
	return globalStr;
}

bool CTokenizer::GetToken( char* destString, int maxLength )
{
	if( !GetToken() )
		return false;

	SDL_strlcpy( destString, m_Buffer, maxLength > m_BufferSize ? m_BufferSize : maxLength );

	return true;
}


bool CTokenizer::CheckToken( const char* stringToLookFor, bool consumeIfMatch )
{
	if( !m_BufferIsNextToken )
	{
		if( !GetToken() )
			return false;
	}

	bool result = m_IsCaseSensitive ? ( SDL_strcmp( stringToLookFor, m_Buffer ) == 0 ) : ( SDL_strcasecmp( stringToLookFor, m_Buffer ) == 0 );
	m_BufferIsNextToken = consumeIfMatch ? !result : true;
	return result;    
}

bool CTokenizer::CheckToken( const char* stringToLookFor, bool consumeIfMatch, Uint32 size)
{
	if( !m_BufferIsNextToken )
	{
		if( !GetToken() )
			return false;
	}

	bool result = m_IsCaseSensitive ? ( SDL_strncmp( stringToLookFor, m_Buffer, size) == 0 ) : ( SDL_strncasecmp( stringToLookFor, m_Buffer, size) == 0 );
	m_BufferIsNextToken = consumeIfMatch ? !result : true;
	return result;    
}

float CTokenizer::GetFloat()
{
	if( !m_BufferIsNextToken )
	{
		if( !GetToken() )
			return 0.0f;
	}

	m_BufferIsNextToken = false;
	return (float)atof( m_Buffer ); 
}

int CTokenizer::GetInt()
{
	if( !m_BufferIsNextToken )
	{
		if( !GetToken() )
			return 0;
	}

	m_BufferIsNextToken = false;
	return atoi( m_Buffer ); 
}

bool CTokenizer::CheckTokenIsNumber()
{
	if( !m_BufferIsNextToken )
	{
		if( !GetToken() )
			return false;
	}

	m_BufferIsNextToken = true;

	if( m_LastTokenWasQuotedString )
		return false;

	int len = strlen( m_Buffer );
	char* c = m_Buffer;

	for( int a = 0; a < len; a++ )
	{
		if( (( *c < '0' ) || ( *c > '9' )) && ( *c != '.' ) && !( !m_ReturnNegativeSeperatelyFromNumber && ( a == 0 ) && ( *c == '-' ) && ( len > 1 ) ) )
			return false;
		c++;
	}

	return ( len > 0 );
}

bool CTokenizer::CheckTokenIsQuotedString()
{
	if( !m_BufferIsNextToken )
	{
		if( !GetToken() )
			return false;
	}

	m_BufferIsNextToken = true;
	return m_LastTokenWasQuotedString;    
}
