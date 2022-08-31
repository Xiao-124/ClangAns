#include "types.hpp"
using namespace std;
std::map <std::string, std::vector<std::string> > Class::templateClass;
std::map<std::string, std::string>  Class::templateClassType;

TypeBase::TypeBase(string file, string full_name)
	: full_name_(move(full_name))
	, file_(move(file))
{
}

TypeBase::~TypeBase() = default;

const string& TypeBase::GetFullName() const
{
	return full_name_;
}

const string& TypeBase::GetName() const
{
	return full_name_;
}

const string& TypeBase::GetFile() const
{
	return file_;
}

Enum::Enum(string file, string full_name)
	: TypeBase(move(file), move(full_name))
{
}



Function::Function(std::string file, std::string full_name)
	: TypeBase(move(file), move(full_name))
{
}



Class::Class(string file, string full_name)
	: TypeBase(move(file), move(full_name))
{
}

Class::Type Class::GetType() const
{
	return Type::Class;
}

Enum::Type Enum::GetType() const
{
	return Type::Class;
}

Function::Type Function::GetType() const
{
	return Type::Class;
}