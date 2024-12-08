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

// #include "utils.hpp"

//  using namespace std;

// struct MyStruct{
//     constexpr MyStruct(int x,double y) : mx{x}, my{y}{}
//     int mx;
//     double my;

// };

// class MyClass{
// public:
//     constexpr MyClass(int x,double y) : mx{x}, my{y}{}
//     int getX()const { return mx;}
//     double getY()const { return my;}
// private:
//     int mx;
//     double my;
// };

// namespace std{

//     template <>
//     struct tuple_size<MyClass> : integral_constant<size_t,2u>{};

//     template <>
//     struct tuple_element<0,MyClass> {using type = int;};
//     template <>
//     struct tuple_element<1,MyClass> {using type = double;};

// }

//     template <std::size_t N>
//     auto get(const MyClass& m){
//         if constexpr(N ==0) {
//             return m.getX();
//         } else if constexpr (N ==1){
//             return m.getY();
//         } else {
//             static_assert(0);
//         }
//     }

// class ClassForComparison{
// public:
//     ClassForComparison(int x) : mx{x}{}
//     auto operator<=>(const ClassForComparison&) const = default;
//     // If spaceship is defaulted but == not declared, then compiler will define and default it

//     // if only == is defaulted then spaceship is not declared
// public:
//     int mx;
// };


// template<typename T, typename U>
// void printCompare(const T& t,const U& u){
//     using resultType = compare_three_way_result_t<T,U>;
//     string stype = typeid(resultType).name();
//     fmt::print("Compare result type {}\n",stype);

//     auto result = t <=> u;
//     fmt::print("Result of Comparison: ");
//     if(result == 0){
//         if constexpr (std::is_same_v<resultType,std::strong_ordering>){
//             fmt::print("Equal\n");
//         } else {
//             fmt::print("Equivalent\n");
//         }
//     } else if ( result > 0){
//         fmt::print("Greater\n");
//     }  else if ( result < 0){
//         fmt::print("Less \n");
//     } else {
//         fmt::print("Orordered\n");
//     }
// }

// class Person{
// private:
//     string name;
//     int age;
//     double salary;
// public:
//     Person(const char*p , int a, double s ):name{p},age{a}, salary{s}{}
//     // auto operator<=>(const Person& other){
//     // partial_ordering operator<=>(const Person& other){
//     auto operator<=>(const Person& other) -> common_comparison_category_t<
//                                                 decltype(name <=> other.name),
//                                                 decltype(age <=> other.age),
//                                                 decltype(salary <=> other.salary)> {
//         if(auto cmp = name <=>other.name; cmp != 0 ){
//             // return static_cast<partial_ordering>(cmp);
//             return cmp;
//         }
//         if(auto cmp = age <=> other.age;cmp!=0){
//             // Cast is necessary  if return type is different in branches as 
//             // comparison of double is partial_ordering , others are strong ordering 
//             // Or instead of auto we can return partial_ordering.
//             // There is a nice type trait instead common_comparison_category_t
//             // return static_cast<partial_ordering>(cmp); 
//             return cmp; 
//         }
        
//         return salary <=> other.salary;

//         // if we want to return strong ordering even though we have double members
//         // then we can do ( below will convert partial ordering to strong order following specific rules)
//         // return strong_order(salary,other.salary)
//     }


// };

// auto main() -> int {
   
//     using TpType = tuple<int,double,long>;
//     // Array has tuple interface
//     using ArrayTpType = std::array<double,20>;
//     constexpr auto numOfTypes = tuple_size_v<TpType>;
//     tuple_element_t<0,TpType> a; // int
//     tuple_element_t<4,ArrayTpType> b; // int

//     auto [x,y] = make_tuple(10,4.5);
//     auto f = [x,y] {return x+y;};// Does not work c++17, works fine with c++ 20, 
//     // with c++ 17 x,y needs to be captured by reference [&x,&y],

//     constexpr MyStruct m(3,6);
//     // constexpr auto [x1,y1] = m; // error: decomposition declaration cannot be declared 'constexpr'\

//     MyClass myClass{3,7.5};
//     using std::get;
//     auto [xVal,yVal] = myClass;    // MyClass has related functions implemented for tuple access


//     // Spaceship ( Three way comparison) Operator <=> C++20

//     // Equality operators: == !=
//     // Relational operators : < <= > >=
//     // classes overload < and = , and others use those 2
//     //   a!=b -> !(a==b) etc

//     // a > b -> b < a
//     // a>= b -> !(a < b)
//     // a<= b -> !(b < a)

//     // But equalities above are not always correct, ie below : 
//     double d1{NAN};
//     double d2{3.56};

//     string str1{"abdu"};
//     string str2{"uysal"};
//     // str.compare() // does 3 way comparison
//     // strcmp(s1,s2) // does 3 way comparison
//     auto val = str1 <=> str2; //  (aka std::strong_ordering)
//     if(str1 <=> str2 < 0){ // str1 <=> str2 -> returns a StrongOrdering type which has conversion to int
//         fmt::print("Correct\n");
//     } else {
//         fmt::print("Incorrect\n");
//     }

//     auto doubleComparsionResult = 9.0 <=> 10.0; // std::partial_ordering

//     // With C++20 now == and <=> are primary operators, while !=, < , > ,<= , >= atr secondary
//     // If primary operator is defined all secondaries can be called without defining them
//     // Secondaries can be rewritten by using primaries.
    
//     // if == is defined for object m all the following calls are valid and not an error : 
//     // m != 5 , 5 == m . 5!= m 

//     ClassForComparison m1{12}, m2{67};

//     fmt::print("m1 < m2 : {}\n",m1 < m2);
//     fmt::print("m1 <= m2 : {}\n",m1 <= m2);
//     fmt::print("m1 > m2 : {}\n",m1 > m2);
//     fmt::print("m1 >= m2 : {}\n",m1 >= m2);
//     fmt::print("m1 == m2 : {}\n",m1 == m2);
//     fmt::print("m1 != m2 : {}\n",m1 != m2);

//     // Default comparison is done in declaration order of member variables.

//     // If values in comparison can be either equal, smaller or bigger than each other than Strong_ordering is returned
//     // Int , long etc.
//     // Barry Revzin article : https://brevzin.github.io/c++/2019/07/28/comparisons-cpp20/

//     // There is weak_ordering
//     // If there are some values which cant be compared than partial_ordering is used.

//     // so a <=> b is either strong_ordering, weak_ordering or partial ordering.

//     strong_ordering::equal;
//     strong_ordering::equivalent;
//     strong_ordering::less;
//     strong_ordering::greater;
 
//     weak_ordering::equivalent;
//     weak_ordering::less;
//     weak_ordering::greater;

    
//     partial_ordering::equivalent;
//     partial_ordering::less;
//     partial_ordering::greater;
//     partial_ordering::unordered;


//     printCompare(4,12);
//     printCompare(4,12.0);
//     printCompare(4.5,12.0);
//     printCompare(6.7,6.7);
//     printCompare(6.7,NAN);

//     Person p1{"john",12};
//     Person p2{"abdu",12};

//     fmt::print("{}\n" , p1 > p2);

// }