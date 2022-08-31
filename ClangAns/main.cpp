#include <iostream>
#include <clang-c/Index.h>  // This is libclang.
#include "parser.hpp"
#include "serializer_gen.hpp"
#include <sstream>
#include <fstream>
#include <map>
#include "serializer.hpp"
#include "parser_util.hpp"

using namespace std;


int main() {
	string files = "D:/c++programe/clang_Ans/Test/Test/main.cpp";
	parser::Options options;
    auto types = parser::GetTypes(files, options);

	serializer::Options out_file;
	serializer::Serialize(types, out_file);
    
}


/*
ostream& operator<<(ostream& stream, const CXString& str) {
    stream << clang_getCString(str);
    clang_disposeString(str);
    return stream;
}

int main() {
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit = clang_parseTranslationUnit(
        index,
        "header.hpp", nullptr, 0,
        nullptr, 0,
        CXTranslationUnit_None
    );
    if (unit == nullptr) {
        cerr << "Unable to parse translation unit. Quitting." << endl;
        exit(-1);
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(
        cursor,
        [](CXCursor c, CXCursor parent, CXClientData client_data) {
            cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
                << clang_getCursorKindSpelling(clang_getCursorKind(c)) << ","
                << parser::GetName(clang_getCursorType(c)) << clang_getCursorKind(c)<< endl;
            return CXChildVisit_Recurse;
            ;
            

        },
        nullptr
            );

   

    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);


    
}
*/







