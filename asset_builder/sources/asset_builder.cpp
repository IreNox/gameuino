#include "asset_builder.h"

#include "base.h"

#include <third_party/crc_32.h>

#include <fstream>
#include <iostream>

namespace tiki
{
	struct BaseHeader
	{
		uint16_t	magic;
		uint16_t	assetCount;
	};

	struct AssetHeader
	{
		uint32_t	nameCrc;
		uint32_t	offset;
	};

	AssetBuilder::AssetBuilder()
	{
		m_builders =
		{
			{ "font", &m_fontBuilder }
		};
	}

	bool AssetBuilder::buildProject( std::string projectJsonFile, std::string outputFile )
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
		return writeCppHeader( outputFile );
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
			asset.name		= assetPath.filename().generic_string();
			asset.nameCrc	= crc32buf( asset.name.c_str(), asset.name.length() );

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
		BaseHeader baseHeader;
		baseHeader.magic		= 0x5442u;
		baseHeader.assetCount	= (uint16_t)m_assets.size();
		writeBytes( &baseHeader, sizeof( baseHeader ) );

		size_t currentOffset = sizeof( BaseHeader ) + (sizeof( AssetHeader ) * m_assets.size());
		for( const Asset& asset : m_assets )
		{
			AssetHeader assetHeader;
			assetHeader.nameCrc	= asset.nameCrc;
			assetHeader.offset	= (uint32_t)currentOffset;
			writeBytes( &assetHeader, sizeof( assetHeader ) );

			currentOffset += asset.data.size();
		}

		for( const Asset& asset : m_assets )
		{
			writeBytes( asset.data.data(), asset.data.size() );
		}
	}

	bool AssetBuilder::writeCppHeader( std::string outputFile )
	{
		std::ofstream file( outputFile );
		if( !file.is_open() )
		{
			std::cout << "Failed to open: " << outputFile << std::endl;
			return false;
		}

		file << "#pragma once" << std::endl;
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
		file << "}" << std::endl;
		file << std::endl;

		return true;
	}

	void AssetBuilder::writeBytes( const void* pData, size_t length )
	{
		tiki::writeBytes( m_workingData, pData, length );
	}
}
