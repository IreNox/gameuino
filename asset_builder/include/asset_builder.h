#pragma once

#include "font_builder.h"

namespace tiki
{
	class AssetBuilder
	{
	public:

											AssetBuilder();

		bool								buildProject( std::string projectJsonFile, std::string outputPath );

	private:

		FontBuilder							m_fontBuilder;
		std::map< std::string, Builder* >	m_builders;

		std::vector< Asset >				m_assets;
		std::vector< uint8_t >				m_workingData;

		bool								loadAssets( std::string projectJsonFile );
		bool								buildAssets();
		void								writeAssets();
		bool								writeNameHeader( std::string outputPath );
		bool								writeDataHeader( std::string outputPath );

		void								writeBytes( const void* pData, size_t length );
	};
}
