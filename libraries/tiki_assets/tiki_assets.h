#pragma once

#include "tiki_core.h"

namespace tiki
{
	enum AssetName : uint8;

	static const uint16 s_assetMaxSize = 1024u;

	class Assets
	{
	public:

		void			initialize( const Asset* pAssets, uint8 assetCount );

		const uint8*	getAsset( AssetName assetName );
		const uint8*	loadAsset( AssetName assetName );

	private:

		const Asset*	m_pAssets;
		uint8			m_assetCount;

		uint8			m_assetData[ s_assetMaxSize ];
	};
}