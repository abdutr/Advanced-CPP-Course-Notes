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


 consteval int baz(int x){
   return x*x;
 }

 constinit int var = 5; // Must be constant initialized, otherwise syntax error
 // constinit = constexpr - const
 // constexpr variables are const by default, so constinit is initialized with consexpr but variable is not constant 

class [[nodiscard]] MyClass{ // return value from Functions returning MyClass must not be discarded
public:
   inline static constinit int iVal = 456; // constinit can be used for global or static member variables
};

[[nodiscard]] int noDiscardFunc(){return 5;}; // Result should not be discarded, added with C++17
[[nodiscard("noDiscardFunc2 should not be discarded")]] int noDiscardFunc2(){return 5;}; // Message is added with C++20

MyClass myClassReturningFunc(){return MyClass{};}


// Concepts #############

template <std::integral T>
class ClassName {
public:

private:

};


template<std::integral T>
void numberFunc(T integer){
   fmt::print("Func for integer types\n");
}

template<std::floating_point T>
void numberFunc(T floatingPoint){
   fmt::print("Func for floating point types\n");
}

// we can even skip template type
void easierNumberFund(integral auto x){
   fmt::print("easierNumberFund for integral types\n");
}

// Concept is also a new keyword C++20

//Before concepts, it is tricky to do simple integral check.
// 3 options with SFINAE
template<typename T,enable_if_t<is_integral_v<T>>* = nullptr >
void foo1(T){

}

template <typename T>
enable_if_t<is_integral_v<T>,T> foo2(T){}

template <typename T>
void foo3(T, enable_if_t<is_integral_v<T>> *p=nullptr){}

template <typename T>
void print(const T& t){
   cout << t;
}

// 3 tool: 
// requires clause
//       prefix
//       trailing
// requires expression
// named constraints ==> concep

// requires <compileTimeboolean>

// requires clause
template <typename T>
requires (sizeof(T) > 2)  // we cant use name of the input (x) with prefix requires
void funcWithInputBigger2(T x){}

template <typename T>
// we can use name of the input (x) with trailing version of  requires
void funcWithInputBigger2AndIntegral(T x) requires (sizeof(x) > 2) && is_integral_v<typeof(x)>{}

// requires clause with requires expression + concept
template <typename T>
requires (sizeof(T) > 2) &&
requires {typename T::size_type;} &&  // Requires expression
input_iterator<T> // Concept
class ConstrainedClass{};

template <typename T>
requires is_pointer_v<T> || is_reference_v<T>
class AnotherClass{};

//Concept definition
template <typename T>
concept Integral = is_integral_v<T>;

template <typename T>
concept SignedIntegral = Integral<T> && is_signed_v<T>;

template <typename T>
// concept UnsignedIntegral = Integral<T> && is_unsigned_v<T>; // or
concept UnsignedIntegral = Integral<T> && !SignedIntegral<T>;

template<typename T>
requires Integral<T> int integralTakingFunc(T){}

// Constrained template parameter
template<Integral T>
int integralTakingFunc2(T){}

template<Integral T,Integral U>
class ConstrainedClass2{};

template <size_t N>
requires (N > 10)
class ConstrainedClass3{};

template <typename T>
concept as_int = integral<T> || is_convertible_v<T,int>;

// template<as_int T> // or
template<typename T>
requires as_int<T>
int intConvertibleTakingFunction(){return 0;}


// or 


int intConvertibleArgTakingFunction(as_int auto x){}
int ConvertibleToStringTakingFunc(convertible_to<string> auto x){}

integral auto integralReturningFunc(int x){
   // return x*3.4; // Deduced type 'double' does not satisfy 'integral'
   return x*3; // ok
}

template <typename T>
void func(T x){
   if constexpr (integral<T>){
      fmt::print("For integral types\n");
   } else if constexpr (floating_point<T>){
      fmt::print("For floating point types\n");
   } else {
      fmt::print("For other types\n");
   }
}

template <typename T>
concept additive = requires (T x,T y){
   x+ y;
   x-y;
};


template<typename T>
void printDependingOnType(T x){
   if constexpr ( additive<T>){
      fmt::print("Additive Type\n");
   } else {
      fmt::print("Non Additive Type\n");
   }
}

template<size_t N>
requires (has_single_bit(N)) && (N >32)
class PowerOfTwoBiggerThan32{};


constexpr bool isPrime(int x){
   if(x<2) return false;

   if(x %2 == 0) return x ==2;
   if(x %3 == 0) return x ==3;
   if(x %5 == 0) return x ==5;

   for(int i{7}; i*i <= x; i+=2){
      if( x % i == 0) return false;
   }
   return true;
}

template<int N>
concept Prime = isPrime(N);

template<int N>
requires (isPrime(N))
void primeFunc(){}

template<typename T>
concept Abdu = requires (T x){
   // simple requirements, will check if following is valid ( not a syntax error)
   x++;
   is_integral_v<T>; // Can be be checked with is_integral, not checking if T is integral or not  !!!
   // x == nullptr;  // is x comparable with nullptr 
};

template<typename T>
concept Printable = requires (T var) {
   // cout << var;
   var.print(); // var must have callable print function
};

struct A{};
struct B{
   void print();
};


// Requires expression can be used with requires claus, can be also used outside concept definition
template<typename T>
requires requires(T x){
    x+x;
    x-x;
   sizeof(T) > 2; // Can this check be done ( Yes always so kind of useless here)
} && integral<T>
class AdditiveClass{};

template<typename T>
requires requires(T x){
    x+x;
    x-x;
    requires sizeof(T) > 2; // Unlike previous two conditions  here sizeof(T) > 2 must be true, 
} && integral<T>
class AdditiveClass2{};


template <typename T>
concept Abdu2 = requires{
   // type requirement
   typename T::value_type; // value_type must exist
};

template <typename T>
concept Alex = requires {
   typename AdditiveClass2<T>; // T must be a valid type for AdditiveClass2
};

template <typename T>
concept Moveable = is_move_constructible_v<T>;

auto main() -> int {
   auto x = baz(5);
   int a = 5;
   // auto y = baz(a); // Syntax error must be compile time
   var = 7; // Var is not constant so we can reassign ( it is constinit C++20)
   // constinit int localVar = 5; // COnstinit cant be used like this : Local variable cannot be declared 'constinit'

   noDiscardFunc2();
   // warning: ignoring return value of function declared with 'nodiscard' attribute: noDiscardFunc2 should not be discarded [-Wunused-result]
   myClassReturningFunc();  // ignoring return value of function declared with 'nodiscard' attribute

   vector vec{3,5,7,1};
   max_element(vec.begin(),vec.end()); // Stardard may not define functions as noDiscard even if you expect it
   // Though compilers may have it defined as noDiscard,above was noDiscard with MSVC, but ok with my Clang env.

   // Concepts ###########
   // Used to constaint templates, improve error messages, reduce compile time load
   // Most importantly to avoid SFINAE
   numberFunc(5);
   numberFunc(6.7);

   easierNumberFund(5);
   // easierNumberFund(7.8); // Nice error message
//    86 |    noDiscardFunc2();
//    |    ^~~~~~~~~~~~~~
// /workspaces/Week1---Value-Category/Lessons/Lesson17.cpp:88:4: warning: ignoring return value of function declared with 'nodiscard' attribute [-Wunused-result]
// 88 |    myClassReturningFunc();  // ignoring return value of function declared with 'nodiscard' attribute
//    |    ^~~~~~~~~~~~~~~~~~~~
// /workspaces/Week1---Value-Category/Lessons/Lesson17.cpp:101:4: error: no matching function for call to 'easierNumberFund'
// 101 |    easierNumberFund(7.8);
//    |    ^~~~~~~~~~~~~~~~
// /workspaces/Week1---Value-Category/Lessons/Lesson17.cpp:75:6: note: candidate template ignored: constraints not satisfied [with x:auto = double]
// 75 | void easierNumberFund(integral auto x){
//    |      ^
// /workspaces/Week1---Value-Category/Lessons/Lesson17.cpp:75:23: note: because 'double' does not satisfy 'integral'
// 75 | void easierNumberFund(integral auto x){
//    |                       ^
// /usr/lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/concepts:100:24: note: because 'is_integral_v<double>' evaluated to false
// 100 |     concept integral = is_integral_v<_Tp>;


   print(12);
   print(1.2);
   print(string{"Abel\n"});
   // print(vector{5,7,8,12});  // Enable it to see big error, old style constrained with SFINAE

   // funcWithInputBigger2('A'); // note: candidate template ignored: constraints not satisfied [with T = char]
   // note: because 'sizeof(char) > 2' (1 > 2) evaluated to false
   funcWithInputBigger2(4); // Ok

   // ConstrainedClass3<5> obj1{}; Constraints not satisfied for class template 'ConstrainedClass3' [with N = 5] note: because '5UL > 10' (5 > 10) evaluated to false
   ConstrainedClass3<12l> obj2{}; // ok

   intConvertibleTakingFunction<double>();
   intConvertibleTakingFunction<int>();
   // intConvertibleTakingFunction<string>(); //because 'std::basic_string<char>' does not satisfy 'integral';


   integral auto xVal = 5/* or lets say call int foo(), then foo must return integral*/;
   // Concepts can be used any place auto can be used

   vector<int> iVec(100);

   for(integral auto x:iVec){
      cout << x ;
   }
   cout <<'\n';


   func(5);
   func(5.8);
   func("Abdu");

   printDependingOnType(5);
   printDependingOnType(&iVec);

   // PowerOfTwoBiggerThan32<54> powerOfTwoBiggerThan32; 
   // // constraints not satisfied for class template 'PowerOfTwoBiggerThan32' [with N = 54]
   // because 'has_single_bit(54UL)' evaluated to false
   PowerOfTwoBiggerThan32<128> powerOfTwoBiggerThan32_2;

   primeFunc<5>();
   primeFunc<7>();
   // primeFunc<8>(); // candidate template ignored: constraints not satisfied [with N = 8] because 'isPrime(8)' evaluated to false

   static_assert(Abdu<int> );
   static_assert(Abdu<double> );
   static_assert(Abdu<vector<int>::iterator> );
   // static_assert(Abdu<string> ); 
   // Static assertion failed Because 'string' (aka 'basic_string<char>') does not satisfy 'Abdu' 
   // Because 'x++' would be invalid: cannot increment value of type

   constexpr auto b1 = Printable<int>; // False
   constexpr auto b2 = Printable<string>; // False
   constexpr auto b3 = Printable<A>; // False
   constexpr auto b4 = Printable<B>; // True

   AdditiveClass<char> additiveClass;
   // AdditiveClass2<char> additiveClass2;  
   // Constraints not satisfied for class template 'AdditiveClass2' [with T = char]clang(template_arg_list_constraints_not_satisfied)
   // Because 'sizeof(char) > 2' (1 > 2) evaluated to false

   constexpr auto hasValueType1 = Abdu2<int>; // False
   constexpr auto hasValueType2 = Abdu2<vector<int>>; // True
   constexpr auto hasValueType3 = Abdu2<vector<int>::iterator>; // True
   
   
   constexpr auto canBeTemplateTypeForAdditive2 = Alex<int>; // True
   constexpr auto canBeTemplateTypeForAdditive2_2 = Alex<char>; // False as Additive2 type size > 2


}