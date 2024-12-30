// #include <algorithm>
// #include <bitset>
// #include <cmath>
// #include <cstring>
// #include <functional>
// #include <iostream>
// #include <iterator>
// #include <string>
// #include <optional>
// #include <strings.h>
// #include <tuple>
// #include <type_traits>
// #include <utility>
// #include <variant>
// #include <format>
// #include <set>
// #include <list>
// #include <any>
// #include <complex>
// #include <compare>

// #include "fmt/core.h"
// #include "fmt/format.h"

// #include "utils.hpp"

//  using namespace std;

//  class Mint{
// public:
//     Mint() = default;
//     explicit Mint(int x) : mx{x}{}
//     int get()const {return mx;}
// private:
//     int mx{};
//  };

// // Formatter 1

// //  template<>
// //  class std::formatter<Mint>{
// // public:
// //     constexpr auto parse(std::format_parse_context& ctx){
// //         // ctx.begin();
// //         // Returns first character related to formatting "{:12}" returns loc of 1
// //         // For {} returns location of }
// //         //ctx.end() // returns last location of str "{:12}\n" it returns location after \n 
// //         auto iter = ctx.begin();
// //         while(iter != ctx.end() && *iter != '}'){
// //             if(*iter < '0' || *iter > '9'){
// //                 throw std::format_error(std::format("invalid width char {}",*iter));
// //             }
// //             mWidth = mWidth*10 + *iter -'0';
// //             ++iter;
// //         }

// //         return iter;
// //     }

// //     constexpr auto format(const Mint& m,std::format_context& ctx) const {
// //         return std::format_to(ctx.out(),"{:{}}",m.get(),mWidth);
// //     }

// //     int mWidth{};
// //  };

// //  How can we std::formatter int for above

// // Formatter 2

// // template<>
// // class std::formatter<Mint>{
// // public:
// //     std::formatter<int> mf;
// //     constexpr auto parse(std::format_parse_context& ctx){
// //         return mf.parse(ctx);
// //     }

// //     constexpr auto format(const Mint& m,s td::format_context& ctx) const {
// //        return mf.format(m.get(),ctx);
// //     }

// // };

// // Formatter 3
// template <>
// class std::formatter<Mint> : public  std::formatter<int>{
// public:
//     constexpr auto format(const Mint& m, std::format_context& ctx) const{
//         return std::formatter<int>::format(m.get(),ctx);
//     }
// };

// enum class Fruit{apple,melon,orange};

// template<>
// class std::formatter<Fruit> : public std::formatter<string>
// {
//     public:
//     auto format(Fruit f,std::format_context& ctx) const {
//         string str;
//         switch(f){
//             using enum Fruit;
//             case apple:
//                 str = "apple"; break;
//             case melon:
//                 str = "melon"; break;
//             case orange:
//                 str = "orange"; break;
//         }
//         return std::formatter<string>::format(str,ctx);
//     }
// };


// //Aggregate rules for C++20 ( it is different between versions)
// // Aggregates cant have user declared constructor ( C++20)
// // Public inherirance can exist
// // If Provate/Protected  inheritance is used then no longer aggregate. 
// // Base class does not need to be aggregate type, still derived is aggregate
// // Virtual inheritance/functions breaks being aggregate, cant have virtual inheritance
// // Multiple inheritance is ok, does not break aggregate
// // Aggregates can have static variables

// class Triangle{
// private:
//     double e1,e2,e3;
// };

// // Aggregate, no information hiding, no enforsing invariants etc.
// struct Point{
//     int x, y;
// };

// struct Abdu{
//     int x,y,z;
     
//     // private: int a; // Not aggregate
//     string str; // Still aggregate, even though str is not aggregate
//     // There is no condition saying all members should be aggregate.
// };

// class MyClass{};
// class MyClass2{
//     MyClass2(int);
// };


// struct Abdu2 : MyClass{
//     int x,y,z;
//     int& a,&b; // Having ref is ok
// };

// struct Abdu3 : MyClass2{
//     int x,y,z;
//     using MyClass2::MyClass2; // Inherited constructor breaks aggregate, not aggregate
// };

// class Abdu4{ // Class can also be aggregate as long as conditions are satisfied
// public:
//     int x,y;
//     int foo();
// protected:
//     int bar(); // Having private/protected functions does not break being aggregate
// private:
//     int baz();
//     // Thought it cant have virtual function

//     Abdu4 operator+(const Abdu4&); // No problem having operator overload
// };

// class Abdu5{
//     int x =5; // Default member initializer is ok with aggregate with C++14
//     int y =5;
//     Abdu5() = default; // Not aggregate with C++20, it was aggregate before
// };

// struct Abdu6{
//     int x;
//     double dVal;
//     std::string str;
//     int arr[3];
// };

// struct Uys{
//     int a,b;
// };

// struct Abdu7{
//     int x;
//     Uys u;
//     int ar[3];
// };

// struct Person{
//     int id;
//     string name{"Michael Brain"};
//     int age;
// };

// Person GetPerson(){
//     return Person{.id=0,.name="Abdu",.age=27};
// }

// auto main() -> int {
//     Mint m{345};
//     // These 2 below are supported for formatter1,2
//     cout << format("|{}|\n",m);
//     cout << format("|{:15}|\n",m);

//     // All  things which are supported by int are supported with formatter 2,3 
//     cout << format("|{:<}|\n",m);
//     cout << format("|{:<#15}|\n",m);
//     Fruit f = Fruit::melon;
//     cout << format("|{:_<16}|\n",f);
//     cout << format("|{:_>24}|\n",Fruit::orange);

//     // All examples before and Lesson 14 expects constexpr format specifying text
//     // For non constexpr we use vformat

//     string formatStr = "|{:<5}|";
//     // auto resultStr = format(formatStr,345); // Not valid 
//     // Call to consteval function 'std::basic_format_string<char, int>::basic_format_string<std::basic_string<char>>' is not a constant 
//     // expressionclang(invalid_consteval_call)

//     // We need to use make_format_args when using vformat
//     auto resultStr = vformat(formatStr,make_format_args(345));
//     cout << resultStr << '\n';
    

//     //Aggregate types

//     static_assert(std::is_aggregate_v<Point>,"not an aggregate");
//     static_assert(std::is_aggregate_v<Abdu>,"not an aggregate");
//     static_assert(std::is_aggregate_v<Abdu2>,"not an aggregate");
//     // static_assert(std::is_aggregate_v<Abdu3>,"not an aggregate"); // Not aggregate
//     static_assert(std::is_aggregate_v<Abdu4>,"not an aggregate"); 
//     // static_assert(std::is_aggregate_v<Abdu5>,"not an aggregate");// Not aggregate
//     // static_assert(is_aggregate_v<decltype([](){})>) // Lammbda class types are not aggregate
//     // But we can inherit from lambda classes and that may be aggregate.


//     // For aggregate types we can give initial value like this : 
//     Abdu4 abdu4Object{3,5};
//     Abdu6 abdu6Object{3,5.0,"Alex",7,3,1};

//     Abdu7 abdu7Object{5,{3,7},1}; // Vars which are not specified here are value initialized.
//     cout << abdu7Object.ar[0] << abdu7Object.ar[1] <<  abdu7Object.ar[2] << "\n"; 

//     // Abdu7 abdu7obj = 5 // does not work should be either = {5} or var{4}

//     array<int,5> ar{2,4,6,87}; // Valid because array is aggregate,
//     // Above is not initializer list constructor

//     auto [var1,var2] = abdu4Object; // Structured binding can be used with aggregates
//     // With C++20 designated initializer can be used for aggregate types
//     Abdu4 abdu4Object2{.x =5,.y = 8};// Variable order is important.
//     // Static variables cant be initialized via designated initializer
//     Abdu7 abdu7Object2{.x=5,.u ={.a=5,.b=7},.ar = {1}}; // Nested type can use designated initializer like this
//     // Abdu7 abdu7Object3{.x=5,.u.a=5,.ar = {1}}; // This is not valid C++, C extension

//     // Aggregates are helpful when used for function return type, MRVO and structural binding
//     auto [id,name,age] = GetPerson();
// }