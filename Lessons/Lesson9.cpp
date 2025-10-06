// #include <bitset>
// #include <cmath>
// #include <cstring>
// #include <functional>
// #include <iostream>
// #include <string>
// #include <optional>
// #include <strings.h>
// #include <utility>
// #include <variant>
// #include <format>
// #include <set>
// #include <list>
// #include <any>

// #include "fmt/core.h"

// #include "utils.hpp"

// using namespace std;
// struct AbduVis{
//     template <typename T, typename U>
//     void operator()(const T& t,const U& u){
//     // void operator()(const auto& t,const auto& u){ // Abbreviated template syntax c++20
//         cout << format("{} {}\n{} {}\n",typeid(T).name(),typeid(U).name(),t,u);
//         // format C++20 , original is from fmt library
//     }
// };

// // Variant can be used for inheritance, unlike unions
// class Derived : public variant<int,string>{};

// struct A{
//     void foo(int){}
// };

// struct B{
//     void foo(double){}
// };

// struct Der : A,B{};

// struct Der2 : A,B{
//     using A::foo;
//     using B::foo;

// };

// template<typename ...Args>
// struct Der3 : Args ...{

// };

// struct A3{ void fa();};
// struct B3{ void fb();};
// struct C3{ void fc();};

// template<typename ...Args>
// struct Der4 : Args ...{
//     using Args::foo...;
// };

// struct A4{ void foo(int);};
// struct B4{ void foo(double);};
// struct C4{ void foo(long);};

// auto fn1 = [] (int x){ return x*4;};
// auto fn2 = [] (int x){ return x*4;};
// auto fn3 = [] (int x){ return x*4;};

// // instead of decltype(fn1) we can even use decltype([] (int x){ return x*4;}) with c++20
// // Lambdas now (cpp20) can be used in unevaluated context
// struct LambdaDerived : decltype(fn1),decltype(fn2),decltype(fn3){

// };
// template <typename ...Args>
// struct Abdu : Args ... {

// };


// template <typename ...Args>
// struct Overload : Args ... {

// };

// template <typename T, typename U>
// struct  Pair{
//     Pair(const T&t,const U&u):mFirst(t),mSecond(u){};

//     T mFirst;
//     U mSecond;
// };

// //Deduction guide
// template<typename T,typename U>
// Pair(T,U) -> Pair<T,U>;

// //Easier deduction guide example
// template<typename T>
// class MyClass{
// public:
//     MyClass(const T&){};    
// };

// MyClass(const char*) -> MyClass<std::string>;

// template <typename ...Args>
// struct Overload2 : Args ... {
//     using Args::operator()...;
// };

// // N.Ergin does not support this syntax of main :)
// auto main() -> int {


//     variant<int,double,string> vx(3.14);
//     variant<long,int,string> vy(in_place_index<2>,6,'A');
    
//     std::visit(AbduVis{},vx,vy); // This needs 9 function to be defined
//     // int,long or int int or ..... string string

//     Derived d = {"hello"};
//     d.emplace<0>(77);
//     std::cout << get<0>(d) << "\n";

//     Der myDer;
//     // myDer.foo(1.25);  // Compile error ambiguity
//     myDer.A::foo(1); // ok
//     myDer.B::foo(1.25); // Ok 

//     Der2 der2; // Now these are overload, so ok, no ambiguity
//     der2.foo(1.2);
//     der2.foo(5);

//     Der3<A3> x;// can call fa
//     Der3<A3, B3> y;// can call fa fb
//     Der3<A3, B3, C3> z;// can call fa fb fc

//     Der4<A4> x2;// can call foo(int)
//     Der4<A4, B4> y2;// can call foo(int/double)
//     Der4<A4, B4, C4> z2;// can call foo(int/double/long)

//     auto fn = [](int x){return x*5;};
//     decltype(fn) fx; // ok with C++20, error before as lambda default const is deleted

//     // Stateless lambda = no capture, it has default constructor with c++20
//     // Lambda with captures still does not have default constructor 
//     int num{5};
//     auto fn2 =  [num](int x){return 5*x;};
//     // decltype(fn2) fx2; // compile error , stateful lambda does not have def. constructor.
//     decltype(fn2) fx2(fn2);

//     auto comparatorFunc = [] (int x, int y){
//         return abs(x) < abs(y);
//     };
//     set<int, decltype(comparatorFunc)> myset(comparatorFunc); // Works with c++17, to construct comparatorFunc we 
//     // need to pass it as argument
//     set<int, decltype(fn)> myset2; // Works with c++20 ,now lambda has default constructor
//     set<int, decltype([] (int x, int y){ return abs(x) < abs(y);})> myset3; // Works with c++20 
    
//     auto f1 = [](){};
//     auto f2 = [](){};
//     auto f3 = [](){};
//     Abdu<decltype(f1),decltype(f2),decltype(f3)> abdu;

//     Overload overload{
//         [](int a){return a*a;},
//         [](int a){return a*2;},
//         [](int a){return a*3;},
//         [](int a){return a*4;},
//     };// Creates Overload<LambdaType1,LambdaType2 ... > thanks to CTAD C++17, however this needs deduction guide in C++17
//     // So we need c++20 for above to work

//     int a[10]{};
//     double b[10]{};
//     Pair p(a,b); // Without deduction guide : T = int[10] U = double[10], so we can not initialize array[10] with = 
//     // cannot initialize an array element of type 'double/int' with an lvalue of type 'const double/int[10]'
//     // if constructor was Pair(T t,U u). this works as deduction will be int/double*
//     // With deduction guide , T = int* , U = double*

//     MyClass m("Abdu");// Without deduction guide T is char[5], with guide it is std::string

//     list<int> myList{3,5,7};
//     vector myvec(myList.begin(),myList.end()); // vector<int> ,not vector<iter>, Thanks to deduction guide  
//     // template<typename Iter> vector(Iter,Iter) -> vector<typename iterator_traits<Iter>::value_type>;

//     //Overloader idiom, Overlaoded class needs deduction guide on C++17, for 20 + no need for aggregate types
//     // template<typename ...Args> Overload2(Args...) -> Overload2<Args...>;
//     variant <int,double,long,string,char> varX{"Abdu"};
//     visit(Overload2{
//         [](int){cout<< "int\n";},
//         [](double){cout<< "double\n";},
//         [](long){cout<< "long\n";},
//         [](string){cout<< "str\n";},
//         [](auto){cout<< "Other Types\n";}
//     }, varX);

//     // if variant is called, old value destroyed then while new value is constructed exception happened
//     // now variant is in a bad state , old value is lost, new one is not constructed 
//     // This can be checked by variant.valueless_by_exception()
//     auto isCorrupt = varX.valueless_by_exception();
//     using vType = decltype(varX);
//     constexpr auto varSize = variant_size_v<vType>; // 5 possible types

//     using oneIndexType = variant_alternative_t<1,vType>; // double

//     // Variant can be used for error handling code for example
//     // enum ErrorType{sytem,archive,log};
//     // std::variant<Data,ErrorType> foo()
    
//     // Variant can be used instead of dynamic polymorphism to avoid having vPtr, vTable (memory)
//     // dereferensing when accessing ( runtime), dynamic memory allocation ( high runtime cost)
//     // There are considerations if class structure is mostly predetermined static polymorphism via variant can be good
//     // If it is more "agile" dynamic polymorphism can be good, but more complex than these 2 (memory, code usability etc.)

//     // Any
//     any anyVar;
//     any anyVar2{};
//     cout << format("anyVar Has Value : {}\n",anyVar.has_value());
//     cout << format("anyVar2 Has Value : {}\n",anyVar.has_value());

//     any anyVar3{12};
//     any anyVar4{5.6};
//     any anyVar5{"Morria"};
//     any anyVar6{std::vector<int>{1,34,5,67,42}};


//     anyVar4 = 3;// Can change type  at runtime
//     // Any does not need to hold value in itself, implementation defined.
//     // For big sizes it generally does dynamic allocation, for smaller sizes keeps it in buffer ( Implementation defined)

//     // typeid(int) return typeInfo object, copy constructor is deleted.
//     const auto& r = typeid(std::string); // ok
//     // const auto r2 = typeid(std::string); // not ok

//     // Any is different than void ptr , it also has reference to typeInfo()

//     if(anyVar3.type() == typeid(int)){
//         cout << "anyVar3 holds int\n";
//     } // else if anyVar3.type() == typeid(string) etc

//     if(anyVar.type() == typeid(void)){
//         cout << "anyVar does not hold anything\n";
//     }

//     cout << any_cast<int>(anyVar3) << "\n";
//     try{
//         cout << any_cast<float>(anyVar4) << "\n";
//     } catch ( const std::bad_any_cast& ex){
//         fmt::print("anyVar4 does not hold float\n");
//     }

//     //  any_cast<int>(anyVar3) = 5; // Cant assign to PRValue
//     any_cast<int&>(anyVar3) = 5;

//     any anyStr{in_place_type<string>, 5 ,'a'};
//     fmt::print("{}\n",any_cast<string>(anyStr));
//     any anyStr2{in_place_type<string>, 5 ,'b'};
//     anyStr2.reset();
//     // anyStr2.has_value() 0 
//     anyStr2.emplace<string>(10,'b');
//     auto& anyStr2Ref = any_cast<string&>(anyStr2);
//     fmt::print("{}\n",anyStr2Ref);

//     //AnyStr2 is moved to anyStr3
//     auto anyStr3 = any_cast<string&&>(std::move(anyStr2));

//     vector<any> avec{13,2.54, "abdu",67L, "alex"s};

//     for(const auto& a:avec){
//         // similar to variant if cast is incorrect, nullptr is returned
//         if( auto pi = any_cast<int>(&a)){ 
//             fmt::print("{}\n",*pi);
//         } else if( auto pd = any_cast<double>(&a)){
//             fmt::print("{}\n",*pd);
//         } else if( auto pc = any_cast<const char*>(&a)){
//             fmt::print("{}\n",*pc);
//         } else if( auto pl = any_cast<long>(&a)){
//             fmt::print("{}\n",*pl);
//         } else if( auto ps = any_cast<string>(&a)){
//             fmt::print("{}\n",*ps);
//         }
//     }
// }   