#include <iostream>
#include <type_traits>

int&& foointrefref();
int fooint();
int& barintref();
struct Abdu {
	int x{}; 
};

struct AbduStatic {
	static int x;
};

template <typename T>
constexpr const char* p = "PRValue";

template <typename T>
constexpr const char* p<T&> = "LValue";

template <typename T>
constexpr const char* p<T&&> = "XValue";

// Instead of above we can also use this
//template <typename T>
//void func() {
//	if constexpr (std::is_rvalue_reference_v<T>()) {
//		std::cout << "X Value";
//	}
//	else if constexpr (std::is_lvalue_reference_v<T>()) {
//		std::cout << "L value";
//	}
//	else if constexpr (!std::is_reference_v<T>()) {
//		std::cout << "PR Value";
//	}
//}

#define printValueCategory(e)  std::cout << "Value Category of '" << #e << "' is " << p<decltype((e))> << '\n';

auto main() -> int {
	/*
	Decltype(name) is different than expression version
	To trigger expression version on name we use decltype((x)) below


	Decltype(expression) If value is :
	PRValue -> T
	Lvalue -> T&
	XValue -> T&&
	*/
	int x{ 5 };
	int* p2{ &x };
	decltype(10);// int PRValue
	decltype(x + 5);// int PRValue
	decltype(*p2); // int& Lvalue
	decltype((x)); //int& Lvalue
	decltype(foointrefref()); //int&& XValue
	decltype(Abdu{}.x); // int&& Abdu{}.x is XValue, my vscode compiler suck says wrong thing use clang or gcc

	std::cout << p<decltype(10)> << "\n";
	std::cout << p<decltype(x+5)> << "\n";
	std::cout << p<decltype(*p2)> << "\n";
	std::cout << p<decltype((x))> << "\n";
	std::cout << p<decltype(foointrefref())> << "\n";
	std::cout << p<decltype((Abdu{}.x))> << "\n";
	printValueCategory(10);
	printValueCategory(x+5);
	printValueCategory(*p2);
	printValueCategory((x));
	printValueCategory(foointrefref());
	printValueCategory(Abdu{}.x);
	printValueCategory(x++);
	printValueCategory(x--);
	printValueCategory(++x);
	printValueCategory(--x);
	printValueCategory(foointrefref());
	printValueCategory(fooint());
	printValueCategory(barintref());
	printValueCategory('a');
	printValueCategory("Abc");
	printValueCategory(foointrefref); // Functions themself are lvalue
	printValueCategory(fooint);
	printValueCategory(barintref);
	printValueCategory(std::move(x));
	printValueCategory(std::move(foointrefref)); // This is still LValue there is a bug in MSVC compiler if you see X value it is incorrect
	printValueCategory(nullptr);
	printValueCategory(Abdu{});
	printValueCategory([] {return 1; }); // Same with line above this is just temporary object of class xxxyyyzz
	auto abdu{ Abdu() };
	printValueCategory(abdu);
	auto& abduRef{ abdu };
	printValueCategory(abduRef);
	auto&& abduRefRef{ Abdu{} }; //Forwarding/Universal reference, though in this context does not matter
	printValueCategory(abduRefRef);
	printValueCategory(abdu.x);
	printValueCategory(Abdu{}.x);
	printValueCategory(std::move(abdu).x);
	auto staticAbdu{ AbduStatic{} };
	printValueCategory(std::move(staticAbdu).x);
	int a, b, c;
	printValueCategory(a > 10 ? b : c);
	printValueCategory(a > 10 ? b : 10);
	printValueCategory(a > 10 ? 10 : b);

	Abdu abd;
	const Abdu cabd;

	Abdu& r = abd;
	//Abdu& r2 = cabd;
	//Abdu& r2 = Abdu{};

	const Abdu& r2 = abd;
	const Abdu& r3 = cabd;
	const Abdu& r4 = Abdu{};
	const Abdu& r5 = std::move(cabd);

	//Abdu&& r6 = abd;
	//Abdu&& r6 = cabd;
	Abdu&& r6 = Abdu{};
	//Abdu&& r7 = std::move(cabd);
	Abdu&& r7 = std::move(abd);
	const Abdu&& r8 = std::move(cabd);
	const Abdu&& r9 = std::move(abd);

	Abdu m;
	Abdu&& rr = std::move(m);

	//Abdu m2 = rr; // This is not a move, this call copy constructor
	Abdu m2 = std::move(rr); // This is not a move, this call copy constructor

	// instead of std::move we could use static_cast<T&&>(exp), no difference
}

// Possible std::move implementation
//template <typename T>
//constexpr Move(T&&) noexcept {
//
//}