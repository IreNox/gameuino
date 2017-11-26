#pragma once

#include <cctype>
#include <vector>

namespace tiki
{
	inline void writeBytes( std::vector< uint8_t >& targetData, const void* pData, size_t length )
	{
		const  uint8_t* pBytes = static_cast<const uint8_t*>(pData);
		for( size_t i = 0u; i < length; ++i )
		{
			targetData.push_back( pBytes[ i ] );
		}
	}

	inline std::string getCamelCaseString( std::string input )
	{
		std::string output;

		bool toUpper = true;
		for( char c : input )
		{
			if( c == '_' || c == ' ' || c == '-' )
			{
				toUpper = true;
				continue;
			}

			if( toUpper )
			{
				c = std::toupper( c );
				toUpper = false;
			}


			output.push_back( c );
		}

		return output;
	}
}