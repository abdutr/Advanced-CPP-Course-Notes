// #include <format>
// #include <iostream>
// #include <vector>
// #include <type_traits>
// // Causes link error if cant RVOzed , so can use this pattern for the class if
// // possible
// class force_rvo {
// public:
//   force_rvo(int) { std::cout << "force_rvo(int)\n"; }

//   force_rvo(const force_rvo &); // not implemented
//   force_rvo(force_rvo &&);      // not implemented
// };

// class Myclass {
// public:
//   Myclass(int) {}
//   Myclass() = default;
// };

// const Myclass foo(int x) {
//   // Const return type prevent copy elision/ move optimization
//   // Reason is no one implements Myclass(const Myclass&& in) so fallback happens
//   // to copy constructor
//   Myclass m{x};

//   return x;
// }

// Myclass foo2() {
//   Myclass x;

//   // Some code

//   return std::move(x); // This blocks copy elision and forces move , harmful
//   // Depending on compiler this can be optimized , if cant it is moved anyway
//   // so forcing move is harmful
// }

// // void func()throw(); // Old style does not throw exception
// // void func2()throw(std::bad_alloc); // Old style can throw bad_alloc

// void func() noexcept(false);
// // void func(); // Same with above line

// template <typename T>
// void func2(T) noexcept(std::is_nothrow_copy_constructible_v<T>);

// void func3(int) noexcept{};

// template <typename T>
// void func4(T x) noexcept(
//     noexcept(x + x)); // noexcept args are non evaluated context

// void func5(int) noexcept(false);

// class TestClass {
// public:
//   TestClass() noexcept =
//       default; // With C++ 20 we can provide noexcept even with default
// };

// class Student {
// public:
//   Student(const char *name) : name_{name} {}
//   std::string getName() const { return name_; }
//   Student(const Student &other) : name_{other.name_}{ 
//     std::cout << "COPY " << name_ << "\n";
//   }
//   Student(Student &&other) :name_{std::move(other.name_)} {
//     // Student(Student &&other) noexcept:name_{std::move(other.name_)} {
//     std::cout << "MOVE " << name_ << "\n";
//   }

// private:
//   std::string name_;
// };

// auto main() -> int {
//   std::cout << std::format("Nice {}\n", 1);
//   foo(5);

//   void (*funcPtr)(int) = func3; // funcptr does not carry noexcept specifier
//   constexpr auto b = noexcept(funcPtr(12)); // Value is false

//   void (*funcPtr2)(int) noexcept = func3;    // but we can manually add.
//   constexpr auto b2 = noexcept(funcPtr2(5)); // Value true

//   // void (*funcPtr3)(int)noexcept = func5; // cant do this assignment noexcept
//   // specifier does not match

//   auto f = func3;
//   constexpr bool isNoExcept =
//       noexcept(f); // True, type deduction gets correct noexcept spec.

//   std::vector<Student> vec{"Abdu", "Morria","Alexandru"};
//   std::cout << "capacity: " << vec.capacity() << '\n';
//   vec.push_back("Aysenur Nazligul Aybakan");

//   // Above first 3 elements are copied instead of moved reason
//   // is move constructor is not noexcept . Why ? Because push_back
//   // is gives strong guarantee, if moves fails we cant rollback to
//   // prior state, so copy is used if copy fails no issue .

//   // Uncomment code with noexcept move constructor to see elemets being moved.

//   return 0;
// }