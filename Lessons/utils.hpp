#include <iostream>

namespace utils{

template<typename Container>
void print(Container& container){
  for(auto val:container){
    std::cout << val << " ";
  }
  std::cout << "\n";
}

} // namespace utils

