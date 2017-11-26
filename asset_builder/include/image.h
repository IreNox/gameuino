#pragma once

#include <string>
#include <vector>

namespace tiki
{
	enum ImageFormat
	{
		ImageFormat_Stencil,
		ImageFormat_Monochrome,
		ImageFormat_Rgb444,
		ImageFormat_Rgb565,
		ImageFormat_Rgb666,
		ImageFormat_Rgba5551,
	};

	struct Pixel
	{
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
		uint8_t	a;
	};

	class Image
	{
	public:

		void					create( size_t width, size_t height );
		bool					loadImageFromFile( std::string fileName );

		size_t					getWidth() const { return m_imageWidth; }
		size_t					getHeight() const { return m_imageHeight; }
		Pixel&					getPixel( size_t x, size_t y ) { return m_imageData[ x + (y * m_imageWidth) ]; }

		void					writeImage( std::vector< uint8_t >& targetData, ImageFormat format );

	private:

		size_t					m_imageWidth;
		size_t					m_imageHeight;
		std::vector< Pixel >	m_imageData;

		void					writeImageStencil( std::vector< uint8_t >& targetData );
		void					writeImageRgb565( std::vector< uint8_t >& targetData );
	};
}
