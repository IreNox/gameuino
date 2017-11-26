#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <third_party/stb_image.h>

namespace tiki
{
	void Image::create( size_t width, size_t height )
	{
		m_imageWidth	= (size_t)width;
		m_imageHeight	= (size_t)height;

		const size_t imageSize = m_imageWidth * m_imageHeight * 4u;
		m_imageData = std::vector< Pixel >( imageSize );
	}

	bool Image::loadImageFromFile( std::string fileName )
	{
		int x;
		int y;
		int comp;
		stbi_uc* pImage = stbi_load( fileName.c_str(), &x, &y, &comp, 4 );
		if( pImage == nullptr )
		{
			return false;
		}

		if( comp != 4 )
		{
			stbi_image_free( pImage );
			return false;
		}

		m_imageWidth	= (size_t)x;
		m_imageHeight	= (size_t)y;

		const size_t imageSize = m_imageWidth * m_imageHeight;
		const Pixel* pImagePixels = (const Pixel*)pImage;
		m_imageData = std::vector< Pixel >( pImagePixels, pImagePixels + imageSize );
		stbi_image_free( pImage );
		return true;
	}

	void Image::writeImage( std::vector< uint8_t >& targetData, ImageFormat format )
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

	void Image::writeImageStencil( std::vector< uint8_t >& targetData )
	{
		uint8_t currentBit = 0u;
		uint8_t currentByte = 0u;
		for( size_t y = 0u; y < m_imageHeight; ++y )
		{
			const Pixel* pLineSource = &m_imageData[ y * m_imageWidth ];

			for( size_t x = 0u; x < m_imageWidth; ++x )
			{
				const Pixel& pixelSource = pLineSource[ x ];

				const uint8_t pixel = (pixelSource.a != 0u);
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
