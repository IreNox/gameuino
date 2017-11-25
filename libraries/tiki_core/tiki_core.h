#pragma once

#include <Arduino.h>

namespace tiki
{
	typedef uint8_t		uint8;
	typedef uint16_t	uint16;
	typedef uint32_t	uint32;
	typedef uint64_t	uint64;
	typedef int8_t		sint8;
	typedef int16_t		sint16;
	typedef int32_t		sint32;
	typedef int64_t		sint64;

	struct uint28
	{
		uint8	x;
		uint8	y;
	};

	typedef uint28 Point;

	struct Rectangle
	{
		uint28	pos;
		uint28	size;

		bool contains( const Point& point )
		{
			return point.x >= pos.x &&
				   point.y >= pos.y &&
				   point.x < pos.x + size.x &&
				   point.y < pos.y + size.y;
		}

		bool intersect( const Rectangle& rect )
		{
			return !(rect.pos.x > pos.x + size.x || 
				   rect.pos.x + rect.size.x < pos.x || 
				   rect.pos.y > pos.y + size.y ||
				   rect.pos.y + rect.size.y < pos.y);

		}
	};
}