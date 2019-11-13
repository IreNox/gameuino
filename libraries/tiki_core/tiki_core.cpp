#include "tiki_core.h"

namespace tiki
{
	void toLower( char* pBuffer, uint8 bufferLength )
	{
		char* pBufferEnd = pBuffer + bufferLength;
		while( pBuffer != pBufferEnd && *pBuffer != '\0')
		{
			char c = *pBuffer;
			if( c >= 'A' && c <= 'Z' )
			{
				c += ('a' - 'A');
				*pBuffer = c;
			}

			pBuffer++;
		}
	}

	void toUpper( char* pBuffer, uint8 bufferLength )
	{
		char* pBufferEnd = pBuffer + bufferLength;
		while( pBuffer != pBufferEnd && *pBuffer != '\0')
		{
			char c = *pBuffer;
			if( c >= 'a' && c <= 'z' )
			{
				c -= ('a' - 'A');
				*pBuffer = c;
			}

			pBuffer++;
		}
	}
}