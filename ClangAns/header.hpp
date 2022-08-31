#pragma once
//#define __REFLECTION_PARSER__

//#define CLASS(class_name, ...) class class_name
//#include "serializer.hpp"
#define CLASS(class_name, ...) class __attribute__((annotate(#__VA_ARGS__))) class_name
class S {
	int o;
	int j;
};


CLASS(Vec, Fields) {
public:
	int x;
	int y;
};


template<typename T>
CLASS(MyClass:public Vec, Fields) {
public:
	int z;
	int w;
	T s;
};


MyClass<int> a;
MyClass<double> b;

template<typename T>
CLASS(A, Fields){
public:
	T a;

};

template<typename U, typename T>
CLASS(B:public A<T>,Fields ){
public:
	int a;
	T c;
	U u;
};

B<int, double> c;