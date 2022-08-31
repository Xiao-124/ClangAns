#include "parser.hpp"
#include <iostream>
#include <clang-c/Index.h>
#include "parser_class.hpp"
#include "parser_util.hpp"

using namespace std;

namespace 
{
	ostream& operator<<(ostream& s, const CXString& str)
	{
		s << parser::Convert(str);
		return s;
	}

	CXTranslationUnit Parse(	//得到ast
		CXIndex& index, const string& file)
	{

		const char* comlist[2] = { {"-D__REFLECTION_PARSER__"}, {"-std=c++17"}};
		CXTranslationUnit unit = clang_parseTranslationUnit(
			index,
			file.c_str(), comlist, 2,
			nullptr, 0,
			CXTranslationUnit_None);

		if (unit == nullptr)
		{
			cerr << "Unable to parse translation unit. Quitting." << endl;
			exit(-1);
		}

		auto diagnostics = clang_getNumDiagnostics(unit);
		if (diagnostics != 0)
		{
			cerr << "> Diagnostics:" << endl;
			for (int i = 0; i != diagnostics; ++i)
			{
				auto diag = clang_getDiagnostic(unit, i);
				cerr << ">>> "
					<< clang_formatDiagnostic(
						diag, clang_defaultDiagnosticDisplayOptions());
			}
		}

		return unit;
	}

	struct GetTypesStruct
	{
		vector<unique_ptr<TypeBase>>* types;
		const parser::Options* options;
	};

	CXChildVisitResult isAddClass(CXCursor cursor, CXCursor parent, CXClientData client_data) {
		auto* c = reinterpret_cast<bool*>(client_data);
		if (clang_getCursorKind(cursor) == CXCursor_AnnotateAttr) {
			*c = true;
			return CXChildVisit_Break;
		}
		return CXChildVisit_Continue;
	}

	CXChildVisitResult GetTypesVisitor(
		CXCursor cursor, CXCursor parent, CXClientData client_data)
	{
		static bool visit_childer = false;
		auto* data = reinterpret_cast<GetTypesStruct*>(client_data);
		std::unique_ptr<TypeBase> type;
		bool isAdd = false;
		string class_name = parser::Convert(clang_getCursorSpelling(cursor));
		switch (clang_getCursorKind(cursor))	//curosr的类型，
		{
			
			case CXCursor_ClassDecl:	//class
			case CXCursor_StructDecl:	//struct
				clang_visitChildren(cursor, isAddClass, &isAdd);
				if (isAdd) {
					type = std::make_unique<Class>(parser::GetClass(cursor));
				}
				break;
			case CXCursor_ClassTemplate:
				clang_visitChildren(cursor, isAddClass, &isAdd);
				if (isAdd) {
					Class::templateClass[class_name];
					type = std::make_unique<Class>(parser::GetClass(cursor));
				}
				break;
			case CXCursor_CallExpr:			
				if (Class::templateClass.find(class_name) != Class::templateClass.end()) {
					string templateA = parser::GetName(clang_getCursorType(cursor) );
					if (find(Class::templateClass[class_name].begin(), Class::templateClass[class_name].end(), templateA) == Class::templateClass[class_name].end()) {
						Class::templateClass[class_name].push_back(templateA);
						//cout << templateA << endl;
					}
				}
				//std::cout << class_name << std::endl;
				break;
			default:
				break;
		}
		
		const string& name = type->GetFullName();
		if (type
			&& !name.empty()
			&& parser::IsRecursivelyPublic(cursor)
			&& !(name.back() == ':')	)
			
		{
			data->types->push_back(std::move(type));
		}
		
		return CXChildVisit_Recurse;//使用相同的访问者和客户端数据递归遍历此游标的子项。
	}
}  // namespace



vector<unique_ptr<TypeBase>> parser::GetTypes(
	const std::string& file,
	const Options& options)
{
	vector<unique_ptr<TypeBase>> results;
	
	CXIndex index = clang_createIndex(0, 0);
	CXTranslationUnit unit = Parse(index, file);	//得到ast(语法树).

	auto cursor = clang_getTranslationUnitCursor(unit);	//得到cursor(指向语法树的指针)

	GetTypesStruct data = { &results, &options };
	clang_visitChildren(cursor, GetTypesVisitor, &data);	//查看TU的所有children,GetTypesVisitor为每次访问cursor调用的函数,
															//data为给GetTypeVistor提供的数据

	clang_disposeTranslationUnit(unit);
	clang_disposeIndex(index);
	
	return results;
}