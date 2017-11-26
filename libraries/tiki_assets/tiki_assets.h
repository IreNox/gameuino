#pragma once

#include "tiki_core.h"

namespace tiki
{
	enum AssetName : uint8;

	class Assets
	{
	public:

		void		initialize( const void** ppAssets, uint8 assetCount );

		const void*	getAsset( AssetName asset );

	private:

		const void**	m_ppAssets;
		uint8			m_assetCount;
	};
}