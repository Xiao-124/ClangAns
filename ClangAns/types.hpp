#pragma once

#include <string>
#include <vector>
#include <map>

class TypeBase
{
public:
	enum class Type
	{
		Class,
	};

public:
	TypeBase(std::string file, std::string full_name);
	virtual ~TypeBase();

	virtual Type GetType() const = 0;
	const std::string& GetFullName() const;
	const std::string& GetName() const;

	const std::string& GetFile() const;

private:
	std::string file_;
	std::string full_name_;
};

class Enum : public TypeBase
{
public:
	using ValueList = std::vector<std::pair<std::string, int>>;

public:
	Enum(std::string file, std::string full_name);
	Type GetType() const override;

	ValueList Values;
};

struct NamedObject	//类型描述
{
	std::string Name;	//名称
	std::string Type;	//类型
};

class Function:public TypeBase	//函数描述
{
public:
	Function(std::string file, std::string full_name);
	Type GetType() const override;

	std::string Name;	//名称
	std::vector<NamedObject> Arguments;	//参数列表
	std::string ReturnType;	//返回值类型
};

class Class : public TypeBase
{
public:
	using MethodList = std::vector<Function>;
	using FieldList = std::vector<NamedObject>;

public:
	Class(std::string file, std::string full_name);
	Type GetType() const override;

	MethodList Methods;	//函数列表
	MethodList StaticMethods;//静态函数列表

	FieldList Fields;	//成员列表
	FieldList StaticFields;//静态成员列表

	std::vector <std::string> parent;
	std::vector<std::string> templateType;

	
	static std::map <std::string, std::vector<std::string> > templateClass;
	static std::map<std::string, std::string> templateClassType;
};





