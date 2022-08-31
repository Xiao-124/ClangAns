#include "reflection_class.hpp"

#include <map>
#include <sstream>
#include <vector>
using namespace std;
namespace reflection {

    void ReflectionClassHeader(std::ostream& o, const Class& c) {
        string code_string;
        code_string += "class Type%class_name%Operator {\n";
        code_string += 
            "constructorWithJson(const PJson & json_context) {"
            "   %class_name%* ret_instance = new %class_name%;"
            "   PSerializer::read(json_context, *ret_instance);"
            "   return ret_instance;}";
        



        
    }  
}



