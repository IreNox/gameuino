#include "image_writer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <third_party/stb_image.h>

namespace tiki
{
	bool ImageWriter::loadImageFromFile( std::string fileName )
	{
		int x;
		int y;
		int comp;
		stbi_uc* pImage = stbi_load( fileName.c_str(), &x, &y, &comp, 4 );
		if( pImage == nullptr )
		{
			return false;
		}

		m_imageWidth	= (size_t)x;
		m_imageHeight	= (size_t)y;

		const size_t imageSize = x * y * comp;
		m_imageData = std::vector< uint8_t >( pImage, pImage + imageSize - 1 );
		stbi_image_free( pImage );
		return true;
	}

	void ImageWriter::writeImage( std::vector<uint8_t>& targetData, ImageFormat format )
	{
		switch( format )
		{
		case ImageFormat_Stencil:
			writeImageStencil( targetData );
			break;

		case ImageFormat_Monochrome:
			break;

		case ImageFormat_RGB444:
			break;

		case ImageFormat_RGB565:
			break;

		case ImageFormat_RGB666:
			break;

		default:
			break;
		}
	}

	void ImageWriter::writeImageStencil( std::vector< uint8_t >& targetData )
	{
		uint8_t currentBit = 0u;
		uint8_t currentByte = 0u;
		for( size_t y = 0u; y < m_imageHeight; ++y )
		{
			const uint8_t* pLineSource = &m_imageData[ y * m_imageWidth * 4u ];

			for( size_t x = 0u; x < m_imageWidth; ++x )
			{
				const uint8_t* pPixelSource = &pLineSource[ x * 4u ];

				const uint8_t pixel = (pPixelSource[ 3u ] != 0u);
				currentByte |= pixel << currentBit;

				currentBit++;
				if( currentBit == 8u )
				{
					targetData.push_back( currentByte );
					currentBit	= 0u;
					currentByte	= 0u;
				}
			}
		}
	}
}
