#include "parser_class.hpp"

#include "parser_util.hpp"
#include <iostream>

using namespace std;

namespace
{
	

	NamedObject GetFieldFromCursor(CXCursor cursor)
	{
		NamedObject field;
		field.Name = parser::Convert(clang_getCursorSpelling(cursor));
		field.Type = parser::GetName(clang_getCursorType(cursor));
		return field;
	}


	CXChildVisitResult VisitClass(
		CXCursor cursor, CXCursor parent, CXClientData client_data)
	{
		
		auto* c = reinterpret_cast<Class*>(client_data);
		if (clang_getCXXAccessSpecifier(cursor) == CX_CXXPublic)
		{
			switch (clang_getCursorKind(cursor))
			{
				case CXCursor_FieldDecl:
					c->Fields.push_back(GetFieldFromCursor(cursor));
					break;
				case CXCursor_VarDecl:
					c->StaticFields.push_back(GetFieldFromCursor(cursor));
					break;
				case CXCursor_CXXBaseSpecifier:
					c->parent.push_back(parser::GetName(clang_getCursorType(cursor)));
					break;
				case CXCursor_TemplateTypeParameter:
					c->templateType.push_back(parser::GetName(clang_getCursorType(cursor)));
					break;
				case CXCursor_TemplateRef:
					break;
				default:
					break;
			}

		}
		
		
		return CXChildVisit_Continue;	//继续游标遍历刚刚访问过的游标的下一个兄弟，而不访问其子级。
	}
}



Class parser::GetClass(CXCursor cursor)
{
	bool isAdd = false;



	Class c(GetFile(cursor), GetFullName(cursor));
	clang_visitChildren(cursor, VisitClass, &c);
	return c;
}
