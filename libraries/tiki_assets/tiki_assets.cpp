#include "tiki_assets.h"

namespace tiki
{
	void Assets::initialize( const Asset* pAssets, uint8 assetCount )
	{
		m_pAssets		= pAssets;
		m_assetCount	= assetCount;
	}

	const uint8* Assets::getAsset( AssetName assetName )
	{
		const Asset& asset = m_pAssets[ assetName ];
		return asset.pData;
	}

	const uint8* Assets::loadAsset( AssetName assetName )
	{
		const Asset& asset = m_pAssets[ assetName ];

		memcpy_P( m_assetData, asset.pData, asset.dataSize );

		return m_assetData;
	}
}
