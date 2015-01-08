/******************************************************************************* 
author : ljc
version : <1.0> 
-------------------------------------------------------------------------------- 
info : 
-------------------------------------------------------------------------------- 
*******************************************************************************/

#include "AirManager.h"
#include "tool.h"
#include "tokenizer.h"

CAirManager::CAirManager()
{


}

CAirManager::~CAirManager()
{
}

void CAirManager::SetAlloc(const char *alloName)
{
	CAirBaseConfig::SetAlloc(CMemManager::GetInstance()->GetAllocater(alloName));
}

void CAirManager::ParseFile(const char *strFileName)
{
	PrintMessage("ParseFile %s ", strFileName);
	SetAlloc(strFileName);
	Reset();

	CTokenizer tok;
	if( !tok.OpenFile( strFileName ) )
	{
		throw(CError("CAirManager::ParseFile : Can't open %s",strFileName));
		return;
	}

	tok.SetIsCaseSensitive(false);

	while( !tok.AtEndOfFile() )
	{
		int actionNum = -1;
		if( tok.CheckToken( "[" ) )
		{
			if( !tok.CheckToken( "Begin" ) )
			{
			}

			if( !tok.CheckToken( "Action" ) )
			{
			}                    

			if( !tok.CheckTokenIsNumber() )
			{
			}

			actionNum = tok.GetInt();
			if( !tok.CheckToken( "]" ) )
			{
			}

			//PrintMessage("actionNum %d", actionNum);
			AddAction( actionNum );       
		}
		else if( tok.CheckToken( "Clsn1Default", false ) || tok.CheckToken( "Clsn2Default", false ) || tok.CheckToken( "Clsn1", false ) || tok.CheckToken( "Clsn2", false ) )
		{
			char token[MAX_PATH];
			tok.GetToken(token, MAX_PATH);
			//const char* token = tok.GetToken();
			bool isClsn1 = ( token[ 4 ] == '1' );
			bool isDefault = ( strlen( token ) > 7 );

			if( !tok.CheckToken(":") )
			{
				Error("need :", tok);
			}

			int clsnBoxCount = tok.GetInt();
			CreateClsnBox( clsnBoxCount, isClsn1, isDefault );

			
			for( int c = 0; c < clsnBoxCount; c++ )
			{
				if( !( tok.CheckToken( "Clsn1" ) || tok.CheckToken( "Clsn2" ) )) // for some reason kfm uses clsn2 sometimes in clsn1 items
				{
					Error("need Clsn", tok);
				}

				if( !tok.CheckToken( "[" ) )
				{
					Error("need [", tok);
				}

				if( tok.GetInt() != c )
				{
				}

				if( !tok.CheckToken( "]" ) )
				{
					Error("need ]", tok);
				}

				if( !tok.CheckToken( "=" ) )
				{
					Error("need =", tok);
				}

				int coor[4];
				for( int i = 0; i < 4; i++ )
				{
					if( !tok.CheckTokenIsNumber() )
					{
						Error("need num", tok);
					}

					coor[i] = tok.GetInt();

					if( i < 3 )
					{
						if( !tok.CheckToken( "," ) )
						{
							Error("need ,", tok);
						}
					}
				}

				AddClsnBox( coor[0], coor[1], coor[2], coor[3], c ); 
			}
		}
		else if( tok.CheckToken( "Loopstart" ) )
		{
			SetLoop();
		}
		else if( tok.CheckTokenIsNumber() )
		{
			int values[5];
			for( int v = 0; v < 5; v++ )
			{
				if( !tok.CheckTokenIsNumber() )
				{
					Error("need num", tok);
				}

				values[ v ] = tok.GetInt();

				
				if( v < 4 )
				{
					if( !tok.CheckToken( "," ) )
					{
						Error("need ,", tok);
					}
				}
			}

			SDL_RendererFlip flipFlag = SDL_FLIP_NONE;

			if( tok.CheckToken( "," ) )
			{
				if( tok.CheckToken( "H" ) )
				{
					flipFlag = SDL_FLIP_HORIZONTAL;
				}
				else if( tok.CheckToken( "V" ) )
				{
					flipFlag = SDL_FLIP_VERTICAL;
				}
				else if( tok.CheckToken( "VH" ) || tok.CheckToken( "HV" ) )
				{
					flipFlag = (SDL_RendererFlip)(SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL);
				}
				else if( !tok.CheckToken( ",", false ) )
				{
				}
			}

			const char* TransType = NULL;
			if( tok.CheckToken( "," )&&!tok.AtEndOfLine() )
			{
				TransType = tok.GetToken(); // alpha param
			}

			AddElement( values[0], values[1], values[2], values[3], values[4], flipFlag, TransType);
			AddClsnToElement();
		}
		else
		{
			GET_ALL_LINE_TOKEN(tok);
		}
	}  
	ReAllocMem();
	tok.CloseFile();
}

