#pragma once
#include "header.hpp"
template<>
PJson PSerializer::write(const Vec& instance);
template<>
Vec& PSerializer::read(const PJson& json_context, Vec& instance);



template<>
PJson PSerializer::write(const MyClass<int>& instance);
template<>
MyClass<int>& PSerializer::read(const PJson& json_context, MyClass<int>& instance);
template<>
PJson PSerializer::write(const MyClass<double>& instance);
template<>
MyClass<double>& PSerializer::read(const PJson& json_context, MyClass<double>& instance);




template<>
PJson PSerializer::write(const B<int, double>& instance);
template<>
B<int, double>& PSerializer::read(const PJson& json_context, B<int, double>& instance);


