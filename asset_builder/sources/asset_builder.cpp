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
			{ "font", &m_fontBuilder }
		};
	}

	bool AssetBuilder::buildProject( std::string projectJsonFile, std::string outputPath )
	{
		if( !loadAssets( projectJsonFile ) )
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

	bool AssetBuilder::loadAssets( std::string projectJsonFile )
	{
		std::path projectPath = projectJsonFile;
		projectPath = projectPath.parent_path();

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
		file << "\tstatic const uint8 s_assetData[] =" << std::endl;
		file << "\t{" << std::endl;
		file << "\t\t";

		char buffer[ 16u ];
		size_t lineIndex = 0u;
		for( uint8_t byte : m_workingData )
		{
			snprintf( buffer, sizeof( buffer ), "0x%02xu, ", byte );
			file << buffer;

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

		file << "\tstatic const void* s_assets[] =" << std::endl;
		file << "\t{" << std::endl;
		for( const Asset& asset : m_assets )
		{
			file << "\t\ts_assetData + " << asset.dataOffset << ", // AssetName_" << getCamelCaseString( asset.name ) << std::endl;
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
