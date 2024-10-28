// #include <format>
// #include <iostream>
// #include <vector>
// #include <type_traits>
// #include <string>
// #include <memory>

// template<typename Rep,typename S>
// struct Duration{

// };


// // Swap uses moved from state, if your object is not valid in a valid state
// // after move, this can cause issues.
// template<typename T>
// void swap(T& x,T& y){
//   T temp(std::move(x));
//   x = std::move(y);
//   y = std::move(temp);
// }

// // universal reference + abbreviated function template
// void foo(auto&& x){}

// // universal reference
// template<typename T>
// void func(T&& arg){ 
//   // We can check if value sent here is const or not, lvalue or rvalue using T
//   // We can also check it using arg (so abbreviated function templates can use
//   // this technique)

//   // // if T is reference
//   // bar(arg);
//   // // if T is not a reference
//   // bar(std::move(arg));

//   // // Instead of above we have utility function: std::forward
//   // bar(std::forward<T>(arg));
//   // Perfect forwarding, passes l/r value and constness
// }


// // const &
// template<typename T>
// void func2(const T&){}

// template<typename T, typename U>
// void call_foo(T&& t, U&& u){
//   foo(std::forward<T>(t),std::forward<U>(u));
// }

// template<typename ...Args>
// void call_foo(Args&& ...args){
//   foo(std::forward<Args>(args)...);
// }

// template<typename T>
// constexpr T&& forward_basic(std::remove_reference_t<T>& t) noexcept{
//   return static_cast<T&&>(t);
// }

// template<typename T>
// constexpr T&& forward_actual_libgcc(std::remove_reference_t<T>& t) noexcept{
//   return static_cast<T&&>(t);
// }

// template<typename T>
// constexpr T&& forward_actual_libgcc(std::remove_reference_t<T>&& t) noexcept{
//   static_assert(!std::is_lvalue_reference_v<T>,"Can not forward rvalue as an lvalue.");
//   return static_cast<T&&>(t);
// }
// // This prevent forwarding rvalue as lvalue, example below, but when does this run ? 
// // There can be many cases to use forward other than perfect forwarding, so this is not
// // template<class T>
// // void wrapper(T&& arg)
// // {
// //     foo(forward<decltype(forward<T>(arg).get())>(forward<T>(arg).get()));
// // }


// template<typename T>
// void call_foo2(T&& arg){
//   foo(std::forward<decltype(arg)>(arg)); // useful for lambda, abbreviated template syntax etc 
// }

// struct Abdu{
//   int x;
// };

// template<typename T,typename ...Args>
// std::unique_ptr<T> MakeUnique(Args&& ...args){
//   return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
// }
// // Difference between func and func2 is , with func we know if value if lvalue or rvalue,
// // const or not etc, with func2 we lose all this information.
// // Both can bind to all difference cases of l/rvalue and const/non-const

// class MyClass{
// public:
//   MyClass(const MyClass&);
//   MyClass(MyClass&&) noexcept;

//   template<typename T>
//   MyClass(T&&); // This has more priority at some cases than copy/move constructor
//   // MyClass myclass = nonConstMyClassObj; // This will call universal constructor
//   // Undesired
// };
// // To fix the issue above we can constraint template type with enable_if or C++20 requires
// class MyClass2{
// public:
//   MyClass2(const MyClass2&);
//   MyClass2(MyClass&&) noexcept;

//   template<typename T>
//     requires(!std::is_same_v<std::remove_cvref<T>,MyClass2>)
//   MyClass2(T&&); // This has more priority at some cases than copy/move constructor
//   // MyClass myclass = nonConstMyClassObj; // This will call universal constructor
// };

// template<typename StringLike>
// void StringAcceptingFunc(StringLike&& str) { 
// // we may want to have function which accept string, but want to know if type is l/rvalue and 
// // know constness details, so we can still use universal referece, but will need to constrain
// // template type with enable_if or C++20 requires
// }
// auto main() -> int {
//   std::string s(100,'A');
//   auto& r1=s;
//   auto& r2=s;
//   std::cout << s << "\n";
//   s = std::move(s);
//   // std::swap(r1,r2);
//   std::cout << s << "\n";
//   std::cout <<"Test\n";

//   // Static assert protects from incorrectly calling the case below
//   // forward_actual_libgcc<Abdu&>(Abdu{});
//   // for R value , template type passed to forward, should be  Lvalue, just Abdu in this c ase
//   return 0;
// }