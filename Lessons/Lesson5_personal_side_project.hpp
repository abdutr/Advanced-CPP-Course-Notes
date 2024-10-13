// #pragma once
// #include <cassert>
// #include <chrono>
// #include <cstdint>
// #include <functional>
// #include <iostream>
// #include <type_traits>

// template <typename Rep = double, typename Period = std::ratio<1>,
//           typename Callable, typename... Args>
// decltype(auto) benchmark(Callable &&callable, Args &&...args) {
//   const auto start = std::chrono::high_resolution_clock::now();
//   using CallableReturnType = std::invoke_result_t<Callable, Args...>;
//   if constexpr (std::is_same_v<CallableReturnType, void>) {
//     std::invoke(std::forward<Callable>(callable), std::forward<Args>(args)...);
//     const auto finish = std::chrono::high_resolution_clock::now();
//     return std::chrono::duration<Rep, Period>(finish - start);
//   } else {
//     decltype(auto) result{std::invoke(std::forward<Callable>(callable),
//                                       std::forward<Args>(args)...)};
//     const auto finish = std::chrono::high_resolution_clock::now();
//     const auto function_runtime{
//         std::chrono::duration<Rep, Period>(finish - start)};
//     return (std::pair<std::invoke_result_t<Callable, Args...>,
//                      std::chrono::duration<Rep, Period>>(
//         std::forward<decltype(result)>(result), function_runtime));
//   }
// }

// inline auto funcToBenchmark(int x) { // Idiotic function to pass time
//   int64_t val{0};
//   for (int64_t i{0}; i < x; i++) {
//     val += i;
//   }
//   return val;
// }

// inline int globalVarToTriggerSideEffects = 0;

// class BenchmarkTestClass {
// public:
//   BenchmarkTestClass(int x) : x{x} {}
//   int x;
//   inline static int AccessCounter = 0;
//   int &getX() {
//     ++AccessCounter;
//     ++globalVarToTriggerSideEffects;
//     return x;
//   }
//   BenchmarkTestClass(BenchmarkTestClass &&other) {
//     std::cout << "Move constructor called\n";
//     x = other.x;
//     other.x = 0;
//   }
//   BenchmarkTestClass(const BenchmarkTestClass &other) {
//     std::cout << "Copy constructor called\n";
//     x = other.x;
//   }
//   BenchmarkTestClass &operator=(const BenchmarkTestClass &other) {
//     std::cout << "Copy assignment called\n";
//     x = other.x;
//     return *this;
//   }
//   BenchmarkTestClass &operator=(BenchmarkTestClass &&other) {
//     std::cout << "Move assignment called\n";
//     x = other.x;
//     other.x = 0;
//     return *this;
//   }
// };

// inline BenchmarkTestClass &&func1(BenchmarkTestClass &&x) {
//   funcToBenchmark(1000000);
//   x.getX() = 3;
//   return std::move(x);
// }

// inline BenchmarkTestClass func2(BenchmarkTestClass x) {
//   funcToBenchmark(1000000);
//   return x;
// }

// void test_function_1() { std::cout << "Time me : " << std::endl; }

// int &test_function_2(int x) {
//   static int counter = 0;
//   counter += x;
//   return counter;
// }

// class RefTest {
// public:
//   int a;
//   int &GetA() { return a; }
// };

// inline void testBenchmark() {
//   BenchmarkTestClass a = 5;
//   a.getX() = 4;
//   auto [resultbenchmark, time] = benchmark(func1, std::move(a));
//   // resultbenchmark std::tuple_element<0, std::pair<BenchmarkTestClass &&, std::chrono::duration<double>>>::type (aka BenchmarkTestClass &&)
//   // time std::tuple_element<1, std::pair<BenchmarkTestClass &&, std::chrono::duration<double>>>::type (aka std::chrono::duration<double>)
//   auto result_pair = benchmark(func1, std::move(a)); // Type of resultPair : pair<BenchmarkTestClass &&, duration<double, std::ratio<1, 1>>>
//   decltype(auto) result_pair2 = benchmark(func1, std::move(a)); //           pair<BenchmarkTestClass &&, duration<double, std::ratio<1, 1>>>
//   int&& intVar = 5;
//   static_assert(std::is_rvalue_reference_v<decltype(resultbenchmark)>);
//   static_assert(std::is_rvalue_reference_v<decltype(result_pair.first)>);
//   std::cout << resultbenchmark.x << "Time : " << time << "\n";
//   assert(resultbenchmark.x == 3);

//   // Above case needs more investigation and improvement

//   // Below are simple cases, using auto instead of decltype(auto) works due to
//   // structured binding,std::get and std::pair implementation

//   // This works for references even though you would think this would create a
//   // copy Reason is std::get is internally used at structural binding resolution
//   // for pairs and tuple and it has return type&&  .
//   //
//   // Normal return by values is also valid and works as expected
//   std::cout << "Test function 1 Runtime: " << benchmark(test_function_1).count()
//             << std::endl;
//   auto timed_result{benchmark(test_function_2, 5)};
//   decltype(auto) function2_result = timed_result.first;
//   std::cout << "Test function 2 Runtime: " << timed_result.second.count()
//             << std::endl;
//   std::cout << "Return value of funtion 2 " << function2_result << std::endl;
//   function2_result = 7;
//   auto [function2_result2, function2_time2]{benchmark(test_function_2, 5)};
//   std::cout << "Static variable result from reference " << function2_result
//             << " Result of new call " << function2_result2
//             << " should be equal and be 12" << std::endl;

//   RefTest ref_test(10);
//   auto [a_ref, member_var_access_time]{benchmark(&RefTest::GetA, &ref_test)};
//   std::cout << "Member variable access time: " << member_var_access_time.count()
//             << std::endl;
//   a_ref = 12;
//   std::cout << "a_ref value: " << a_ref << " a inside ref_test: " << ref_test.a
//             << std::endl;
//   ref_test.a = 9;
//   std::cout << "a_ref value: " << a_ref << " a inside ref_test: " << ref_test.a
//             << std::endl;

//   auto [a_ref2, member_var_access_time_ns]{
//       benchmark<int64_t, std::nano>(&RefTest::GetA, &ref_test)};
//   auto [a_ref3, member_var_access_time_micros]{
//       benchmark<double, std::micro>(&RefTest::GetA, &ref_test)};
//   auto [a_ref4, member_var_access_time_ms]{
//       benchmark<double, std::milli>(&RefTest::GetA, &ref_test)};
//   auto [a_ref5,
//         member_var_access_time_s]{benchmark<double>(&RefTest::GetA, &ref_test)};
//   auto [a_ref6, member_var_access_time_decas]{
//       benchmark<double, std::deca>(&RefTest::GetA, &ref_test)};
//   std::cout << "Member variable access time in ns: "
//             << member_var_access_time_ns.count() << std::endl;
//   std::cout << "Member variable access time in microsecond: "
//             << member_var_access_time_micros.count() << std::endl;
//   std::cout << "Member variable access time in millisecond: "
//             << member_var_access_time_ms.count() << std::endl;
//   std::cout << "Member variable access time in second: "
//             << member_var_access_time_s.count() << std::endl;
//   std::cout << "Member variable access time in decasecond: "
//             << member_var_access_time_decas.count() << std::endl;
// }
