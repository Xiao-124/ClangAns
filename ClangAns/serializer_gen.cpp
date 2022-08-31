#include "serializer_gen.hpp"

#include <fstream>
#include <locale>
#include <unordered_set>

#include "serializer_class.hpp"

using namespace std;

namespace
{
	string CalcIncludeGuard(const serializer::Options& options)
	{
		string include_guard = options.out_hpp_path;
		for (char& c : include_guard){
			c = toupper(c, std::locale());
			if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
			{
				continue;
			}
			c = '_';
		}
		return include_guard;
	}

	

	void BeginHeader(ostream& o,const serializer::Options& options,const std::vector<std::unique_ptr<TypeBase>>& types)
	{
		string header =
			"#pragma once\n"
			"#include \"" + options.include_path + "\"\n";
		o << header;
	}

	void EndHeader(ostream& o,const serializer::Options& options)
	{
		
	}

	void BeginSources(ostream& o, const serializer::Options& options)
	{
		string header =
			"#include \"" + options.out_hpp_path + "\"\n";
		o << header;
		
	}

	void EndSources(ostream& o)
	{
		
	}
}  

void serializer::Serialize(const std::vector<std::unique_ptr<TypeBase>>& types, const Options& options)
{
	

	//BeginHeader(*out_hpp, options, types);
	for (const auto& type : types)
	{
		switch (type->GetType())
		{
			case TypeBase::Type::Class:
				SerializeClassHeader(static_cast<const Class&>(*type));
				break;
		}
	}
	//EndHeader(*out_hpp, options);

	//BeginSources(*out_cpp, options);
	for (const auto& type : types)
	{
		switch (type->GetType())
		{
		case TypeBase::Type::Class:
			SerializeClassSources(static_cast<const Class&>(*type));
			break;
		}
		
	}
	//EndSources(*out_cpp);


	

}
