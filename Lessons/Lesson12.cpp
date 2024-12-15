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


// class Abdu{
// public:
//     constexpr Abdu(int x=0): mx{x}{}
//     // constexpr bool operator==(const Abdu& other) const { return mx == other.mx;};
//     bool operator==(const Abdu& other)const = default; // Default is constexpr if it is possible, so same with above
//     // auto operator<=>(const Abdu&)const = default;
//     [[nodiscard]] auto operator<=>(const Abdu&)const = default; 
//     // Default will keep all specificers, so it will be  nodiscard, if == is not defined and 
//     // just <=> is defaulted == will also keep same specifiers.

// private:
//     int mx;
// };

// class Date {
// public:
//     std::strong_ordering operator<=>(const Date& other) const noexcept{
//         if(auto cmp1 = my <=> other.my ; cmp1 != 0){
//             return cmp1;
//         }
//         if(auto cmp2 = mm <=> other.mm ; cmp2 != 0){
//             return cmp2;
//         }

//         return md <=> other.md;
//     }
// private:
// int my,mm,md; // Ordering is important, with this correct ordering we can just default <=>, above is just
// // example implementation
// };

// std::ostream& operator<<(std::ostream& os, std::strong_ordering sVal){
//     return os << (sVal == 0 ? "equal": sVal < 0 ? "less": "greater");
// }

// template <>
// struct fmt::formatter<std::strong_ordering>{
//     constexpr auto parse(format_parse_context& ctx) {
//         return ctx.begin();
//     }

//     // Format your type
//     template <typename FormatContext>
//     auto format(const strong_ordering& obj, FormatContext& ctx) {
//         // Use `format_to` to format the string representation
//         return fmt::format_to(ctx.out(), "StrongOrdering<{}>", (obj == 0 ? "equal": obj < 0 ? "less": "greater"));
//     }
// };

// struct Abdu2{
//     int mx{},my{};

//     void foo(){
//         // To have access to local member variables this needs to be captures
//         // = could be used , but not good, deprecated with c++20, this would copy ptr so changes in member vairables
//         // would affect the original value, = gives wrong impression that it is copy, so member var wont be affected
//         // [=,this] is also allowed with C++20
//         auto f = [this](int val){
//             return val *mx + my;
//         };
//     }

//     // Return f which captures this like above could be problematic due to lifetime issues
//     // So we can use copy of this instead to avoid this
//     auto foo2() {
//         auto f = [copy_this = *this](int val){
//         // auto f = [*this](int val){ // This is also copy capture ( supported from C++17)
//             // return val *mx + my; // Easy access if copy capture is done like above
//             return val *copy_this.mx + copy_this.my;
//         };
//         return f;
//     }
//     // "This" capture gets complicated, check attached lambda_this_capture.jpg
// };

// void func(){
//     // Can pass multiple args via variadics
//     auto f = [](auto &&... args){};

// }


// double i{};
// auto main() -> int {

//     constexpr Abdu n1{123};
//     constexpr Abdu n2{456};
//     constexpr auto comparison = n1 == n2;

//     vector<int> x(100'000,5);
//     vector<int> y{6,7};
//     fmt::print("y > x : {}\n", y > x); // Containers are compared with lexicographical comparison

//     fmt::print("y > x : {}\n",lexicographical_compare(x.begin(),x.end(),y.begin(), y.end()));
//     // With C++20 lexicographical_compare_three_way is added which will compare via <=>
//     auto result = lexicographical_compare_three_way(x.begin(),x.end(),y.begin(), y.end());// aka std::strong_ordering
//     fmt::print("lexicographical_compare_three_way result : {}\n",result);



//     // Lambdas

//     const int ten = 10;
//     //  mutable makes member functions not const.
//     // [ten = ten] -> init capture, so decltype(ten) wont be const even if right side is const
//     // auto f = [ten]() mutable { ++ten;}; // Syntax error: ten will be const member of lambda class, cant increment,
//     // auto g = [ten = ten]() {++ten;}; //  Syntax error: Cannot assign to a variable captured by copy in a non-mutable lambda
//     auto h = [ten=ten]() mutable {++ten;}; // OK, functions is non const( mutable) and ten is not const

//     auto one = [i=0]() -> decltype(i){return 1;}();
//     auto isSame = std::is_same_v<decltype(one), int>;
//     fmt::print("std::is_same_v<decltype(one), int>: {}\n", isSame);
    
//     // If lambda does not capture anything then it is stateless lambda.
//     // [] <TemplateParams> (parameter list) specifiers exception attr -> retType {code}
//     // <TemplateParams>  is added with C++20, optional
//     // (parameter list) is mandatory until C++23, after it ,it is optional if empty.

//     const auto lamd = [] (int x) { return x*7;};
//     auto lamd2 = [] (int x) { return x*7;};// Automatically constexpr if it is possible
//     constexpr auto val = lamd(5);
//     constexpr auto val2 = lamd2(5);
//     // Each lamda  type is unique
//     // const auto lamd = [] (int x) { return x*7;};
//     const auto lamd3 = [] (int x) { return x*7;};
//     constexpr auto isSameType = is_same_v<decltype(lamd),decltype(lamd3)>;  // False
//     // global or static lifetime objects can not be captured, but can be used. 

//     const int number35{35}; // Interestingly there is no need to capture for const vars
//     auto lambda35 = [] (int a){
//         return a*number35;
//     };
    

//     int arr[4]{};

//     auto lambda5 = [arr](){
//         using arrType = decltype(arr); // int[4] no ptr decay here
//     };

//     auto lambda6 = [arr=arr](){
//         using ptrType = decltype(arr); // ptrType = int*, decay here;
//     };

//     // For reference captured variable there is no need for mutable in lamda declaration
//     // , we can modify them without value, as we are changing the referenced value, not the reference itself

//     auto uptr = make_unique<std::string> ( 10'000,'a');
//     // Move cases need init capture , otherwise cant be moved to lambda.
//     auto lambda7 = [uptr = move(uptr)]  () mutable{
//         *uptr = "Abcd";};

//     // "This" capture gets complicated, check attached lambda_this_capture.jpg

//     // Lambda default is not noexcept
//     auto lambda8 = [](int x){return x*x;};
//     constexpr auto isNoexcept = noexcept(lambda8(43)); // False;
// }