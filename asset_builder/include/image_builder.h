#pragma once

#include "builder.h"

namespace tiki
{
	class ImageBuilder : public Builder
	{
	public:

		virtual bool buildAsset( std::vector< uint8_t >& targetData, const Asset& asset ) override final;
	};
}