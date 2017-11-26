#pragma once

#include <third_party/json.hpp>

#include <filesystem>
#include <vector>

namespace std
{
	using path = std::experimental::filesystem::path;
}

namespace tiki
{
	using json = nlohmann::json;

	struct Asset
	{
		std::string				name;
		std::string				fileName;

		json					config;
		std::string				type;

		std::vector< uint8_t >	data;
		size_t					dataOffset;
	};

	class Builder
	{
	public:

		virtual bool buildAsset( std::vector< uint8_t >& targetData, const Asset& asset ) = 0;
	};
}