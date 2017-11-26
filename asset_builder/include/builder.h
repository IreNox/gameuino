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

		uint32_t				nameCrc;
		std::vector< uint8_t >	data;
	};

	class Builder
	{
	public:

		virtual bool buildAsset( std::vector< uint8_t >& targetData, const Asset& asset ) = 0;
	};
}