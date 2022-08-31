#pragma once
#include "serializer_class.hpp"

#include <map>
#include <sstream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
namespace serializer {


    void SerializeClassHeader(const Class& c) {
        //cout << c.GetFile() << endl;
        string include = c.GetFile().substr(0, c.GetFile().find_last_of('.')) + ".serializer" + ".gen.h";
        ofstream out;
        string template_string("template<>\n");
        string code_string;
        string name = c.GetFullName();

        if (outMyFile.find(include) == serializer::outMyFile.end()) {
            out.open(include, ios::trunc);
            code_string += "#pragma once\n";
            code_string += "#include \"serializer.h\"\n ";
            code_string += "#include \"";
            code_string += c.GetFile();
            code_string += "\"\n";
            outMyFile[include] = 1;
            
        }       
        else {
            out.open(include, ios::app);
     
        }
        
        
        ostream& o = out;

        

        if (c.templateClass.find(name) != c.templateClass.end()) {
            for (int i = 0; i < c.templateClass[name].size(); i++) {
                code_string += template_string;
                code_string += "PJson PSerializer::write(const %name%& instance);\n";

                code_string += template_string;
                code_string += "%name%& PSerializer::read(const PJson& json_context, %name%& instance);\n";

                code_string = ReplaceAll(code_string, { {"%name%", c.templateClass[name][i]} });
            }
        }
        else {
            code_string += template_string;
            code_string += "PJson PSerializer::write(const %name%& instance);\n";
            code_string += template_string;
            code_string += "%name%& PSerializer::read(const PJson& json_context, %name%& instance);\n";
            code_string = ReplaceAll(code_string, { {"%name%", name} });
            code_string += "\n";
        }
        o << code_string ;
        out.close();
    }

    vector<string> requireArgument(const string& a) {
        vector<string> sa;
        if (a.find('<') == a.npos)
            return sa;
        int a_size = a.find_last_of('>') - a.find_first_of('<');   
        string c;
        string _a = a.substr(a.find_first_of('<') + 1, a_size - 1);
        for (int i = 0; i < _a.size(); i++) {
            if (_a[i] == ',') {
                sa.push_back(c);
                c = "";
                continue;
            }
            if (_a[i] == ' ')
                continue;
            c += _a[i];
        }
        sa.push_back(c);
        return sa;
    }


    

    void SerializeClassSources(const Class& c) {
        string include = c.GetFile().substr(0, c.GetFile().find_last_of('.')) + ".serializer" + ".gen.cpp";
        ofstream out;
        string template_string("template<>\n");
        string code_string;
        string name = c.GetFullName();
        vector<string> parentName;


        if (outMyFile.find(include) == serializer::outMyFile.end()) {
            out.open(include, ios::trunc);
            code_string += "#include \"";
            code_string += c.GetFile().substr(0, c.GetFile().find_last_of('.')) + ".serializer" + ".gen.h";
            code_string += "\"\n";
            outMyFile[include] = 1;
        }
        else {
            out.open(include, ios::app);
        }
        
        //out.open(include, ios::ate);
        ostream& o = out;


        
 
        if (c.templateClass.find(name) != c.templateClass.end()) {            
            for (int j = 0; j < c.templateClass[name].size(); j++) {
                vector< string> parName;

                for (int i = 0; i < c.parent.size(); i++) { //对继承的类的添加
                    vector<string> arg1 = requireArgument(c.parent[i]);
                    vector<string> arg3 = requireArgument(c.templateClass[name][j]);
                    string pName = c.parent[i].substr(0, c.parent[i].find_first_of('<'));
                    
                    if (arg1.size() != 0) {                
                        pName += "<";
                        for (int z = 0; z < arg1.size(); z++) {
                            for (int k = 0; k < c.templateType.size(); k++) {
                                if (arg1[z] == c.templateType[k]) {
                                    arg1[z] = arg3[k];                
                                }
                                
                            }
                        }
                        for (int z = 0; z < arg1.size(); z++) {
                            if (z != arg1.size() - 1) {
                                pName += arg1[z];
                                pName += ",";
                            }
                            else {
                                pName += arg1[z];
                            }
                        }
                        pName += ">";
                    }
                    parName.push_back(pName);
                    
                }

                code_string += template_string;
                code_string +=
                    "PJson PSerializer::write(const %name%& instance) { \n"
                    "   PJson::object  ret_context; \n";

                for (int i = 0; i < c.parent.size(); i++) { //对继承的类的添加
                 
                    code_string +=
                        "   auto&& %json_name% = PSerializer::write(*(%base_name%*) & instance);\n"
                        "   assert(%json_name%.is_object());\n"
                        "   auto && %json_map_name% = %json_name%.object_items();\n "
                        "   ret_context.insert(%json_map_name%.begin(), %json_map_name%.end()); \n";
                    string json_name = "json_context_" + to_string(i);
                    string json_map_name = "json_context_map_" + to_string(i);
                    code_string = ReplaceAll(code_string, { {"%json_name%", json_name},
                                                            {"%json_map_name%", json_map_name},
                                                            {"%base_name%", parName[i]}});
                    

                }

                for (int i = 0; i < c.Fields.size(); i++) { //对自己参数的添加
                    code_string +=
                        "   ret_context.insert_or_assign(\"%type_name%\", PSerializer::write(instance.%type_name%));\n";
                    code_string = ReplaceAll(code_string, { {"%type_name%", c.Fields[i].Name} });
                    if (c.Fields[i].Type.find("vector") != string::npos) {
                        std::cout << c.Fields[i].Type <<"," << c.Fields[i].Name << std::endl;
                    }

                    

                }
                code_string +=
                    "   return  PJson(ret_context);\n"
                    "}\n";

                //read函数
                code_string += template_string;
                code_string += "%name% &PSerializer::read(const PJson& json_context, %name%& instance) {\n"
                                "   assert(json_context.is_object());\n";

                for (int i = 0; i < c.parent.size(); i++) {
                    code_string += "   PSerializer::read(json_context, *(%base_name%*)& instance);\n";
                    code_string = ReplaceAll(code_string, { {"%base_name%", parName[i]} });
                }

                for (int i = 0; i < c.Fields.size(); i++) {
                    code_string +=
                        "   if (!json_context[\"%type_name%\"].is_null()) {\n"
                        "       PSerializer::read(json_context[\"%type_name%\"], instance.%type_name%);\n"
                        "   } \n";
                    code_string = ReplaceAll(code_string, { {"%type_name%", c.Fields[i].Name} });
                }
                code_string +=
                    "   return instance;\n"
                    "}\n";


                code_string += "\n";

                code_string = ReplaceAll(code_string, { {"%name%", c.templateClass[name][j]} });

            }
        }
        else {

            code_string += template_string;
            code_string +=
                "PJson PSerializer::write(const %name%& instance) { \n"
                "   PJson::object  ret_context; \n";

            for (int i = 0; i < c.parent.size(); i++) { //对继承的类的添加
                code_string +=
                    "   auto&& %json_name% = PSerializer::write(*(%base_name%*) & instance);\n"
                    "   assert(%json_name%.is_object());\n"
                    "   auto && %json_map_name% = %json_name%.object_items();\n "
                    "   ret_context.insert(%json_map_name%.begin(), %json_map_name%.end()); \n";
                string json_name = "json_context_" + to_string(i);
                string json_map_name = "json_context_map_" + to_string(i);
                code_string = ReplaceAll(code_string, { {"%json_name%", json_name},
                                                        {"%json_map_name%", json_map_name},
                                                        {"%base_name%", c.parent[i]}});
            }

            for (int i = 0; i < c.Fields.size(); i++) { //对自己参数的添加
                code_string +=
                    "   ret_context.insert_or_assign(\"%type_name%\", PSerializer::write(instance.%type_name%));\n";
                code_string = ReplaceAll(code_string, { {"%type_name%", c.Fields[i].Name} });
            }
            code_string +=
                "   return  PJson(ret_context);\n"
                "}\n";

            //read函数
            code_string += template_string;
            code_string += "%name% &PSerializer::read(const PJson& json_context, %name%& instance) {\n"
                "   assert(json_context.is_object());\n";

            for (int i = 0; i < c.parent.size(); i++) {
                code_string += "   PSerializer::read(json_context, *(%base_name%*)& instance);\n";
                code_string = ReplaceAll(code_string, { {"%base_name%", c.parent[i]} });
            }

            for (int i = 0; i < c.Fields.size(); i++) {
                code_string +=
                    "   if (!json_context[\"%type_name%\"].is_null()) {\n"
                    "       PSerializer::read(json_context[\"%type_name%\"], instance.%type_name%);\n"
                    "   } \n";
                code_string = ReplaceAll(code_string, { {"%type_name%", c.Fields[i].Name} });
            }
            code_string +=
                "   return instance;\n"
                "}\n";


            code_string += "\n";
            code_string = ReplaceAll(code_string, { {"%name%", name} });

        }
             
        o << code_string;
        out.close();

    }
}



