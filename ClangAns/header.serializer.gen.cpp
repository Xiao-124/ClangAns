#include "header.serializer.gen.hpp"
template<>
PJson PSerializer::write(const Vec& instance) { 
   PJson::object  ret_context; 
   ret_context.insert_or_assign("x", PSerializer::write(instance.x));
   ret_context.insert_or_assign("y", PSerializer::write(instance.y));
   return  PJson(ret_context);
}
template<>
Vec &PSerializer::read(const PJson& json_context, Vec& instance) {
   assert(json_context.is_object());
   if (!json_context["x"].is_null()) {
       PSerializer::read(json_context["x"], instance.x)
   } 
   if (!json_context["y"].is_null()) {
       PSerializer::read(json_context["y"], instance.y)
   } 
   return Vec;
}



template<>
PJson PSerializer::write(const MyClass<int>& instance) { 
   PJson::object  ret_context; 
   auto&& json_context_0 = PSerializer::write(*(Pilot::Vec*) & instance);
   assert(json_context_0.is_object());
   ret_context.insert_or_assign("z", PSerializer::write(instance.z));
   ret_context.insert_or_assign("w", PSerializer::write(instance.w));
   ret_context.insert_or_assign("s", PSerializer::write(instance.s));
   return  PJson(ret_context);
}
template<>
MyClass<int> &PSerializer::read(const PJson& json_context, MyClass<int>& instance) {
   assert(json_context.is_object());
   PSerializer::read(json_context, *(Pilot::Vec*)& instance);
   if (!json_context["z"].is_null()) {
       PSerializer::read(json_context["z"], instance.z)
   } 
   if (!json_context["w"].is_null()) {
       PSerializer::read(json_context["w"], instance.w)
   } 
   if (!json_context["s"].is_null()) {
       PSerializer::read(json_context["s"], instance.s)
   } 
   return MyClass<int>;
}

template<>
PJson PSerializer::write(const MyClass<double>& instance) { 
   PJson::object  ret_context; 
   auto&& json_context_0 = PSerializer::write(*(Pilot::Vec*) & instance);
   assert(json_context_0.is_object());
   ret_context.insert_or_assign("z", PSerializer::write(instance.z));
   ret_context.insert_or_assign("w", PSerializer::write(instance.w));
   ret_context.insert_or_assign("s", PSerializer::write(instance.s));
   return  PJson(ret_context);
}
template<>
MyClass<double> &PSerializer::read(const PJson& json_context, MyClass<double>& instance) {
   assert(json_context.is_object());
   PSerializer::read(json_context, *(Pilot::Vec*)& instance);
   if (!json_context["z"].is_null()) {
       PSerializer::read(json_context["z"], instance.z)
   } 
   if (!json_context["w"].is_null()) {
       PSerializer::read(json_context["w"], instance.w)
   } 
   if (!json_context["s"].is_null()) {
       PSerializer::read(json_context["s"], instance.s)
   } 
   return MyClass<double>;
}





template<>
PJson PSerializer::write(const B<int, double>& instance) { 
   PJson::object  ret_context; 
   auto&& json_context_0 = PSerializer::write(*(Pilot::A<double>*) & instance);
   assert(json_context_0.is_object());
   ret_context.insert_or_assign("a", PSerializer::write(instance.a));
   ret_context.insert_or_assign("c", PSerializer::write(instance.c));
   ret_context.insert_or_assign("u", PSerializer::write(instance.u));
   return  PJson(ret_context);
}
template<>
B<int, double> &PSerializer::read(const PJson& json_context, B<int, double>& instance) {
   assert(json_context.is_object());
   PSerializer::read(json_context, *(Pilot::A<double>*)& instance);
   if (!json_context["a"].is_null()) {
       PSerializer::read(json_context["a"], instance.a)
   } 
   if (!json_context["c"].is_null()) {
       PSerializer::read(json_context["c"], instance.c)
   } 
   if (!json_context["u"].is_null()) {
       PSerializer::read(json_context["u"], instance.u)
   } 
   return B<int, double>;
}



