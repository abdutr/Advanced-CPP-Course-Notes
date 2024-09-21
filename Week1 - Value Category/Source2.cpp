#include <iostream>
#include <type_traits>

template <typename T>
struct RemoveReference {
	using type = T;
};

template <typename T>
struct RemoveReference<T&> {
	using type = T;
};

template <typename T>
struct RemoveReference<T&&> {
	using type = T;
};

template <typename T>
using RemoveReference_t = RemoveReference<T>::type;

template<typename T>
std::remove_reference_t<T>&& Move(T&& t) noexcept {
	return static_cast<std::remove_reference_t<T>&&>(t); 
}

template <typename T>
void func(T x)noexcept(noexcept(x + x)) { 
	// first noexcept is noexcept specifier
	// second one is noexcept operator
}

template <typename T>
void func2(T x)noexcept(noexcept(x + x) && noexcept(x - x) && noexcept(x.func())) {

}

class MyClass {
private:
	// Inclass initializer or default member initializer, if not initialized in constructor 
	// this values are used, if = default is used, values are also initialized via default 
	// member initializer
	int mx{};
	std::string mname{ "NoName yet" };
};

class MyClass2 {
public:
	void print()const {
		std::cout << mx << " " << mname << "\n";
	}
private:
	int mx;
	std::string mname;
};

class MyClass3 {
public:
	MyClass3() {  };
	MyClass3(int) { std::cout << "MyClass(int)\n"; };
	MyClass3(const MyClass3&) = delete;
};

void func(MyClass3) {};

MyClass3 func2(int x) {
	return MyClass3{ x };
}

auto main() -> int { 
	RemoveReference<int&&>::type x{}; // This was unvalid before after c++20 it is ok
	typename RemoveReference<int&&>::type x2{}; // typename was needed before c++20
	constexpr auto b = noexcept(std::cout << 1); // Will not be printed, unevaluated context

	MyClass2 obj;
	obj.print(); // Printed value of mx unknown UD, mname empty string

	MyClass2 obj2 {}; // This is value initialization, first step is zero initialization
	// Static objects are also zero initialized
	obj2.print(); // Printed value of mx is 0, mname empty string 

	func(MyClass3{}); // With C++17 this will not do any copy, as PRValue will only be materialized
	// when it is initialized the variable inside func. Before C++17 this would require copy and
	// existence of Copy Constructor
	func(MyClass3{ 5 }); // Same with above nothing changes
	
	func2(5); // No copy here as well
	//auto m = MyClass3{ MyClass3{func2(7)} }; // this must not trigger copy as well
	// but MSVC sucks again I guess it calls it for me.

	// With C++17 (unnamed) Return Value Optimization is no longer compiler optimization
	// It happens as a result of passing unmaterialized object and only 

	//Named  Return  Value optimization is still compiler optimiation.
}
