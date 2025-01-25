#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstring>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <ostream>
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

template<typename Iter,typename Sentinel>
void algo(Iter beg,Sentinel end){}

struct NullSent{
    bool operator==(auto x)const{
        return *x == '\n';
    }
};

template< auto ENDVAL>
struct EndSent{

    bool operator==(auto pos)const{
        return *pos == ENDVAL;
    }
};

struct UnreachableSentinel_t{
    constexpr bool operator==(const auto& pos)const {
        return false;
    }
};
constexpr UnreachableSentinel_t UnreachableSentinel;

template <typename InIter,typename T,typename Projection = std::identity>
InIter Find(InIter beg,InIter end,const T& val, Projection pr={}){
    while(beg != end){
        if(std::invoke(pr,*beg) == val){
            return beg;
        }
        ++beg;
    }

    return end;
}

class MyClass{
public:
    int foo(int x){
        fmt::print("MyClass::foo(int x) x = {}\n",x);
        return x*1000;
    }


};

struct Abdu{
    int x{10};
    int y{20};
};

struct Point{
    Point() = default;
    Point(int x,int y): mx{x}, my{y}{}
    int mx{};
    int my{};
    friend std::ostream& operator<<(std::ostream& os,const Point& p){
        return os << "[" << p.mx << "," << p.my << "]";
    }

};

Point createRandomPoint(){
    mt19937 eng{random_device{}()};
    uniform_int_distribution dist(0,99);

    return Point(dist(eng),dist(eng));
}

template<input_iterator Iter,sentinel_for<Iter> Sent,
typename Init = iter_value_t<Iter>,typename Op = std::plus<>,typename Proj = identity>
Init Accumulate(Iter beg, Sent end, Init init = Init{},Op op= {},Proj proj = {}){

    while(beg!=end){
        init = invoke(op,move(init),invoke(proj,*beg));
        ++beg;
    }
    return init;
}

template<std::ranges::input_range R,typename Init = ranges::range_value_t<R>,typename Op = std::plus<>,typename Proj = identity>
Init Accumulate(R && r, Init init = Init{},Op op={},Proj proj={}){
    return Accumulate(ranges::begin(r),ranges::end(r),op,proj);
}

auto main() -> int {
    // ranges::sort is a contexpr object, so we are calling operator() on sort object
    // ranges::sort()
    // Why this is done like this ? To support ADL, avoiding issues with function object lookup
    fmt::print("{}\n",typeid(ranges::sort).name()); // clang has garbled name NSt6ranges9__sort_fnE

    // no range version of iota, accumulate , ones from numeric header( some are added with C++23)
    // Ranges have different parametric structure

    // begin and end does not need to be same type.
    // if begin and end are same time, then this is called common range( there is related concept as well)
    vector<int> ivec{3,56,8,3,2,1};
    counted_iterator iter{ivec.begin(),3}; // This iter can be incremented 3 times

    while(iter.count()){ // iter.count returns remaining: so  3
        fmt::print("{}\n",*iter++);
    }   

    // default_sentinel is provided by iterator header, checks count == 0
    for(counted_iterator it(ivec.begin(),5);iter!=default_sentinel; ++iter){
        fmt::print("{}\n",*iter);
    }

    char str[] = "abdu uysal\n";

    ranges::for_each(str,NullSent{},[](char c){ fmt::print("{}",c);});
    fmt::print("\n");

    auto iter2 = ranges::find(ivec.begin(),EndSent<8>{},8);
    fmt::print("{}\n",*iter2);

    // Sort until value 2
    ranges::sort(ivec.begin(),EndSent<2>{});
    utils::print(ivec);

    vector<int> ivec2(100);

    mt19937 eng{random_device{}()};
    uniform_int_distribution dist(0,100);
    ranges::generate(ivec2, [&]{return dist(eng);} );
    ranges::copy(ivec2,ostream_iterator<int>(cout, " "));

    vector<int> ivec3(100);
    ranges::iota(ivec3,0);
    ranges::shuffle(ivec3, eng);
    fmt::print("\nIvec3: \n");
    utils::print(ivec3);
    fmt::print("\n");

    auto searchedVal = 7;
    // this does not do any check about iter != sentinel or end, so we must be sure that value is in the container
    // here iota creates val from 0-100 so we are sure, no infinite loop
    auto searchedIter = ranges::find(ivec3.begin(),UnreachableSentinel,searchedVal);
    fmt::print("7 is found at index {}\n",searchedIter - ivec3.begin());
    // for_each (non ranges version) returns the calleable
    // Ranges for each is different, returns calleable fun and iterator as well

    vector vec{3,5,7,2,1};
    auto result = ranges::for_each(vec,[](int x){ fmt::print("{}",x);});
    result.fun; //in_fun_result<__normal_iterator<int *, vector<int>>, (lambda at /workspaces/Week1---Value-Category/Lessons/Lesson21.cpp:124:40)>
    fmt::print("{}\n",result.in - vec.begin());// iterator -> __gnu_cxx::__normal_iterator<int *, std::vector<int>>


    vector vec1{3,5,7,34,9,1};
    vector<int> vec2(100);
    auto copyResult = ranges::copy(vec1,vec2.begin());
    // copyResult.in; // iterator in vec1
    // copyResult.out; // iterator after lastly written item in vec2
    auto [iter_source,iter_dest] = ranges::copy(vec1,vec2.begin());

    auto resFindIter = Find(vec1.begin(),vec1.end(),9,[](int x){return x*x;});
    fmt::print("{}\n",*resFindIter);


    // Tangent, how to have function ptr to member function
    int (MyClass::*fp)(int) = &MyClass::foo; // Just use auto for clarity/safety
    MyClass myclassObj;
    (myclassObj.*fp)(5);

    MyClass *myclassObj2 = new MyClass;
    ((*myclassObj2).*fp)(7);

    // Invoke is much more easier and help alleviate many issues in generic programming
    invoke(fp,myclassObj,8);
    invoke(fp,myclassObj2,9); // We can pass address of object without referencing here , it works

    Abdu abduObj;
    int * p = &abduObj.x;
    int Abdu::*nptr = &Abdu::x; // These 2 are different, this is data member pointer

    (abduObj.*nptr) = 7; // Std::invoke can also be used for this

    invoke(nptr,abduObj) = 25;

    // ivec3 values 1-100 shuffled, lets sort them according abs value of x-50
    ranges::sort(ivec3,{},[](int x){
        return abs(x-50);
    });
    utils::print(ivec3);

    vector<Point> pVec(100);
    ranges::generate(pVec,createRandomPoint);
    ranges::copy(pVec,ostream_iterator<Point>(cout,"\n"));

    ranges::sort(pVec,{},&Point::mx); // sort according to mx values
    ranges::sort(pVec,{},&Point::my); // sort according to my values


    vector<string> sVec{"abdu uysal","mehmet duran","cevik enes"};

    if( auto iter = ranges::find(sVec,10, [](const std::string& s){return s.size();});
    iter!=sVec.end()){
        fmt::print("{}\n",*iter);
    }

    auto lengthCalculator = [](unsigned val,const std::string& s){
        return val + s.length();
    };
    auto resAccum = accumulate(sVec.begin(),sVec.end(),0u,lengthCalculator);
    fmt::print("Result of accum ( length of names) : {}\n",resAccum);

    // Views : lightweight ranges
    // Instead of std::ranges:views we write std::views
    // std::views::take()
    // std::views::filter()
    // std::views::drop()
     // ivec3 values 1-100 shuffled,
    for(auto x: views::take(ivec3,10)){
        fmt::print("{} ",x);
    }
    fmt::print("\n ");
    for(auto x: views::filter(ivec3,[](int x){return x>=50;})){
        fmt::print("{} ",x);
    }
    fmt::print("\n ");

    auto viewOfiVec3 = views::take(ivec3,10);
    ranges::take_view view2Ofivec3(ivec3,10);

    ranges::for_each(views::take(ivec3,10),[](int x){ cout << x << " ";});

    auto optionA =   ivec | views::take(12);// Same
    auto optionB = views::take(ivec,12);// Same
    // all views are range, but not all ranges are view
    // range should support view concept to be a view
    fmt::print("\n ");
    for(auto val: views::reverse(ivec3)){
        fmt::print("{} ",val);
    }
    fmt::print("\n ");

    fmt::print("\n ");
    for(auto val: views::reverse(views::take(ivec3,5))){
        fmt::print("{} ",val);
    }
    fmt::print("\n ");

    fmt::print("\n ");
    for(auto val: views::filter(views::reverse(views::take(ivec3,10)),[](int x){return x%2 ==0;})){
        fmt::print("{} ",val);
    }
    fmt::print("\n ");

    // We can just use pipelining

    fmt::print("\n ");
    for(auto val: ivec3 | views::take(10) | views::reverse | views::filter([](int x){return x%2==0;})){
        fmt::print("{} ",val);
    }
    fmt::print("\n ");

}
