#pragma once

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
}