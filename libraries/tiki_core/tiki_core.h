#pragma once

#include <Arduino.h>

#define TIKI_ON 				2
#define TIKI_OFF				1

#define TIKI_ENABLED( value )	( ( 0 + value ) == 2 )
#define TIKI_DISABLED( value )	( ( 0 + value ) != 2 )

#define TIKI_DEBUG				TIKI_ON

#define TIKI_FORCE_INLINE		__attribute__((always_inline))
#define TIKI_PROGRAM_MEMORY		PROGMEM

#if defined(__AVR__) // AVR (UNO, Duemilanove, etc.)
#	define TIKI_AVR				TIKI_ON
#else
#	define TIKI_AVR				TIKI_OFF
#endif

#if defined(__SAM3X8E__) // ARM (DUE)
#	define TIKI_ARM_DUE			TIKI_ON
#else
#	define TIKI_ARM_DUE			TIKI_OFF
#endif

#if TIKI_ENABLED( TIKI_DEBUG )
#	define TIKI_TRACE( ... )	Serial.println( __VA_ARGS__ )
#	define TIKI_ASSERT( exp )	if( !(exp) ) Serial.println( #exp )
#else
#	define TIKI_TRACE( ... )
#	define TIKI_ASSERT( exp )
#endif

namespace tiki
{
	typedef uint8_t			uint8;
	typedef uint16_t		uint16;
	typedef uint32_t		uint32;
	typedef uint64_t		uint64;
	typedef int8_t			sint8;
	typedef int16_t			sint16;
	typedef int32_t			sint32;
	typedef int64_t			sint64;

#if TIKI_ENABLED( TIKI_AVR )
	typedef uint8			ruint;
	typedef volatile uint8	rtype;
#elif TIKI_ENABLED( TIKI_ARM_DUE )
	typedef uint32			ruint;
	typedef Pio				rtype;
#endif

	struct Asset
	{
		const uint8*	pData;
		uint16			dataSize;
	};

	struct uint8x2
	{
		uint8	x;
		uint8	y;
	};

	struct sint8x2
	{
		sint8	x;
		sint8	y;
	};

	typedef uint8x2 Point;

	struct Rectangle
	{
		uint8x2	pos;
		uint8x2	size;

		Rectangle()
		{
		}

		Rectangle( uint8 x, uint8 y, uint8 width, uint8 height )
		{
			pos.x	= x;
			pos.y	= y;
			size.x	= width;
			size.y	= height;
		}

		bool contains( const Point& point ) const
		{
			return point.x >= pos.x &&
				   point.y >= pos.y &&
				   point.x < pos.x + size.x &&
				   point.y < pos.y + size.y;
		}

		bool intersect( const Rectangle& rect ) const
		{
			return !(rect.pos.x > pos.x + size.x ||
				   rect.pos.x + rect.size.x < pos.x ||
				   rect.pos.y > pos.y + size.y ||
				   rect.pos.y + rect.size.y < pos.y);
		}

		template<typename T>
		TIKI_FORCE_INLINE bool isPowerOfTwo( T x )
		{
			return ( x & ( x - 1 ) ) == 0;
		}

		template<typename T>
		TIKI_FORCE_INLINE T alignValue( T value, T alignment )
		{
			//TIKI_ASSERT( alignment > 0 );
			//TIKI_ASSERT( isPowerOfTwo( alignment ) );
			return ( value + alignment - 1 ) & ( 0 - alignment );
		}
	};

	struct BoundingRectangle
	{
		uint8x2	min;
		uint8x2	max;
	};

	void toLower( char* pBuffer, uint8 bufferLength );
	void toUpper( char* pBuffer, uint8 bufferLength );
}