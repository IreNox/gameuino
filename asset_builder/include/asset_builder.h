#pragma once

#include "font_builder.h"
#include "image_builder.h"

namespace tiki
{
	class AssetBuilder
	{
	public:

											AssetBuilder();

		bool								buildProject( std::string projectPath, std::string outputPath );

	private:

		FontBuilder							m_fontBuilder;
		ImageBuilder						m_imageBuilder;
		std::map< std::string, Builder* >	m_builders;

		std::vector< Asset >				m_assets;
		std::vector< uint8_t >				m_workingData;

		bool								loadAssets( std::string projectPath );
		bool								buildAssets();
		void								writeAssets();
		bool								writeNameHeader( std::string outputPath );
		bool								writeDataHeader( std::string outputPath );

		void								writeBytes( const void* pData, size_t length );
	};
}
