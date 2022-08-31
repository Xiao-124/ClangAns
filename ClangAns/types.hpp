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

struct NamedObject	//��������
{
	std::string Name;	//����
	std::string Type;	//����
};

class Function:public TypeBase	//��������
{
public:
	Function(std::string file, std::string full_name);
	Type GetType() const override;

	std::string Name;	//����
	std::vector<NamedObject> Arguments;	//�����б�
	std::string ReturnType;	//����ֵ����
};

class Class : public TypeBase
{
public:
	using MethodList = std::vector<Function>;
	using FieldList = std::vector<NamedObject>;

public:
	Class(std::string file, std::string full_name);
	Type GetType() const override;

	MethodList Methods;	//�����б�
	MethodList StaticMethods;//��̬�����б�

	FieldList Fields;	//��Ա�б�
	FieldList StaticFields;//��̬��Ա�б�

	std::vector <std::string> parent;
	std::vector<std::string> templateType;

	
	static std::map <std::string, std::vector<std::string> > templateClass;
	static std::map<std::string, std::string> templateClassType;
};





