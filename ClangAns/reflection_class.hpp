#pragma once
#include <iostream>

#include "serializer.hpp"
#include "serializer_util.hpp"
#include "types.hpp"

namespace reflection
{
	void ReflectionClassHeader(std::ostream& o, const Class& c);
	void ReflectionClassSources(std::ostream& o, const Class& c);
}