#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <string>
#include <optional>
#include <strings.h>
#include <type_traits>
#include <utility>
#include <variant>
#include <format>
#include <set>
#include <list>
#include <any>
#include <complex>

#include "fmt/core.h"

#include "utils.hpp"

template <typename T>
void func(T){}

void foo(int){}

class Functor{
public:
void operator()(int x){
    if ( x > mVal){
        ++mCount;
    }
}
int getCount() const{
    return mCount;
}

private:
int mVal{3};
int mCount{};
};

template<typename T>
class TypeTeller; // Incomplete Type

template<typename T>
void func2(T&&){
    TypeTeller<T> x;
}

template<typename T>
class MyClass{
public:
// If send "abdu" as r parametere mx would be char[4] due to reference if we dont 
// provide deduction guide
MyClass(const T& r):mx{r}{}
private:
T mx;
};

template <typename T>
MyClass(T)->MyClass<T>;

template<typename T>
class MyClass2{
public:
// If send "abdu" as r parametere mx would be char[4] due to reference if we dont 
// provide deduction guide
MyClass2(const T& r):mx{r}{}
private:
T mx;
};

// All integral types will create MyClass2<unsigned long long>
template<std::integral T>
MyClass2(T) -> MyClass2<unsigned long long>;

// const char* provided instantioans will create MyClass2<std::string>
MyClass2(const char*) -> MyClass2<std::string>;

template <typename T>
struct Sum{
    T value;
    template<typename... Types>
    Sum(Types... values): value{(values + ...)}{}
};

template<typename... Types>
Sum(Types...) -> Sum<std::common_type_t<Types...>>;

template<typename T>
struct Abdu{
    T str;
};


template<typename T>
struct Abdu2{
    T str;
};

explicit Abdu2(const char*)-> Abdu2<std::string>;

std::pair<int,double> fooRetPair(){
    return std::pair{3,5.0};
}

struct AbduStrBind{
    double dVal{};
    int a[5]{};
};

int(& funcReturnArray())[3]{
    static int arr[3] = {1,2,3};
    return arr;
}


auto funcReturnArray2() -> int(&)[3] {
    static int arr[3] = {1,2,3};
    return arr;
}

struct Point{
    int x,y,z;
};

auto main() -> int {
    using namespace std;
    // Ctad works below
    set set2{{1,3,5,7}, [](int a,int b){return b<a;}};
    std::vector<int> bigVec{100000};
    func(ref(bigVec)); // Sometimes we may want to pass as reference even though func takes it by value
    // To avoid copy , or ensure sended var is updated, not the copy .

    // for_each() returns callable.
    vector<int> vec(1000, 5);
    auto f = for_each(vec.begin(),vec.end(),Functor{});
    fmt::print("Count of Values more than 3 {}\n",f.getCount());

    vector v2{vec}; // copy
    vector v3{vec,vec}; // vector<vector<int>> with 2 elements 

    // has all elements from vec, thanks to deduction guide ( lesson 9 and below has more details) it does not contain iterators
    vector v4(vec.begin(),vec.end()); 

    vector v5{vec.begin(),vec.end()};// Initializer list constructor will work, will have two iterator inside

 // Complex (const T& var1 = T{},const T& var2 = T{})
    complex c1(3.7,5.3);
    complex c2(3.7);
    // complex c3();
    complex<double> c4(4.7);
    complex<double> c5; // Having c5() means function declaration

    function f1{foo}; // Works ctad

    // vector<pair> vecPair{{12,15},{13,14}};  // CTAD does not work
    vector<pair<int,int>> vecPair2{{12,15},{13,14}};  // CTAD does not work
    vector vecPair3{pair{12,15},pair{13,14}};  // CTAD does work here
    // tuple takes reference but "abdu" is still deducted as const char* instead of const char[4] thanks to deduction guide
    tuple tx{2,5.6,"abdu"}; // Type: tuple<int, double, const char *> (aka tuple<int, double, const char *>)

    // func2(23);
    // Trying to compile above line gives this message below ( it can be used to show declared type ie : int here)
    // implicit instantiation of undefined template 'TypeTeller<int>'

    int intArr[40]{};
    MyClass myClass(intArr);

    // Sum<CommonType<types...>>
    Sum s{1u,2.0,3l,5.f};
    fmt::print("{}\n",s.value);
    Sum s2{"abc","def"s};
    fmt::print("{}\n",s2.value);

    Abdu myAbdu = {23}; // Allowed with c++20, not allowed before
    // Needs deduction guide for c++17
    // Abdu(T) ->Abdu<T>;

    // Abdu2 a1 = {"hi"}; // Deduction guide is explicit, does not work
    Abdu2 a2 = Abdu2{"hi"};
    Abdu2 a3 = Abdu2{"hi"};
    Abdu2 a4 = {Abdu2{"hi"}};
    // ******** End of CTAD/Deduction guide , Start structured binding

    // array, tuple, classes/structs with all variables public can use structured binding 

    int ar[3]{1,2,3};
    auto [x,y] = fooRetPair(); // All 3 are valid.
    // auto [x,y] (fooRetPair());
    // auto [x,y] {fooRetPair()};

    AbduStrBind abduStrBind;
    auto [d,xVal] = abduStrBind; // xVal is int[5]
    // Deduction is made on the object that is right side of the assignment
    // Compiler sees it like AbduStrBind __abc = abduStrBind
    // Compiler sees it like AbduStrBind& __abc = abduStrBind when it is auto& [d,xVal]
    // d , Xval are just alias to __abc.dVal and __abc.a 
    // d, xVal are not necessarily reference, it can be macro or anything compiler uses instead

    auto [val1,val2,val3] = funcReturnArray();
    //if a function trying to use struct. decomp. with class which has private member variable
    // it can do it , only when class declares funtion private

    Point p1(1,7,9);
    auto [p1x,p1y,p1z] = p1; // Need to have equal length so leftside should have 3 identifier

    int iVar;
    double dVar;
    string strVar;
    tuple<int,double,string> tupleX{21,3.5,"Selami"};
    tie(iVar,dVar,strVar) = tupleX;

    // Best/most popular usage is function return type with pair tuple
    set<int> numSet{56,67,78,12};
    if(auto [iter,inserted] = numSet.insert(5);inserted){
        fmt::print("InsertionSuccessfull\n");
    }

}    