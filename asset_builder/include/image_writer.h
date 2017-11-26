#pragma once

#include <string>
#include <vector>

namespace tiki
{
	enum ImageFormat
	{
		ImageFormat_Stencil,
		ImageFormat_Monochrome,
		ImageFormat_RGB444,
		ImageFormat_RGB565,
		ImageFormat_RGB666,
	};

	class ImageWriter
	{
	public:

		bool					loadImageFromFile( std::string fileName );
		void					writeImage( std::vector< uint8_t >& targetData, ImageFormat format );

	private:

		size_t					m_imageWidth;
		size_t					m_imageHeight;
		std::vector< uint8_t >	m_imageData;

		void					writeImageStencil( std::vector< uint8_t >& targetData );
	};
}
