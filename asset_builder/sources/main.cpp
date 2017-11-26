#include "asset_builder.h"

#include <iostream>

int main( int argc, char* argv[] )
{
	if( argc < 3 )
	{
		std::cout << "Usage: asset_builder project_json_file output_header_file" << std::endl;
		return 1;
	}

	const std::string projectJsonFile	= argv[ 1u ];
	const std::string outputHeaderFile	= argv[ 2u ];

	tiki::AssetBuilder builder;
	if( builder.buildProject( projectJsonFile, outputHeaderFile ) )
	{
		std::cout << "Asset build failed!" << std::endl;
		return 1;
	}

	return 0;
}
