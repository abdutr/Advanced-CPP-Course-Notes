// #include <algorithm>
// #include <any>
// #include <bit> // C++ 20
// #include <bitset>
// #include <chrono>
// #include <cmath>
// #include <compare>
// #include <complex>
// #include <concepts>
// #include <cstddef>
// #include <cstring>
// #include <deque>
// #include <format>
// #include <forward_list>
// #include <functional>
// #include <iostream>
// #include <iterator>
// #include <list>
// #include <memory>
// #include <numeric>
// #include <optional>
// #include <ostream>
// #include <random>
// #include <ranges>
// #include <set>
// #include <source_location>
// #include <stdexcept>
// #include <string>
// #include <strings.h>
// #include <tuple>
// #include <type_traits>
// #include <utility>
// #include <variant>

// #include "fmt/core.h"
// #include "fmt/format.h"

// #include "utils.hpp"

// using namespace std;

// auto main() -> int {
//   vector vec{2, 3, 4, 5};

//   auto vw1 = vec | views::filter([](int x) { return x % 2 == 0; });

//   utils::print(vw1);

//   // lots of functions from original std also exist in std::ranges :
//   // empty, size, ssize,c/r/begin,c/r/end,data,cdata
//   // distance next,prev advance

//   vector<string> sVec{"veli", "abud", "abdu", "alex", "dusan", "kemal"};

//   ranges::copy(sVec, ostream_iterator<string>{cout, " "});

//   cout << "\n";
//   vector<string> destVec(100);

//   auto iterAfterLastWritten =
//       transform(sVec.begin(), sVec.end(), destVec.begin(),
//                 [](const string &s) { return s.size(); });

//     fmt::print("Distance {}\n", distance(destVec.begin(),iterAfterLastWritten));

//     vector iVec{3,6,23,234,34,1};
//     auto minMax = ranges::minmax_element(iVec);
//     auto res = ranges::find(iVec,6);

//     auto iVecView = views::take(iVec,4); // This function is a range adaptor, functions which convert to view/range
//     // Specific type returned is dependant on input types, so it is more advantageous to use than direct
//     // usage of ranges::take_view<>
    
//     for(int i : views::take(iVec,4)){
//         fmt::print("i: {}\n",i);
//     }
//     // Views are lazy evaluated

//     auto filter = std::views::filter(iVec,[](int x){
//         cout <<"abdu\n";
//         return x%3 == 0;
//     }); // No function is called here

//     auto iter = filter.begin() ; // Function is called here, is this is commented out abdu wont be printed

//     // Range adaptor are composable , so 

//     // lets say we want to create a vec from iVec which includes square of even elements

//     vector<int> temp;
//     vector<int> dest;

//     copy_if(iVec.begin(),iVec.end(),back_inserter(temp),[](int x){ return x %2 ==0;});

//     transform(temp.begin(),temp.end(),back_inserter(dest),[](int x){return x*x;});

//     utils::print(dest);

//     // With C++ 20 same could be done like this:

//     namespace rng = std::ranges;
//     namespace vw = std::views;

//     auto result = vw::transform(vw::filter(iVec,[](int x){return x%2 ==0;}) ,[](int x){return x*x;});
//     auto result2 = iVec | vw::filter([](int x){return x%2==0;}) |  vw::transform([](int x){return x*x;});
//     utils::print(result);
//     utils::print(result2);

//     // w22 : min : 1.31.50
// }
