#pragma once
#include <memory>
#include <string>
#include <vector>
#include <regex>

#include "types.hpp"
namespace parser
{
	struct Options
	{
		std::regex include;
		std::regex exclude;
	};
	

	std::vector<std::unique_ptr<TypeBase>> GetTypes(
		const std::string& file,
		const Options& options = Options());
};