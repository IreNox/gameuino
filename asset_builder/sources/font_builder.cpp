#include "font_builder.h"

#include "base.h"
#include "image.h"

#include <iostream>

namespace tiki
{
	struct FontHeader
	{
		uint8_t	characterWidth;
		uint8_t	characterHeight;
		char	firstCharacter;
		char	lastCharacter;
	};

	bool FontBuilder::buildAsset( std::vector< uint8_t >& targetData, const Asset& asset )
	{
		const json parameters				= asset.config[ "parameters" ];
		const std::string firstCharacter	= parameters[ "character_first" ];
		const std::string lastCharacter		= parameters[ "character_last" ];

		FontHeader header;
		header.characterWidth	= parameters[ "character_width" ];
		header.characterHeight	= parameters[ "character_height" ];
		header.firstCharacter	= firstCharacter[ 0u ];
		header.lastCharacter	= lastCharacter[ 0u ];
		writeBytes( targetData, &header, sizeof( header ) );

		std::path sourcePath = asset.fileName;
		sourcePath.replace_extension( ".png" );

		Image sourceImage;
		if( !sourceImage.loadImageFromFile( sourcePath.generic_string() ) )
		{
			std::cout << "Failed to load: " << sourcePath << std::endl;
			return false;
		}

		Image targetImage;
		const size_t characterCount	= header.lastCharacter - header.firstCharacter + 1u;
		const size_t characterSize	= header.characterWidth * header.characterHeight;
		targetImage.create( characterSize, characterCount );

		const size_t charactersInWidth	= sourceImage.getWidth() / header.characterWidth;
		for( size_t charIndex = 0u; charIndex < characterCount; ++charIndex )
		{
			const size_t charBaseX	= (charIndex % charactersInWidth) * header.characterWidth;
			const size_t charBaseY	= (charIndex / charactersInWidth) * header.characterHeight;

			for( size_t c = 0u; c < characterSize; ++c )
			{
				const size_t cx = charBaseX + (c % header.characterWidth);
				const size_t cy = charBaseY + (c / header.characterWidth);
				targetImage.getPixel( c, charIndex ) = sourceImage.getPixel( cx, cy );
			}
		}

		targetImage.writeImage( targetData, ImageFormat_Stencil );
		return true;
	}
}
