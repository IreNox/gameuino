#include "image_builder.h"

#include "base.h"
#include "image.h"

#include <cctype>
#include <iostream>

namespace tiki
{
	struct ImageHeader
	{
		uint8_t	width;
		uint8_t	height;
		uint8_t	format;
	};

	bool ImageBuilder::buildAsset( std::vector< uint8_t >& targetData, const Asset& asset )
	{
		const json parameters		= asset.config[ "parameters" ];
		std::string formatString	= parameters[ "format" ];
		std::transform( formatString.begin(), formatString.end(), formatString.begin(), ::tolower );

		std::path sourcePath = asset.fileName;
		sourcePath.replace_extension( ".png" );

		Image sourceImage;
		if( !sourceImage.loadImageFromFile( sourcePath.generic_string() ) )
		{
			std::cout << "Failed to load: " << sourcePath << std::endl;
			return false;
		}

		ImageFormat format;
		if( formatString == "stencil" )
		{
			format = ImageFormat_Stencil;
		}
		else if( formatString == "monochrome" )
		{
			format = ImageFormat_Stencil;
		}
		//else if( formatString == "rgb444" )
		//{
		//	format = ImageFormat_Rgb444;
		//}
		else if( formatString == "rgb565" )
		{
			format = ImageFormat_Rgb565;
		}
		//else if( formatString == "rgb666" )
		//{
		//	format = ImageFormat_Rgb666;
		//}
		else
		{
			std::cout << "Invalid format parameter: " << formatString << std::endl;
			return false;
		}

		ImageHeader header;
		header.width	= (uint8_t)sourceImage.getWidth();
		header.height	= (uint8_t)sourceImage.getHeight();
		header.format	= format;

		writeBytes( targetData, &header, sizeof( header ) );
		sourceImage.writeImage( targetData, format );
		return true;
	}

}
