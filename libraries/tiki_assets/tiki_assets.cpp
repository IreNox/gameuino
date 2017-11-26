#include "tiki_assets.h"

namespace tiki
{
	void Assets::initialize( const void** ppAssets, uint8 assetCount )
	{
		m_ppAssets		= ppAssets;
		m_assetCount	= assetCount;
	}
	
	const void*	Assets::getAsset( AssetName asset )
	{
		return m_ppAssets[ asset ];
	}
}
