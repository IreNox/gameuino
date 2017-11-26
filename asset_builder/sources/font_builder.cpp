#include "font_builder.h"

#include "base.h"
#include "image_writer.h"

#include <iostream>

namespace tiki
{
	struct FontHeader
	{
		uint8_t	characterWidth;
		uint8_t	characterHeight;
		char	firstCharacter;
	};

	bool FontBuilder::buildAsset( std::vector< uint8_t >& targetData, const Asset& asset )
	{
		const json parameters = asset.config[ "parameters" ];

		std::path sourcePath = asset.fileName;
		sourcePath.replace_extension( ".png" );

		ImageWriter imageWriter;
		if( !imageWriter.loadImageFromFile( sourcePath.generic_string() ) )
		{
			std::cout << "Failed to load: " << sourcePath << std::endl;
			return false;
		}

		const std::string firstCharacter = parameters[ "character_first" ];

		FontHeader header;
		header.characterWidth	= parameters[ "character_width" ];
		header.characterHeight	= parameters[ "character_height" ];
		header.firstCharacter	= firstCharacter[ 0u ];
		writeBytes( targetData, &header, sizeof( header ) );

		imageWriter.writeImage( targetData, ImageFormat_Stencil );
		return true;
	}
}
