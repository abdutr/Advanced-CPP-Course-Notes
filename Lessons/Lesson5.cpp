// #include "Lesson5_personal_side_project.hpp"
// #include <format>
// #include <iostream>
// #include <memory>
// #include <string>
// #include <type_traits>
// #include <vector>

// void navigate(std::string::iterator beg, std::string::iterator end) {
//   std::cout << "Nonconst\n";
// }
// void navigate(std::string::const_iterator beg,
//               std::string::const_iterator end) {
//   std::cout << "Const\n";
// }

// // Universal reference can be used without std::forward
// // Below example is taking advantage of universal reference holding constness
// // details
// template <typename T> 
// void processContainer(T &&coll) {
//   navigate(coll.begin(), coll.end());
// }

// template <typename T> 
// void func(T &, T &) {};

// template <typename T> 
// void insert1(std::vector<T> &vec, T &&element) {
//   vec.push_back(std::forward<T>(element));
// }

// template <typename T>
// void insert2(std::vector<std::remove_reference_t<T>> &vec, T &&element) {
//   vec.push_back(std::forward<T>(element));
// }

// class MyClass {};

// void foo(MyClass &) {}
// void foo(MyClass &&) {}
// // Assume const versions are also defined

// template <typename C, typename T> 
// void Fill(C &con, const T &val) {
//   for (auto &elem : con) { // This fails when C is vector<bool>
//     // for(auto&& elem:con){ // This fixes the issue with container with proxy
//     // classes
//     elem = val;
//     // auto& elem = pos.operator*(); // This is how compiler sees it,
//     // Error : assigning rvalue to lvalue as  reference proxy rvalue is returned
//   }
// }

// template <typename T>
// decltype(auto) perfectReturnFunc(T &&t) { // Allow us to return with exact return type of foo
//   return foo(std::forward<T>(t));
// }

// MyClass &&func() {
//   return MyClass{}; // Returning reference to temporary object, UB , it being
//                     // rvalue does not change anything
// }

// // How to return result later , ie some operations are needed after
// // perfectReturnFunc calls foo but want to return result of foo
// template <typename Func, typename... Args>
// decltype(auto) call(Func func, Args &&...args) {
//   decltype(auto) ret = func(std::forward<Args>(args)...);
//   // do some operation

//   if constexpr (std::is_rvalue_reference_v<decltype(ret)>) {
//     return std::move(ret);
//   } else {
//     return ret;
//   }
// }

// std::vector<std::string> create_svec() {
//   return {"Abdu", "Ali", "Alex"}; // Copilot suggested names :)
// }

// MyClass ReturnMyClass() { return MyClass{}; }

// auto main() -> int {
//   const std::string constStr = "const";
//   std::string nonConstStr = "nonconst";
//   processContainer(constStr);
//   processContainer(nonConstStr);
//   // func("Abdu","Ali"); ;// inputs are different type , const chart[4]/[5]
//   // error ambiguity
//   func("Abdu", "Alex"); // Both are const char[4], with reference types function
//                         // decay to pointer does not happen

//   std::vector<std::string> vec;
//   std::string s;
//   //  insert1(vec,s); // Invalid T is deducted as string(1st arg) and string&
//   //  (2nd arg)
//   insert2(vec, s); // Now both string& so it is ok.

//   auto &&r1 = MyClass(); // Why do we have auto&&
//   foo(MyClass{});       
//   auto &&var1 = MyClass{};
//   foo(std::forward<decltype(var1)>(var1)); // Work same as 2 line above

//   // This is useful for case below
//   // T x = function()
//   // foo(x)
//   // But we want this to work same as foo(function())
//   //  Done like this:
//   // auto&& x = function();
//   // foo(std::forward<decltype(x)>(x))

//   // Digress to vector<bool>

//   std::vector<bool> ivec(4, false);
//   auto x = ivec[2]; // Type of X : reference (aka std::_Bit_reference)
//   for (auto i : ivec) {
//     i = true; // This does the unexpected and values inside ivec really change
//   }

//   for (auto i : ivec) {
//     std::cout << i << " ";
//   }
//   std::cout << "\n";
//   ivec.operator[](3).operator=(true);
//   // ivec.operator[](3) returns reference (aka std::_Bit_reference) and we
//   // assign value to it
//   auto iter = ivec.begin();
//   *iter = true; // This will also assign value to reference type

//   for (auto x : ivec) {
//     // use x;
//   }

//   // this loop is written like this by compiler
//   /*
//     auto&& rng = ivec;
//     auto pos = rng.beging();
//     auto end = rng.end();
//     for(;pos!=end;++pos){
//       auto x = *pos; if defined likefor(auto x:ivec) or
//       auto& x =*pos; if defined likefor(auto& x:ivec)or
//       auto&& x = *pos; if defined likefor(auto&& x:ivec)
//     }
//   */

//   int num = 4;
//   decltype(auto) y = num;    // y is int
//   decltype(auto) y2 = (num); // y2 is int&
//   // decltype(auto) &y2 = (num); This does not work, decltype(auto) cant take &
//   // after it.

//   auto fn =
//       [](auto &&r1) -> decltype(auto) { // default return type of lambda is auto
//     return foo(std::forward<decltype(r1)>(
//         r1)); // To have same return type , we need trailing return type as
//               // decltype(auto)
//   };

//   for (std::string s : create_svec()) { // no problem
//     // ...
//   }

//   const auto &r3 = create_svec().at(0); // No lifetime extension
//   // vector ( ret val of create_svec) gets destroyed, boom, this is the reason
//   // why loops below are UB

//   // for(char c: create_svec()[0]){ // UB , if uncommented I get seg fault
//   // // for(char c: create_svec().at(0)){ // UB
//   // // for(char c: create_svec().front()){ // UB
//   //   // ...
//   // }

//   // With C++23 problem above with UB or for range loops is fixed
//   // Compiler generate it like this :
//   // auto&& temp1 = create_svec();
//   // auto&& temp2 = temp1[0]; // or temp1.at(0) or temp1.front()

//   MyClass{} = MyClass{};             // This is valid
//   ReturnMyClass() = ReturnMyClass(); // This is valid, no logical use.
//   // Why this is legal ? operator= is not defined like this
//   // operator=(const MyClass& other)& = default; // This would prevent
//   // assignment to rvalue & specifier.

//   testBenchmark();
//   return 0;
// }