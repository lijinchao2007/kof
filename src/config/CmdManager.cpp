/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "CmdManager.h"
#include "tool.h"
#include "tokenizer.h"

CCmdManager::CCmdManager()
{
    m_Commands = NULL;
    m_CommandCount = 0;
}

CCmdManager::~CCmdManager()
{
    delete []m_Commands;
}

bool CCmdManager::LoadCMDFile( const char* file)
{
	PrintMessage("LoadCMDFile file %s ", file);
    int defaultCommandTime = 15;
    int defaultBufferTime = 1;
    
    m_CommandCount = 0;

    CTokenizer tok;
    //changed this to throw a exception
    if( !tok.OpenFile( file ) )
    {
        throw(CError("CCmdManager::LoadCMDFile : Can't open %s",file));
        return false;
    }
    tok.SetIsCaseSensitive(false);   
    // get count first to set up memory        
    while( !tok.AtEndOfFile() )
    {
        bool foundSomething = false;
        if( tok.CheckToken( "command.time" ) )
        {
            foundSomething = true;
            if( !tok.CheckToken( "=" ) )
            {
            }
            if( tok.CheckTokenIsNumber() )
            {
                defaultCommandTime = tok.GetInt();
            }            
        }
        
        if( tok.CheckToken( "command.buffer.time" ) )
        {
            foundSomething = true;
            if( !tok.CheckToken( "=" ) )
            {
            }
            if( tok.CheckTokenIsNumber() )
            {
                defaultBufferTime = tok.GetInt();
            }
        }
        
        if( tok.CheckToken( "[" ) )
        {
            foundSomething = true;
            if( tok.CheckToken( "Command" ) )
            {
                if( tok.CheckToken( "]" ) )
                {
                    m_CommandCount++;
                }       
            }
        }        
        if( !foundSomething )
        {
            tok.GetToken(); // skip it
        }
    }
        
    tok.CloseFile();
 
    if( !tok.OpenFile( file ) )
	{
		throw(CError("LoadCMDFile: File %s not found",file));
        return false;
	}
    m_Commands = new PLCOMMAND[ m_CommandCount ];
    PLCOMMAND* command = m_Commands;
    
    while( !tok.AtEndOfFile() )
    {
        bool foundCommand = false;
        if( tok.CheckToken( "[" ) )
        {
            if( tok.CheckToken( "Command" ) )
            {
                if( !tok.CheckToken( "]" ) )
                {
                }
                
                foundCommand = true;
                command->nCommandTime = defaultCommandTime;
                command->nBufferTime = defaultBufferTime;
                command->strCommand[0] = 0;
                command->nHowManyCommand = 0;
                
                while( command->nHowManyCommand < MAXCOMMAND && !tok.CheckToken( "[", false ) && !tok.AtEndOfFile() )
                {
                    if( tok.CheckToken( "name" )||tok.CheckToken( "Name" ) )
                    {
                        if( !tok.CheckToken( "=" ) )
                        {
                        }
                        
                        SDL_strlcpy( command->strCommand, tok.GetToken(), MAX_PATH);                    
                    }
                    else if( tok.CheckToken( "command" )||tok.CheckToken( "Command" ) )
                    {
                        if( !tok.CheckToken( "=" ) )
                        {
                        } 
                        
                        while( !tok.AtEndOfLine() )
                        {
                            const char* token = tok.GetToken();
                           
                            if( !strcmp( token, "~" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyModifier += PLC_KEYMOD_ON_RELEASE;
                                if( tok.CheckTokenIsNumber() )
                                {
                                    command->nCommand[ command->nHowManyCommand ].gameTicksForHold = tok.GetInt();
                                }
                                else
                                {
                                    command->nCommand[ command->nHowManyCommand ].gameTicksForHold = 1;
                                }
                            }
                            else if( !strcmp( token, "+" ) )
                            {
                            }
                            else if( !strcmp( token, "/" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyModifier += PLC_KEYMOD_MUST_BE_HELD;
                            }
                            else if( !strcmp( token, "$" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyModifier += PLC_KEYMOD_DETECT_AS_4WAY;
                            }
                            else if( !strcmp( token, ">" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyModifier += PLC_KEYMOD_BAN_OTHER_INPUT;
                            }
                            else if( !strcmp( token, "," ) )
                            {
                                command->nHowManyCommand++;
                            }                            
                            else if( !strcmp( token, "D" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_DOWN );
                            }
                            else if( !strcmp( token, "U" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_UP );
                            }
                            else if( !strcmp( token, "B" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_LEFT );
                            }
                            else if( !strcmp( token, "F" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_RIGHT );
                            }
                            else if( !strcmp( token, "DB" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_DOWN ) + PLC_KEYCODE( KEY_LEFT );
                            }
                            else if( !strcmp( token, "DF" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_DOWN ) + PLC_KEYCODE( KEY_RIGHT );
                            }
                            else if( !strcmp( token, "UF" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_UP ) + PLC_KEYCODE( KEY_LEFT );
                            }
                            else if( !strcmp( token, "UB" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_UP ) + PLC_KEYCODE( KEY_LEFT );
                            }
                            else if( !strcmp( token, "a" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_A );
                            }
                            else if( !strcmp( token, "b" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_B );
                            }
                            else if( !strcmp( token, "c" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_C );
                            }
                            else if( !strcmp( token, "x" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_X );
                            }
                            else if( !strcmp( token, "y" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_Y );
                            }
                            else if( !strcmp( token, "z" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_Z );
                            }
                            else if( !strcmp( token, "s" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_START );
                            }
                        }
                        command->nHowManyCommand++;
                    }
                    else if( tok.CheckToken( "time" ) || tok.CheckToken( "Time" ) )
                    {
                        if( !tok.CheckToken( "=" ) )
                        {
                        } 
                        
                        if( !tok.CheckTokenIsNumber() )
                        {
                        }
                        
                        command->nCommandTime = tok.GetInt();
                    }
                    else if( tok.CheckToken( "buffer.time" ) )
                    {
                        if( !tok.CheckToken( "=" ) )
                        {
                        } 
                        
                        if( !tok.CheckTokenIsNumber() )
                        {
                        }
                        
                        command->nBufferTime = tok.GetInt();
                    }else{
						GET_ALL_LINE_TOKEN(tok);
					}
                }
                                
                command++;                
            }
        } 
        if( !foundCommand )
            tok.GetToken(); // skip it
    }
 
    tok.CloseFile();
    return true;
}



