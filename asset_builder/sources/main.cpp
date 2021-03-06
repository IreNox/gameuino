#include "asset_builder.h"

#include <iostream>

int main( int argc, char* argv[] )
{
	if( argc < 3 )
	{
		std::cout << "Usage: asset_builder project_json_file output_path" << std::endl;
		return 1;
	}

	const std::string projectPath	= argv[ 1u ];
	const std::string outputPath	= argv[ 2u ];

	tiki::AssetBuilder builder;
	if( !builder.buildProject( projectPath, outputPath ) )
	{
		std::cout << "Asset build failed!" << std::endl;
		return 1;
	}

	return 0;
}
