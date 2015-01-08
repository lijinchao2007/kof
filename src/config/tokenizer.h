/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/
#ifndef __OM_TOKENIZER__
#define __OM_TOKENIZER__

#include <map>
#include <string>
#include "define.h"


class CTokenizer
{
public:
    CTokenizer( int bufferSize = 256);
    ~CTokenizer();
    
    bool OpenFile( const char* filename ); // false if already open file or on fail
    bool CloseFile();                      // false if no file open
    
    bool AtEndOfLine();
    bool AtEndOfFile();
    bool AtEnd();   

	bool IsHitComment(char c);
	void DealQuote(char** buf, char c);
	bool DealChar(char** buf, char c);
	char* GetPartToken();
	void BackToken();
    const char* GetToken();
    bool        GetToken( char* destString, int maxLength );
    bool        CheckToken( const char* stringToLookFor, bool consumeIfMatch = true );
	// 指定匹配，用于trigger
	bool		CheckToken( const char* stringToLookFor, bool consumeIfMatch, Uint32 size);
    bool        CheckTokenIsNumber();       // returns true if token is a number
    bool        CheckTokenIsQuotedString();  // makes sure token is quoted string
    
    int         GetInt();
    float       GetFloat();
    
    void        SetIsCaseSensitive( bool b )  { m_IsCaseSensitive = b; }
    void        SetReturnNegativeSeperatelyFromNumber( bool b )  { m_ReturnNegativeSeperatelyFromNumber = b; }
    
    const char* GetFileName()       { return m_Filename; }
    int         GetLineNumber()     { return m_CurrFileLine; }
    int         GetColumnNumber()   { return m_CurrFilePos - m_LastLinePos; }
          
protected:     
    char*   m_Buffer;   
    int     m_BufferSize;

    char    m_Filename[MAX_PATH];
    char*   m_FileBuffer;
    int     m_FileSize;
	int     m_LastFilePos;
	int     m_CurrFilePos;
    int     m_CurrFileLine;
    int     m_LastLinePos;

    bool    m_BufferIsNextToken, m_AtEndOfLine, m_AtEndOfFile;
    Uint32     m_NumOperatorCharsRead;
    
    bool    m_IsCaseSensitive;
    bool    m_ReturnNegativeSeperatelyFromNumber;
    bool    m_LastTokenWasQuotedString;

	bool	haveHitSecondWhitespace;
};

//Tokenizer by Nate Pendelton
void ParseWarning(CTokenizer &tok, const char *fmt, ...);
bool Common_ParseSection(CTokenizer &tok, std::map<std::string, std::string>& dict); 

#endif
