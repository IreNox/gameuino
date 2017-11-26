#include "image.h"

#include "base.h"

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

		if( comp < 3 )
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

		case ImageFormat_Rgb444:
			break;

		case ImageFormat_Rgb565:
			writeImageRgb565( targetData );
			break;

		case ImageFormat_Rgb666:
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
				const Pixel& sourcePixel = pLineSource[ x ];

				const uint8_t pixel = (sourcePixel.a != 0u);
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

	void Image::writeImageRgb565( std::vector< uint8_t >& targetData )
	{
		for( size_t y = 0u; y < m_imageHeight; ++y )
		{
			const Pixel* pLineSource = &m_imageData[ y * m_imageWidth ];

			for( size_t x = 0u; x < m_imageWidth; ++x )
			{
				const Pixel& sourcePixel = pLineSource[ x ];

				const uint16_t r = sourcePixel.r;
				const uint16_t g = sourcePixel.g;
				const uint16_t b = sourcePixel.b;

				const uint16_t r5 = ((r >> 3) & 0x1f) << 11;
				const uint16_t g6 = ((g >> 2) & 0x3f) << 5;
				const uint16_t b5 = ((b >> 3) & 0x1f);
				const uint16_t c = r5 | g6 | b5;

				writeBytes( targetData, &c, sizeof( c ) );
			}
		}
	}
}
