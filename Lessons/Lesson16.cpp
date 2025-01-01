// #include <algorithm>
// #include <bitset>
// #include <cmath>
// #include <cstddef>
// #include <cstring>
// #include <functional>
// #include <iostream>
// #include <iterator>
// #include <numeric>
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

// #include "fmt/core.h"
// #include "fmt/format.h"

// #include "utils.hpp"

//  using namespace std;

//  struct Abdu{
//     int a,b,c;
// };

// struct Abdu2{
//     int a[5];
//  };

//  struct Abdu3{
//     int x,y;
//     const int& rA;
//     int && rB;
//  };

 

//  int foo(){ return 0;}

//  int bar(){ return 0;}

//  struct Abdu4{
//     int a,b;
//     struct Nested{
//         int x,y,z;
//     }c;
//  };

// //  template<typename T,T num>  // Before C++20 we need to use this
//  template< auto num> // With C++20 auto support is added
//  int func( ){
//     return num*5;
//  }

//  template <typename T>
//  class Lazy{
//     public:

//     constexpr Lazy() = default;
//     T& get(){
//         static T global;
//         return global;
//     }

//     // T& operator*(){
//     //     return get();
//     // }
//  };

//  template <typename Tag,typename T>
//  class LazyTag{
//     public:

//     constexpr LazyTag() = default;
//     T& get(){
//         static T global;
//         return global;
//     }

//  };

//  template <typename T,auto = []{}> // each lambda will have different type
//  class LazyImproved{
//     public:
//     constexpr LazyImproved() = default;
//     T& get(){
//         static T global;
//         return global;
//     }
//  };

//  constexpr int constexprFunc(int x){
//     return x*5;
//  }

//  constexpr double mySqrt(double){
//     if(is_constant_evaluated()){
//         // Will run if function is used in constexpr required context
//     } else {
//         // all other contexts
//     }
//     return 0.0;
//  }

//  constexpr int getVal(int idx){
//     int ar[] = {2,3,54,6,7,8,89};
//     return ar[idx];
//  }

//  constexpr int constexprThrow(int idx){
//     if( idx <=0){
//         throw runtime_error("Unsupported idx <=0");
//     }
//     return idx;
//  }

//  constexpr int returnNthSmallest(int idx){
//     int a[10] = {1,3,5,7,8,12,0,6,11,65};
//     std::sort(begin(a),end(a)); // constexpr algorithms yeayy.
//     return a[idx];
//  }

//  constexpr int factorial(int n){
//     return n < 2 ? 1 : n * factorial(n-1);
//  }

//  constexpr double getE(int n){
//     double * p = new double[n];
//     for(int i{};i < n ; ++i){
//         p[i] = 1./ factorial(n);
//     }
//     auto sum = accumulate(p, p + n, 0.);
//     delete []p; // if not deleted it is compile time error

//     return sum;
//  }


//  constexpr int constexprFuncWithVec(int n){
//     vector vec{1,4,5,7,8,3,1,1};

//     return accumulate(vec.begin(),next(vec.begin(),n), 0);
//  }

//  consteval int Square(int x){ // Must run in compile, will always run in compile time
//     return x*x;
//  }


// auto main() -> int {
//     auto up = make_unique<Abdu>(1,2,3); // Works with C++20 aggregate rules
//     int a[]{3,5,7};  // Works with C++20 aggregate rules
//     int b[](3,5,7);  // Works with C++20 aggregate rules

//     Abdu2 a2{2,3,6};
//     // Abdu2 a3(2,3,6); // Does not work
//     Abdu2 a4({2,3,6}); // Does  work

//     array<int,4> ar{1,2,3};
//     // array<int,4> ar2(1,2,3); // Does not work
//     array<int,4> ar3({1,2,3});

//     Abdu aImplicit(5,7.8,9); // Gives Warning but work, with {} this does not compile.

//     Abdu3 abd3 = {3,5,foo(),bar()}; // Lifetime extension, rA, rB are valid and ok
//     Abdu3 abd4 {3,5,foo(),bar()}; //  Using rA, rB are undefined behaviour, no good explanation though

//     Abdu4 a41 = {1,2,{6,7,7}};
//     Abdu4 a42 = {1,2,6,7,7}; // Works because Nested is also aggregate
//     // Abdu4 a43 = (1,2,{6,7,7}); // Incorrect. does not compile
//     Abdu4 a44 = {1,2,(6,7,7)}; // Compiles, but incorrect c xyz = 700 due to ',' only assigning last value to x;
    
//     // For reference members life extension does not work
//     // For nested type members , {} must be used

//     Lazy<int> lazyX;
//     Lazy<int> lazyY;
//     lazyX.get()++;
//     cout << lazyY.get() << "\n"; // LazyX/Y are same , how can we get differen lazy<int> ? 

//     // This compiles, kind of forward declaration, IncompleteAbdu is incomplete type
//     struct IncompleteAbdu *p = nullptr; 
//     struct IncompleteAbdu2;
//     struct IncompleteAbdu2 *p2 = nullptr;

//     LazyTag<struct X,int> lazyTagX;
//     LazyTag<struct Y,int> lazyTagY;
//     lazyTagX.get()++;
//     cout << lazyTagY.get() << "\n"; // Now LazyTagY is different than LazyTagX
    
//     LazyImproved<int> lazyImprovedX;
//     LazyImproved<int> lazyImprovedY; // Both are different , no need for tag !

//     int xVal = constexprFunc(5); // No guarantee that it will run on compile time
//     constexpr int constexprX = constexprFunc(7); // Compuile time


//     // constexpr int valOfIdx20 = getVal(20); // Syntax error : cannot refer to element 20 of array of 7 elements in a constant expression
//     int valOfIdx20 = getVal(20); // Undefined behaviour
//     cout << valOfIdx20 << "\n"; // UB


//     constexpr auto result1 = constexprThrow(2);
//     // constexpr auto result2 = constexprThrow(0); // Compile time error due to exception 
//     // note: subexpression not valid in a constant expression
//     // 121 |         throw runtime_error("Unsupported idx <=0");
//     // Below is also compile time error even with catch
//     // try{
//     //     constexpr auto result3 = constexprThrow(-1);
//     // } catch(const exception& ex){
//     //     cout << "Unsupported idx:  " << ex.what() << "\n";
//     // }

//     constexpr int smallest = returnNthSmallest(0);
//     constexpr int biggest = returnNthSmallest(9);
//     constexpr double mathematicalE = getE(10);

//     int iVal = 5;
//     // Square(iVal); // Error must be constexpr var, as square is consteval

//     //     error: call to consteval function 'Square' is not a constant expression
//     //     229 |     Square(iVal); 
//     //         |     ^
//     //   /workspaces/Week1---Value-Category/Lessons/Lesson16.cpp:229:12: note: read of non-const variable 'iVal' is not allowed in a constant expression

//     // If static variables are declared in a file, they are constructed in order
//     // However if variables are in different files there is no construction order guarantee. 
//     // This is called static initialization (order) fiasco ( You can check Jonathan Muller talks)

//     // Global variables and static member/nonmember variables have static storage
//     // Lifetime and storage duration are related but not same.
//     // Static local variables have static storage, but their lifetime starts when parent function is called
//     // Global varibles are initialized in two phases
//     // Static init : Memory is set to 0
//     // Dynamic init : initialization expression is executed

//     // Order of dynamic initialization is not specified ( so we have the static init fiasco)
//     // Probably related jonathan muller talk : https://www.youtube.com/watch?v=6EOSRKMYCTc

// }