#include <algorithm>
#include <bitset>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <string>
#include <optional>
#include <strings.h>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>
#include <format>
#include <set>
#include <list>
#include <any>
#include <complex>
#include <compare>
#include <bit> // C++ 20 

#include "fmt/core.h"
#include "fmt/format.h"

#include "utils.hpp"

using namespace std;

template<typename T>
requires std::integral<T>
class MyClass{};

template<typename T>
concept Abdu = requires(T x){ // 3type requirements
   x.foo(); // Simple Requirement
   *x;
   typename T::value_type; // Type Requirement
   typename T::value_type::first_type; // Type Requirement
   typename T::value_type::second_type; // Type Requirement
   typename MyClass<T>; // Type Requirement
};

template <typename T>
concept cabdu = requires(T::value_type){ // Another way to check if T::value_type exists
   true; // Here cant be empty so we just added true
};

template<typename T>
concept Abdu2 = requires (T x){ 
   {x.foo()};  // Compound requirements
   {x.bar()}noexcept; // Running x.bar should provide noexcept guarantee
   {*x}noexcept; // Running x.bar should provide noexcept guarantee
};

template<typename T>
concept HasNoexceptFoo = requires(T x) {
   {x.foo()}noexcept;
};

class A{
   public:
   void foo();
};

class B{
   public:
   void foo() noexcept;
};

class C{
   public:
   int foo() noexcept;
};

template<typename T>
concept Abdu3 = requires (T x){ 
   {x.foo()}noexcept -> same_as<int>; // like same_as<decltype(x.foo()),int>
   {x.foo()}noexcept -> integral; // like same_as<decltype(x.foo()),int>
};

template<typename T>
concept Nested= requires (T x){ 
   requires sizeof(x)>2; // Nested
   requires requires(T x,T y){ //Nested
      x==y;
      x.foo();
   };
};

template<typename T,typename U>
concept Abdu4 = requires{
   typename std::common_type_t<T,U>;
   requires common_with<T,U>;
};

void foo(std::integral auto){
   fmt::print("Integral\n");
}

void foo(std::unsigned_integral auto){
   fmt::print("unsigned_integral\n");
}

template<typename T>
concept Abdu5 = requires (T x){ 
   x.foo();
};

template<typename T>
concept Abdu6 = Abdu5<T> && requires (T x){ 
   x.bar();
};

void func1(Abdu5 auto){
   fmt::print("func1-Abdu5 is called\n");
}

void func1(Abdu6 auto){
   fmt::print("func1-Abdu6 is called\n");
}

struct struct1{
   void foo();
};

struct struct2{
   void foo();
   void bar();
};

template<typename T>
requires requires(T x){
   x.foo();
} void func2(T x){
   fmt::print("func2 x.foo() is called\n");
}

template<typename T>
requires requires(T x){
   x.foo();
   x.bar();
} void func2(T x){
   fmt::print("func2 x.foo(),x.bar is called\n");
}

auto main() -> int {

   constexpr auto haveValue_type = cabdu<std::vector<int>>;
   constexpr auto haveValue_type2 = cabdu<string>;
   constexpr auto haveValue_type3 = cabdu<char>;

   constexpr auto hasNoexceptFooFuncStr = HasNoexceptFoo<string>;
   constexpr auto hasNoexceptFooFunc = HasNoexceptFoo<A>;
   constexpr auto hasNoexceptFooFunc2 = HasNoexceptFoo<B>;
   fmt::print("Does a/b has noexcept foo function a:{} b:{}\n",hasNoexceptFooFunc,hasNoexceptFooFunc2);

   constexpr auto hasNoexceptFooFunc4 = Abdu3<C>;

   // Concepts can be used :
   // 1.in any template contraint context that expects boolean
   //    Function/Class template -> requires Concept<T>
   // 2. Defining another concept
   //    concept c1 = integral<T> && HasFoo<T>
   // 3. Constraining template function/class like the following
   //    template<integral T> func(T x);  
   // 4. With auto for template parameter or return type or type deduction
   //    void g(integral auto T); or integral auto func() or integral auto num = func();
   // 5. With Lambdas:
   //    []<integral T>(T x) -> floating_point auto{};
   auto f = []<typename T>(T x)->floating_point auto{return x*x;};
   // auto f2 = [](integral auto x)->integral auto{return x*5.0;}; 
   // f2(5);  // deduced type 'double' does not satisfy 'integral'

   foo(5);
   foo(5u); // Above includes this however specific one(most limiting one) is selected 

   // Subsumption only works with concepts
   func1(struct1{}); //func1-Abdu5 is called
   func1(struct2{}); //func1-Abdu6 is called

   // No subsumption happened when requires expression is used without concepts
   func2(struct1{});
   // func2(struct2{}); //call to 'func2' is ambiguous
}