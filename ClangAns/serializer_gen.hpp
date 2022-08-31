#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <fstream>
#include "types.hpp"
#include "serializer_class.hpp"
#include <map>
namespace serializer
{
	struct Options
	{
		std::string include_path;
		std::string out_hpp_path;
		std::string out_cpp_path;
	};


	static std::map<std::string, int> outMyFile;

	void Serialize(const std::vector<std::unique_ptr<TypeBase>>& types, const Options& options = Options());
}
