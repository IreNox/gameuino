#include "asset_builder.h"

#include "base.h"

#include <fstream>
#include <iostream>

namespace tiki
{
	AssetBuilder::AssetBuilder()
	{
		m_builders =
		{
			{ "image", &m_imageBuilder },
			{ "font", &m_fontBuilder }
		};
	}

	bool AssetBuilder::buildProject( std::string projectPath, std::string outputPath )
	{
		if( !loadAssets( projectPath ) )
		{
			return false;
		}

		if( !buildAssets() )
		{
			return false;
		}

		writeAssets();

		return writeNameHeader( outputPath ) && writeDataHeader( outputPath );
	}

	bool AssetBuilder::loadAssets( std::string projectPath )
	{
		std::path projectJsonFile = projectPath;
		projectJsonFile.append( "assets.json" );

		json projectJson;
		{
			std::ifstream file( projectJsonFile );
			if( !file.is_open() )
			{
				std::cout << "Failed to open: " << projectJsonFile << std::endl;
				return false;
			}
			file >> projectJson;
		}

		for( const json& asset : projectJson[ "assets" ] )
		{
			const std::string assetEntry = asset;

			std::path assetPath = projectPath;
			assetPath.append( assetEntry );

			Asset asset;
			asset.name = assetPath.filename().generic_string();

			assetPath.replace_extension( ".json" );
			asset.fileName = assetPath.generic_string();

			{
				std::ifstream file( assetPath );
				if( !file.is_open() )
				{
					std::cout << "Failed to open: " << assetPath << std::endl;
					return false;
				}
				file >> asset.config;
			}

			const std::string type = asset.config[ "type" ];
			asset.type = type;

			m_assets.push_back( asset );
		}

		return true;
	}

	bool AssetBuilder::buildAssets()
	{
		for( Asset& asset : m_assets )
		{
			Builder* pBuilder = m_builders[ asset.type ];
			if( pBuilder == nullptr )
			{
				std::cout << "No builder for: " << asset.fileName << std::endl;
				return false;
			}

			if( !pBuilder->buildAsset( asset.data, asset ) )
			{
				std::cout << "Failed to build: " << asset.fileName << std::endl;
				return false;
			}
		}

		return true;
	}

	void AssetBuilder::writeAssets()
	{
		size_t currentOffset = 0u;
		for( Asset& asset : m_assets )
		{
			asset.dataOffset = currentOffset;
			currentOffset += asset.data.size();

			writeBytes( asset.data.data(), asset.data.size() );
		}
	}

	bool AssetBuilder::writeNameHeader( std::string outputPath )
	{
		std::path nameHeaderFile = outputPath;
		nameHeaderFile.append( "assets.h" );

		std::ofstream file( nameHeaderFile );
		if( !file.is_open() )
		{
			std::cout << "Failed to open: " << nameHeaderFile << std::endl;
			return false;
		}

		file << "#pragma once" << std::endl;
		file << std::endl;
		file << "#include \"tiki_core.h\"" << std::endl;
		file << std::endl;
		file << "namespace tiki" << std::endl;
		file << "{" << std::endl;

		file << "\tenum AssetName : uint8" << std::endl;
		file << "\t{" << std::endl;
		for( const Asset& asset : m_assets )
		{
			file << "\t\tAssetName_" << getCamelCaseString( asset.name ) << ", " << std::endl;
		}
		file << std::endl;
		file << "\t\tAssetName_Count" << std::endl;
		file << "\t};" << std::endl;
		file << "}" << std::endl;
		file << std::endl;

		return true;
	}

	bool AssetBuilder::writeDataHeader( std::string outputPath )
	{
		std::path dataHeaderFile = outputPath;
		dataHeaderFile.append( "asset_data.h" );

		std::ofstream file( dataHeaderFile );
		if( !file.is_open() )
		{
			std::cout << "Failed to open: " << dataHeaderFile << std::endl;
			return false;
		}

		file << "#pragma once" << std::endl;
		file << std::endl;
		file << "#include \"assets.h\"" << std::endl;
		file << std::endl;
		file << "namespace tiki" << std::endl;
		file << "{" << std::endl;
		file << "\tstatic const uint8 s_assetData[] TIKI_PROGRAM_MEMORY =" << std::endl;
		file << "\t{" << std::endl;
		file << "\t\t";

		size_t lineIndex = 0u;
		for( uint8_t byte : m_workingData )
		{
			char byseBuffer[ 16u ];
			snprintf( byseBuffer, sizeof( byseBuffer ), "0x%02xu, ", byte );
			file << byseBuffer;

			lineIndex++;
			if( lineIndex == 16u )
			{
				lineIndex = 0u;
				file << std::endl << "\t\t";
			}
		}
		file << std::endl;
		file << "\t};" << std::endl;

		file << std::endl;

		file << "\tstatic const Asset s_assets[] =" << std::endl;
		file << "\t{" << std::endl;
		for( const Asset& asset : m_assets )
		{
			char sizeBuffer[ 16u ];
			char offsetBuffer[ 16u ];
			snprintf( sizeBuffer, sizeof( sizeBuffer ), "0x%04xu", asset.data.size() );
			snprintf( offsetBuffer, sizeof( offsetBuffer ), "0x%04xu", asset.dataOffset );

			file << "\t\t{ s_assetData + " << offsetBuffer << ", " << sizeBuffer << " }, // AssetName_" << getCamelCaseString( asset.name ) << std::endl;
		}
		file << "\t};" << std::endl;


		file << "}" << std::endl;
		file << std::endl;

		return true;
	}

	void AssetBuilder::writeBytes( const void* pData, size_t length )
	{
		tiki::writeBytes( m_workingData, pData, length );
	}
}
