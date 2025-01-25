// #include <algorithm>
// #include <bitset>
// #include <chrono>
// #include <cmath>
// #include <concepts>
// #include <cstddef>
// #include <cstring>
// #include <deque>
// #include <forward_list>
// #include <functional>
// #include <iostream>
// #include <iterator>
// #include <memory>
// #include <numeric>
// #include <random>
// #include <source_location>
// #include <stdexcept>
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
// #include <bit> // C++ 20 
// #include <ranges> 

// #include "fmt/core.h"
// #include "fmt/format.h"


// #include "utils.hpp"

// using namespace std;

// struct [[deprecated("Use strcut AbduV2" )]] Abdu{
//     int a,b,c;
// };

// [[deprecated]] int deprIntVar = 5;

// using ABDUTYPE [[deprecated]] = unsigned long;

// enum Color {
//     White,
//     Blue [[deprecated]],
//     Yellow
// };

// [[deprecated]]
// void foo(){}

// enum class Color2{white,blue,black,red};

// [[maybe_unused]] [[nodiscard]] static int foo(int x){
    
//     return x*x;
// }

// [[noreturn]] void noReturnFunc(){
//     throw std::runtime_error("Error");
// }

// template<int N>
// void funcGen(){}

// template<typename T>
// class TypeTeller;

// template<typename T>
// void func(T&&){
//     TypeTeller<T> x;
// }

// template<typename T>
// struct TypeIdentity{
//     using type = T;
// };

// template<typename T>
// using TypeIdentity_t = TypeIdentity<T>::type;

// template<typename T>
// void func(T x,TypeIdentity_t<T> y){ // if we want x type to be deducted, and want y to have same time
//     // Std already has functionality for above : std::type_identity_t< Tp>
// }

// template<typename C>
// void func(C x){
//     using std::begin;

//     begin(x);
// }

// template<typename T>
// concept rangeConcept = requires(T& t) {
//     ranges::begin(t);
//     ranges::end(t);
// };

// // Arg must satisfy range concept
// void algo(std::ranges::range auto&&){
//     fmt::print("range\n");
// }

// void algo(std::ranges::input_range auto&&){
//     fmt::print("input_range\n");
// } // Subsume range concept 

// void algo(std::ranges::forward_range auto&&){
//     fmt::print("forward_range\n");
// } 

// void algo(std::ranges::bidirectional_range auto&&){
//     fmt::print("bidirectional_range\n");
// } 

// void algo(std::ranges::contiguous_range auto&&){
//     fmt::print("contiguous_range\n");
// }

// void algo(std::ranges::random_access_range auto&&){
//     fmt::print("random_access_range\n");
// }


// // Sized range does not have subsumption relation with others above
// // void algo(std::ranges::sized_range auto&&){
// //     fmt::print("random_access_range\n");
// // }


// template<typename Iter,typename Sentinel>
// void func(Iter beg,Sentinel end){
//     while(beg != end){
//         fmt::print("{} ",*beg++);
//     }
// }

// struct NullChar{ 
//     bool operator==(auto x) const {
//         return *x == '\0';
//     }
// };



// auto main() -> int {
//     ABDUTYPE unsNum = 5;
//     unsNum += deprIntVar;
//     auto col = Color::Blue;
//     foo();

//     Color2 c{Color2::black};
//     switch(c){
//         [[likely]] case Color2::blue: break; // if we know we get blue mostly
//         case Color2::red: break;
//     }

//     try{
//         noReturnFunc();
//     } catch(const runtime_error& ex){
//         fmt::print("Exception: {}\n",ex.what());
//     }
//     int x = 6;


//     switch(x){
//         case 1 : funcGen<1>();[[fallthrough]] ;// To show this(no break) is intentional
//         case 2 : funcGen<2>(); break;
//         case 3 : funcGen<3>(); break;
//         case 4 : funcGen<4>(); break;
//     }

//     int intVar{5};
//     // func(std::move(intVar)); //implicit instantiation of undefined template 'TypeTeller<int>'

//     vector<int> iVec(10);

//     iota(iVec.begin(),iVec.end(),0);
//     for(auto i : iVec){
//         fmt::print("{} ",i);
//     }
//     fmt::print("\n");

//     namespace chr = std::chrono ; // Namespace alias;

//     namespace rng = std::ranges;

//     // Necati ergin says range are very advantageous and efficient
//     // However need to learn quite a lot and hard to debug until we learn
//     // all the tools and details

//     // 1.Ranges are concept constrained instead of old style sfinae, so much better error messages
//     // 2.Most of the Declaration are different from old versions
//     // 3.Algorithms take container instead of begin/end iter
//     vector<int> iVec2{5,7,2,1,6,3,87,3};
//     ranges::sort(iVec2);
//     utils::print(iVec2);
//     list<int> dList{1,2,5,-2,-5,23,-45};

//     // ranges::sort(dList);
//     // note: candidate template ignored: constraints not satisfied [with _Range = list<int> &, _Comp = ranges::less, _Proj = identity]
//     // note: because 'std::list<int> &' does not satisfy 'random_access_range'


//     using Coll = std::vector<int>;

//     algo(Coll{});
//     algo(deque<int>{});
//     algo(list<int>{});
//     algo(forward_list<int>{});


//     char str[100]= "Abdurrahim Uysal";

//     func(str,NullChar{});
// }