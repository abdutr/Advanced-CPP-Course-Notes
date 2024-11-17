// #include <cmath>
// #include <cstring>
// #include <format>
// #include <iostream>
// #include <iterator>
// #include <sstream>
// #include <string>
// #include <type_traits>
// #include <vector>
// #include <algorithm>
// #include <initializer_list>
// #include <numeric>
// #include <string_view>
// #include <chrono>
// #include <iomanip>
// #include <optional>


// #include "utils.hpp"
// class Date{

// };

// // function def with extra size_t creates function accepts string literals
// // Compiler passes length of the  str as second argument
// constexpr Date operator""_dt(const char* str,size_t size){
//     return Date{};
// }

// std::vector<char> operator""_v(const char* str,size_t size){
//     return std::vector<char>(str,str+size);
// }

// class Meter{
//     public:
//     struct PreventUsage{};
//     Meter(PreventUsage, double dval){}
// };


// Meter operator""_mt(long double val){
//     return Meter{Meter::PreventUsage{},static_cast<double>(val)};
// }

// class Person{
// public:
//     Person(const std::string& name):name(name){}
//     void print() const{
//         std::cout << name << "\n";
//     }
//     // Not a good idea;
//     std::string_view getName() const{
//         return name;
//     }

// private:
//     std::string name;

// };

// Person createPerson(){
//     return Person("abdu long str abdu long str  ");
// }

// class MyClass{
// public:
// // Which one should be used ? 
//     // MyClass(const std::string& str):str(str){}
//     // MyClass(std::string_view str):str(str){}
//     // MyClass(std::string str):str(std::move(str)){}
// // It depends generally string_view is good choice.
// // Check Lesson7_string_constructor_comparison.jpg
// private:
//     std::string str;
// };


// void func(const std::string& s){};
// void funcStrView(std::string_view s){};


// auto main() -> int {
//     "123,456/2"_dt; // This works thanks to secons size_t
//     // size_t parameter version is required to distinguish between string literals and uncooked version\

//     // Generally cooked version is prefered, but sometimes does not satisfy use case
//     // Lets say we want very high precision data and dont want precision loss due to conversion to long 
//     // double ,  or case if handling date lets say 10/20/2024

//     auto vec  = "123 312/2"_v;
//     std::cout << "vec size : " << vec.size() << "\n";   

//     utils::print(vec);

//     Meter m = 123.456_mt;
//     // Meter nonValid = 123.456; // This will not compile, due to constructor

//     int x  = 3.56; // Valid , warnin, not great
//     int y(3.87); // Valid, warning, not great
//     // int z {3.98}; // Not valid with uniform initialization;

//     // Raw string literal, no escape sequence, no special meaning for everything inside ()
//     auto str = R"(abc)";
//     std::cout << str << "\n";

//     auto multiLine = R"(
//         abc
//         def
//         ghi
//     )";

//     std::cout << multiLine << "\n";

//     // () are used as delimiter to show start and end of raw string literal, but if we want
//     // to use () in the string we can use custom delimiter
//     auto multiLineWithParenthesis = R"abdu( abc (jkl) )abdu";

//     std::cout << multiLineWithParenthesis << "\n";

//     // Return type is __detail::_Quoted_string<const char *, char>, not a string
//     // Implementation defined , so above is just what clang returns
//     // Add quotes ( or custom delimeter)  to being/end and escape internal quotes default: "
//     // Escapes via 3rd argument, default is \"
//     auto text = std::quoted("  abdu",'*', '$'); 
//     // https://en.cppreference.com/w/cpp/io/manip/quoted
//     std::cout << text << "\n";

//     std::istringstream iss("  *abdu* *alex*  ");
//     std::string name;

//     iss >> std::quoted(name,'*'); // On extraction it removes quotes
//     std::cout << name << "\n";
//     iss >> std::quoted(name,'*');
//     std::cout << name << "\n";

//     // That will copy the string not optimal
//     func("long str blablablablablablabla blablablablablabla blabla  "); 

//     // No copy, just a view, just hold start/end
//     funcStrView("long str blablablablablablabla blablablablablabla blabla  ");

//     std::string bigStr(100'000,'a');
//     size_t idx{4500};
//     size_t size{40000};
//     auto substr = bigStr.substr(idx,size); // This is a very big copy

//     // This is cheap, though C++20
//     std::string_view sv(bigStr.begin()+idx,bigStr.begin()+idx + size);
//     std::string_view svBeforeCpp20(bigStr.data()+idx, size); // Cheap,C++17 version
//     std::cout << (sv==svBeforeCpp20) <<"\n";
//     // String view just holds the start and end, so if the original data is destroyed, it will be invalid
//     // dangling ptr.

//     // String view is not null terminated, so we cant use it in contexts that require null terminated strings
    
//     // String view does not modify original string, it has some non const functions like
//     //  remove_prefix, rmove_suffix, but they do not modify the original string, they just change the view

//     const char* cstr = "abdu";
//     std::string_view sv2 = cstr;
//     std::cout << sv2.length()<< "\n"; // Will be 4 not 5;

//     const char* cstr2 = "abdu\0\0\0uysal";
//     std::string_view sv3 = cstr2; 
//     std::string_view sv4(cstr2,12);
//     std::cout << sv3 << " Len: "<< sv3.length()<< "\n";  // abdu 4
//     std::cout << sv4 << " Len: "<< sv4.length()<< "\n";  // abduuysal 12

//     // string view does not have constructor taking  string, though string has conversion to string view
//     std::string_view sv5 = std::string("abdu"); // Works as a result, but dangling reference
//     auto str2 = std::string("abdu");
//     std::string_view sv6 = str2; // Works and ok, no dangling reference

//     // String has constructor taking string view, it is explicit
//     std::string str3 {sv5}; // Works
//     // std::string str3 = sv5; // Does not work. explicit

//     std::cout << createPerson().getName() << "\n"; // dangling ptr, name is destroyed UB

//     // If string is reallocated ( resize, reassignment etc), string view will be invalid 

//     // Most string_view functions are constexpr

//     constexpr std::string_view sv7 = "abdu uysal";
//     constexpr auto len = sv7.length();
//     constexpr auto cs = sv7.front();
//     constexpr auto ce = sv7.end();

//     constexpr auto iter_beg = sv7.begin();
//     constexpr auto iter_end = sv7.end();

//     constexpr auto u_idx  = sv7.find('u');

//     using namespace std::string_view_literals;
//     // There is string literal defined for string view : sv
//     auto sv8 = "TestSw"sv;



//     std::optional<int> ox;
//     std::optional<int> ox2{std::nullopt}; // both are same, empty
//     if(ox){  // = operatorbool() is used here
//     //    ...
//     }

//     ox2 = 5;
//     std::cout << *ox2 << "\n";
//     std::optional<std::string> ox3{"abdu"};

//     std::cout << ox3->size() << "\n";

//     std::optional ox4 = 5; // CTAD std::optional<int> 
//     // Acessiong empty optional value using *ox or ox -> length() is UB
//     // Accessing empty optional value using. ox.value() throws exeption if empty\
//     // Bad optional access
// }