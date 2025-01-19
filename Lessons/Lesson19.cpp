#include <algorithm>
#include <bitset>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <random>
#include <source_location>
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
#include <ranges> 

#include "fmt/core.h"
#include "fmt/format.h"


#include "utils.hpp"

using namespace std;

template<copyable T>
class MyClass{};

template<typename F,typename Iter>
void bar(F func,Iter iter) requires indirect_unary_predicate<F,Iter>{
    fmt::print("{}\n",func(*iter)); // Function should be callable with dereferenced Iter
}

void func(std::invocable<int> auto f,int x){
    f(x);
}

void func(std::invocable<int,double> auto f,int x,double y){
    f(x,y);
}


// template<typename _Tp>
// concept range = requires(_Tp& __t)
//   {
// ranges::begin(__t);
// ranges::end(__t);
//   };

void func2(std::ranges::range auto &rangeVar){};

struct Abdu{
    int x : 4{7}; // Before c++20 bitfield members could not take default member initializer
    int y : 3{2}; // But now it is ok with C++20;
    int z : 1{1};
};

template<typename T>
void funcWithDependentTypeArg(typename T::value_type){  // Only typename works here, we cant write class
// typename is required above to distinguish between class static member var or dependant type
}

template<typename T>
struct PointerTrait{
    using Pointer = void*;
};

template <typename T>
struct Abdu2{
    // using Ptr = typename PointerTrait<T>::Pointer; //Before c++20 typename was required here
    using Ptr = PointerTrait<T>::Pointer; // Not needed anymore, as it is clear that it can only be a type here

    T::Abdu bar(T::Abdu p){ // no need for typename here and below as well with C++20
        return static_cast<T::Abdu>(p);
    }
};

template<typename T>
concept cAbdu = requires (T::value_type x){
    x.foo();
};

template <typename T,typename U>
constexpr bool CmpLess(T t, U u){
    using UT = std::make_unsigned_t<T>;
    using UU = std::make_unsigned_t<U>;

    if constexpr ( is_signed_v<T> == is_signed_v<U>){
        return t < u;
    } else if constexpr ( is_signed_v<T> ){
        return t<0 ? true : UT(t) < u;
    } else {
        return u < 0 ? false : t < UU(u);
    }
}

struct A{
    int x;
    bool b;
};

template<typename T>
using fIntPair = pair<int,T>;

namespace X::Y::inline Z{
    int d;
}

namespace X::Y::Z{ // This is fine
    int c;
}

namespace X::Y{
    int b;
}

struct Abdu3{
    Abdu3(Abdu3&&) noexcept = default; // Default deduce noexcept from member variables, however we can provide it (C++20)
};

void sourceLocPrinter(source_location sl = source_location::current()){
    fmt::print("File name {} func name {}\n line no {} column no {}\n",
        sl.file_name(),sl.function_name(),sl.line(),sl.column());
}

source_location func(){
    auto sl = source_location::current();

    return sl;
}


enum class Color {white,yellow,blue,black};

namespace abduNamespace{

    class Uys{
        public:
        enum class Color {white,yellow,blue,black};
    };

    using enum Uys::Color;
}

auto main() -> int {
    MyClass<int> myClassVar1;
    MyClass<string> myClassVar2;
    // MyClass<unique_ptr<int>> myClassVar2; // Not copyable

    const auto pred = [](int x){return x%5 ==0;};
    vector ivec{3,5,7,8,3,2};

    bar(pred,ivec.begin());

    auto beg = ranges::begin(ivec);
    auto end = ranges::end(ivec);
    // So ivec satisfies range concept

    int x = -1;

    x <<=1 ; // Was UB before c++20, not it is not with C++20
    fmt::print("{0:032b} {0}\n",x);
    x =-1;
    x >> 1; // This was implementation defined in C and C++17, implementation could do logical/arithmetic right shift
    // With C++ 20 it is always arithmetic ( so sign bit is fed) so x = -1
    fmt::print("{0:032b} {0}\n",x);

    const char* p1 = "abdu";
    const char* p2 = "abdu";

    auto areTheySame = p1 == p2;
    fmt::print("areTheySame : {} \n",areTheySame); // Implementation defined for me it was false;

    for(int i{}; i < size(ivec);++i){ // Comparing int and unsigned it , gives warning

    }

    for(int i{}; i < ssize(ivec);++i){ // With C++20 ssize added , signed size, so gives no warning

    }

    // With C++20 <bit> header is added with many functionality like below, all constexpr
    // bit_ceil, has_single_bit , countl_zero, countr_one, popcount , bit_width;
    // bit_cast;
    constexpr auto val  = rotl(24u,2); // it is constexpr

    uint16_t uint16Val = 0b0010'1010;

    fmt::print("{0:016b} {0:8}\n" , uint16Val);
    fmt::print("{0:016b} {0:8}\n" , rotl(uint16Val,2));
    fmt::print("{0:016b} {0:8}\n" , rotl(uint16Val,-2));
    fmt::print("{0:016b} {0:8}\n" , bit_floor(uint16Val));
    fmt::print("{0:016b} {0:8}\n" , bit_ceil(uint16Val));

    // How to  check if number is power of 2

    auto isXPowerOf2 = x && !(x && (x-1)); // Check if x != 0 and x & (x-1) = 0

    // There is conexpr C++20 func doing it now
    // Most of the following requires unsigned type, they are restrained for this
    fmt::print("Is power of 2 {} : {}\n",uint16Val, has_single_bit(uint16Val));
    fmt::print("Is power of 2 {} : {}\n",256, has_single_bit(256u));

    countl_zero(5u); // Count leading 0s
    fmt::print("Count leading 0 {}\n",countl_zero(uint16Val));
    fmt::print("Count leading 1 {}\n",countl_one(uint32_t(0b1111'0000'0000'0000'1111'0000'0000'0000)));
    fmt::print("Numbber of bits that are set(1) {}\n",popcount(uint32_t(0b1111'0000'0000'0000'1111'0000'0000'0000)));
    fmt::print("Bitwith  {}\n",bit_width(uint32_t(0b1111'0000'0000'0000'1111'0000'0000'0000)));
    fmt::print("Bitwith  {}\n",bit_width(uint32_t(0b0000'0000'0000'0000'1111'0000'0000'0000)));

    constexpr float e = 2.71828f;
    float e2 = 2.71828f;
    auto eInt = static_cast<int>(e); // 2
    auto eIntUB = *reinterpret_cast<int*>(&e2); // UB

    union Fint {
        float f;
        int i;
    };

    Fint fn = {e}; 
    auto iVal = fn.i; // This not UB in C, however in C++ it is UB
    // But we may want to use value as integer how can we do it ? 

    int intVal{};
    memcpy(&intVal,&e,sizeof(e)); // We could do memcpy

    // instead we can use bitcast with C++20

    constexpr auto uVal = bit_cast<unsigned int, float>(e);
    // constexpr auto uVal2 = bit_cast<unsigned long long, float>(e); // sizes are different between ull and f so error

    // endianness test could be done in runtime.
    // How to check if systyem is big/little endian

    int intValX = 1;
    if(*(char *)&intValX){
        fmt::print("Little endian\n");
    } else {
        fmt::print("Big endian\n");
    }

    static_assert( std::endian::native == std::endian::little); // My system is little endian , detected in compile time

    if constexpr(std::endian::native == std::endian::little){
        // system is little endian
    } else if constexpr (std::endian::native == std::endian::big) {
        // system is big endian
    } else {
        // system is mixed
    }

    // For comparing mixed sign variables we can now use cmp_greater ( again C++20)
    int signedInt = -1;
    unsigned  unsignedInt = 567;

    if(cmp_greater(signedInt , unsignedInt)){
        fmt::print("{} is greater than {}\n",signedInt , unsignedInt);
    } else {
        fmt::print("{} is equal/smaller than {}\n",signedInt , unsignedInt);
    }

    if(CmpLess(signedInt , unsignedInt)){
        fmt::print("{} is greater than {}\n",signedInt , unsignedInt);
    } else {
        fmt::print("{} is equal/smaller than {}\n",signedInt , unsignedInt);
    }

    int arr[20]{};
    // arr[1,2,3] = 19 ; // means arr[3] = 19, however it is deprecated with C++20 

    // Now (C++20)void* to bool conversion is narrowing conversion so will error out with {}

    void *voidPtr{};
    // A aVar{5,voidPtr}; //void *' cannot be narrowed to 'bool' in initializer list  note: insert an explicit cast to silence this issue

    auto p = new int[]{1,2,3,4}; // This is valid with C++20, before we need to provide array size inside []

    pair pairVar{1,7.8};
    fIntPair f{2,6.7}; // This is valid with C++20, CTAD now applies for alias template,
    X::Y::Z::c = 5;
    X::Y::d = 7;

    constexpr auto sourceLoc = source_location::current();
    constexpr auto sourceFileName = sourceLoc.file_name();
    constexpr auto sourceFunctionName = sourceLoc.function_name();
    constexpr auto sourceLine = sourceLoc.line();
    constexpr auto sourceColumn = sourceLoc.column();
    fmt::print("File name {} func name {}\n line no {} column no {}\n",sourceFileName,sourceFunctionName,sourceLine,sourceColumn);

    Color myColor = Color::white;


    switch(myColor){
        using enum Color;
        // using Color::blue,Color::white; // Manually adding
        case black: break;
        case blue: break;
        case yellow: break;
    }

}