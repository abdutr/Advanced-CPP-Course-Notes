// #include <algorithm>
// #include <bitset>
// #include <cmath>
// #include <cstring>
// #include <functional>
// #include <iostream>
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


//  template <typename... Args>
//  void print(Args&&... args){
//     (void)std::initializer_list<int>{((std::cout << std::forward<Args>(args)),0)...};
//     // list will have 0s , due to ',', however left of comma will run so it will print everything
//     // Just an extra way to handle variadic;
//  }

// template<typename F>
//  void doesThrow1(F&& f){
//     if constexpr(noexcept(f(5))){
//         fmt::print("no throw\n");
//     } else {
//          fmt::print("may throw\n");
//     }
//  }

//  template<typename F>
//  void doesThrow2(F&& f){
//     if constexpr(is_nothrow_invocable_v<F, int>){
//         fmt::print("no throw\n");
//     } else {
//          fmt::print("may throw\n");
//     }
//  }

//  class Abdu{
//     public:
//     Abdu(){
//         static auto _{[](){
//             fmt::print("This code must run only once\n"); return 0;
//         }()}; 
//     }
//  };

// // Lamdas can capture variadic input variables no problem,
// //  but init capture support is added with C++20
//  template<typename... Args>
//  auto delay_invoke_foo(Args... args){
//     return [...args = std::move(args)]()-> decltype(auto){
//         return foo(args...);
//     };
//  }

// auto main() -> int {

// // using std::function to receive lamda is not as performant as lambda
// // std::function may do dynamic allocation and will use more memory than lambda
// // It is better to use alternatives instead of std::function if possible

// // Lambda is local, can (kindof) bypass lack of nested functions in C++
// // Templates cannot be local , so lambda can be used inside a function etc.
// // Lambda is advatantegous as it makes inlining and optimization easier for compiler


//     print("1 ","2\n");
//     auto fn = [](auto&&... args){
//         print(std::forward<decltype(args)>(args)...);
//     };

//     fn(45 , " is ", "a ","number\n");

//     auto up = make_unique<string>("Abdu");
//     auto f = [up = std::move(up)]{return *up + "Uysal";};
//     if(up){
//         fmt::print("up full\n");
//     } else {
//         fmt::print("up empty\n");
//     }
//     fmt::print("{}\n",f());
//     if(up){
//         fmt::print("up full\n");
//     } else {
//         fmt::print("up empty\n");
//     }

//     vector<string> svec(1000);
//     string str{"Alex"};

//     // Option1 
//     auto iter = find_if(svec.begin(),svec.end(),
//     [str = str + "Ciprian"](const string& s){
//         return s == str;
//     }
//     );

//     //Option 2 
//     auto iter2 = find_if(svec.begin(),svec.end(),
//     [&str ](const string& s){
//         return s == str + "Ciprian";
//     }
//     );

//     // Option 1 is faster as str + "Ciprian" is only computed once online option 2
//     // calculating it for 1000 times.

//     auto throwingFunc = [](int x)  { return x*5;};
//     auto noThrowingFunc = [](int x) noexcept  { return x*5;};
//     doesThrow1(throwingFunc);
//     doesThrow1(noThrowingFunc);
//     doesThrow2(throwingFunc);
//     doesThrow2(noThrowingFunc);

//     // Stateless lambdas can be converted to function ptr implicitly
//     auto statelessLambda = [](int x) { return x*5;};
//     int (*fp)(int) = statelessLambda;
//     fmt::print("{0}\n", fp(5));

//     int num{5};
//     auto statefulLambda = [&num](int x) { return num*5;};
//     // int (*fp2)(int) = statefulLambda;  // Not possible , has capture stateful


//     // Positive lambda
//     char c = 'a';
//     +c ; // with + it is R value + also cause integral promotion;

//     auto positiveLambda = +[](int x){return x*5;}; //variable positiveLambda, Type: int (*)(int)
//     // Above works as lambda has type conversion to function ptr, so + triggers it.

//     // Immediately called lambdas are very useful for initialization (const) variables with complex
//     // logic, or during class constructor initializer list.

//     // Stylistic but, if you believe it is easy to miss immediately called lambda you can use invoke
//     const int a = [] (){auto val =5 ; return val;}(); 
//     const int b = std::invoke([] (){auto val =5 ; return val;});

//     // Lets say we want some function to be called once
//     Abdu abdu1;
//     Abdu abdu2;  

//     // default constructor and copy constructor of lambdas are no longer deleted with C++20
//     // Above is Only true for stateless lambdas

//     auto  comparator = [] (int a, int b){
//         return abs(a) < abs(b);
//     };
//     set<int,decltype(comparator)> x; // Works in C++20
//     set<int,decltype(comparator)> x2(comparator); // Needee in C++17

//     // Now lambdas can be used in unevaluated context
//     // set<int,decltype(//define lambda here)> x; // Works in C++20

//     auto templateLambda = []<typename T>(T x,T y){};
//     auto templateLambda2 = []<typename T>(const vector<T> vec){
//         return vec.size();
//     };
//     vector<int> vecInt(5);
//     vector<int> vecDouble(7);
//     fmt::print("{}\n",templateLambda2(vecInt));
//     fmt::print("{}\n",templateLambda2(vecDouble));

//     auto perfectForwardLambda = []<typename T>(T&& input){
//         a(std::forward<T>(input));
//     };

//     auto basicLambda = [] (auto val){ return val*6;}; 
    
//     //If we want to call lambda above with a double but want template type to be int
//     constexpr auto result = basicLambda.operator()<int>(5.7); // 30 


// }