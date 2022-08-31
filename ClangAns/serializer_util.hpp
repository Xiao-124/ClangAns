#pragma once

#include <string>
#include <utility>
namespace serializer
{
	std::string GetNameWithoutColons(std::string name);

	using FromToPair = std::pair<std::string, std::string>;
	std::string ReplaceAll(
		const std::string& text,
		std::initializer_list<FromToPair> from_to_pairs);
}