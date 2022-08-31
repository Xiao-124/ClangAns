#include "parser_util.hpp"
#include <iostream>
using namespace std;

string parser::Convert(const CXString& s)
{
	string result = clang_getCString(s);
	clang_disposeString(s);
	return result;
}

string parser::GetFullName(CXCursor cursor)
{
	string name;
	
	while (clang_isDeclaration(clang_getCursorKind(cursor)) != 0)	//得到类型
	{
		string cur = Convert(clang_getCursorSpelling(cursor));		//得到名称
		if (name.empty())
		{
			name = cur;
		}
		else
		{
			name = cur + "::" + name;
		}
		cursor = clang_getCursorSemanticParent(cursor);
		
	}
	
	return name;	//name最后是类::的形式
}

string parser::GetName(const CXType& type)
{
	//TODO: unfortunately, this isn't good enough. It only works as long as the
	// type is fully qualified.
	return Convert(clang_getTypeSpelling(type));	
}

string parser::GetFile(const CXCursor& cursor)	//得到类所在的头文件
{
	auto location = clang_getCursorLocation(cursor);
	CXFile file;
	clang_getSpellingLocation(location, &file, nullptr, nullptr, nullptr);
	return Convert(clang_getFileName(file));
}

bool parser::IsRecursivelyPublic(CXCursor cursor)
{
	while (clang_isDeclaration(clang_getCursorKind(cursor)) != 0)
	{
		auto access = clang_getCXXAccessSpecifier(cursor);
		if (access == CX_CXXPrivate || access == CX_CXXProtected)
		{
			return false;
		}

		if (clang_getCursorLinkage(cursor) == CXLinkage_Internal)
		{
			return false;
		}

		if (clang_getCursorKind(cursor) == CXCursor_Namespace
			&& Convert(clang_getCursorSpelling(cursor)).empty())
		{
			// Anonymous namespace.
			return false;
		}

		cursor = clang_getCursorSemanticParent(cursor);
	}

	return true;
}