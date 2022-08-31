#pragma once
#include <iostream>

#include "serializer_gen.hpp"
#include "serializer_util.hpp"
#include "types.hpp"
namespace serializer
{
	void SerializeClassHeader(const Class& c);
	void SerializeClassSources(const Class& c);
}