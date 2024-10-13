#include <cmath>
#include <cstring>
#include <format>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <numeric>
#include <string_view>
#include <chrono>

void func(std::string str){
  // No need to speccify std::reverse here
  // Argument is in std, so argument dependent lookup will find it
  reverse(str.begin(), str.end());
}

class MoveOnly{
public:
  MoveOnly() = default;

  MoveOnly(MoveOnly&&) noexcept(false) {std::cout << "MoveOnly(MoveOnly&&)\n";};
  MoveOnly& operator=(MoveOnly&&) noexcept(false) { 
    std::cout << "operator=(MoveOnly&&)\n";
    return *this;
    }; // This 2 line is normally enough
  // When move members are defined copies are deleted, but explicit is better
  MoveOnly(const MoveOnly&) = delete;
  MoveOnly& operator=(const MoveOnly&) = delete;

};

void iterate(int x, int y, int z){
  for(auto val:{x,y,z}){
    std::cout << val << " ";
  }
  std::cout << "\n";
}

template <typename T>
void funcTryingToTakeInitList(T){}

class Abdu{
  public:
  Abdu(std::initializer_list<int>){
    std::cout << "Abdu(std::initializer_list<int>)\n";
  } 
  Abdu(int){
    std::cout << "Abdu(int)\n";
  } 
};

template<typename Container>
void print(Container& container){
  for(auto val:container){
    std::cout << val << " ";
  }
  std::cout << "\n";
}

template <typename InIter, typename OutIter>
OutIter Copy(InIter first, InIter last, OutIter d_first){
  while(first!=last){
    *d_first++ = *first++;
  }
  return d_first;
}

template<typename BidIt1,typename BidIt2>
BidIt2 CopyBackward(BidIt1 first, BidIt1 last, BidIt2 d_last){
  while(last!=first){
    *(--d_last) = *(--last);
  }
  return d_last;
}

template <typename InIter, typename OutIter>
OutIter Move(InIter first, InIter last, OutIter d_first){
  while(first!=last){
    *d_first++ = std::move(*first++);
  }
  return d_first;
}

template<typename BidIt1,typename BidIt2>
BidIt2 MoveBackward(BidIt1 first, BidIt1 last, BidIt2 d_last){
  while(last!=first){
    *(--d_last) = std::move(*(--last));
  }
  return d_last;
}

template<typename Iter>
typename std::move_iterator<Iter> MakeMoveIterator(Iter iter){
  return std::move_iterator<Iter>(iter);
}

void doSomething(std::string name){
  std::cout << "doSomething" << name << "\n";
}

// Param must be unsigned long long or, const char* for uncooked version
int operator""_sr(unsigned long long val){
  std::cout << "operator""_sr" << val << "\n";
  return static_cast<int>(std::sqrt(val));
}

// Param must be unsigned long long or, const char* for uncooked version
int operator""_rawsr(const char* val){
  std::cout << "operator""_rawsr" << std::strlen(val) << "\n";
  while(*val){
    std::cout << *val;
    ++val;
  }
  std::cout << "\n";
  return 0;
}

constexpr int operator""_bin(const char* p){
  int retVal{0};
  while(*p){
    if(*p!='0' && *p!='1'){
      throw std::invalid_argument("Not a binary number");
    }
    retVal = retVal*2 + (*p - '0');
    ++p;
  }
  return retVal;
}

auto main() -> int {
  std::initializer_list<int> myList{1,2,3,4,5};
  // Initializer list has an array internally and values between {} are copied to the array
  // Due to copy containers storing move only types cant be initialized with initializer list
  constexpr auto sizeInitList = sizeof(myList);// 16 on 64 bit system
  // Init list only holds 2 pointer -> begin,end, interface provides begin,end,size

  iterate(5,7,8);
  auto x= {1,2,3,4}; // x is initializer list type this works.
  // funcTryingToTakeInitList({1,2,3,4,5}); // This will not work, as template deduction fails

  // std containers insert functions have std::initializer_list overloads to take multiple elements
  std::vector<int> vec;
  vec.insert(vec.begin(), {1,2,3,4,5});

  Abdu a{1};
  Abdu b =(1);
  Abdu c{1,2,3,4,5};
    Abdu d ={1};

  std::cout << std::vector<int>{1,5}.size() << "\n";
  std::cout << std::vector<int>(10,5).size() << "\n";

  // std::vector<MoveOnly> vecMoveOnly{MoveOnly{},MoveOnly{}}; 
  // Does not work copy functions are deleted, move only type cannot be copied

  std::vector<MoveOnly> vecMoveOnly{5};
  // for(auto val:vecMoveOnly){} // Does not work, copy functions are deleted
  MoveOnly moveOnly;
  vecMoveOnly.shrink_to_fit();
  std::cout << " vecMoveOnly.capacity()" << vecMoveOnly.capacity() << "\n";
  vecMoveOnly.push_back(MoveOnly{});
  std::cout << " vecMoveOnly.capacity()" << vecMoveOnly.capacity() << "\n";
  vecMoveOnly.push_back(std::move(moveOnly));
  std::cout << " vecMoveOnly.capacity()" << vecMoveOnly.capacity() << "\n";
  vecMoveOnly.reserve(1000);
  std::cout << " vecMoveOnly.capacity()" << vecMoveOnly.capacity() << "\n";

  // Above I tried to check what happens when move only type needs to be copied/moved when
  // vector is enlarged when move is not noexcept. Look like for move only types  even if move is not
  // no except it is still moved as no other option is available. Not part of the course.
  // https://en.cppreference.com/w/cpp/utility/move_if_noexcept

  /*
  remove
  remove_if
  unique
  Above functions actually do not remove elements from the container, they just move the elements
  */

  // Emplace_back helps us to skip move/copy, it constructs the object in place

  std::vector<int> ivec(10);
  std::iota(ivec.begin(), ivec.end(), 0); 
  // Fills ivec with    0,1,2,3,4,5,6,7,8,9
  // Lets saw we want:      0,1,2,3,4
  print(ivec);
  std::copy_backward(ivec.begin(),ivec.begin()+5,ivec.begin()+7);
  print(ivec);
  // normal copy ( forward one) could not be used here, it would overwrite copied data

  // std::move_iterator<std::vector<int>::iterator> moveIter(ivec.begin());
  std::move_iterator moveIter(ivec.begin());// Instead of above this works thank to 
  // Class template argument deduction (CTAD) C++17

  auto mIter = std::make_move_iterator(ivec.begin());

  // Move iterator needs to used carefully, multiple reference is a problem
  std::vector<std::string> svec{"a","b","c"};

  std::vector<std::string> svec2{std::move_iterator{svec.begin()},std::move_iterator{svec.end()}};
  print(svec);  // svec strings are now empty; 

  std::vector<std::string> svec3{"abc","bcd","cdf"};
  //Need to be careful with move iterators:
  std::for_each(std::make_move_iterator(svec3.begin()),std::make_move_iterator(svec3.end()),
  // [](std::string str){ // This will cause all string to be moved not what we want
  // [](std::string& str){ // This is error cant bind rvalue ref to lvalue ref 
  [](std::string&& str){ // This works as expected
    if(str.contains("d")){ // C++23 has contains ffinaly
      doSomething(std::move(str));
    }
  });

  // auto svVar="abdu"sv;
  using namespace std::chrono_literals;
  734ms;// kind of can be seen as operator called literal operator
  // Literal operator can only take basic types, no user defined types
  // user defined ones must start with _

  // if you want postfix under number
  // operator""_m(unsigned long long x){
  // 7823_m -> 7823 is passe sas integer to operator
  // This was is called "Cooked"

  // operator""_m(const char *p)
  // then operator""_m("7823") -> "7823" is passed as const char* to operator
  // This is called "Uncooked", for numbers we can select cooked or uncooked.
  // For numbers type of the operator must be unsigned long long or long double 

  auto sqrtOf16 = 16_sr;
  auto sqrtOf25 = operator""_sr(25);
  auto uncookedCall = 8567_rawsr;

  constexpr auto binVal = 10010101_bin;
  std::cout << "binVal : " << binVal << "\n";

  return 0;
}