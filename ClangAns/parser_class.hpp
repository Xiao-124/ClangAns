#pragma once
#include <clang-c/Index.h>

#include "types.hpp"


namespace parser
{
	Class GetClass(CXCursor cursor);
}
