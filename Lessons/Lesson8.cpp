// #include <bitset>
// #include <cmath>
// #include <cstring>
// #include <functional>
// #include <iostream>
// #include <string>
// #include <optional>
// #include <strings.h>
// #include <utility>
// #include <variant>
// #include <bitset>


// #include "utils.hpp"

// std::optional<std::string> getPersonNick(int id){
//     std::optional<std::string> nick;
//     if(id == 1){
//         nick = "Abdu";
//     }
//     return nick;
// }
// template<class Visitor,class... Variants>
// constexpr decltype(auto) visitDeclaration(Visitor&& vis,Variants&&... vars){}

// struct PrintVisitor{
    
//     void operator()(int x) const{
//         std::cout << "int" << x << "\n";
//     }
//     void operator()(double x) const{
//         std::cout << "double" << x << "\n";
//     }
//     void operator()(const std::string& x) const {
//         std::cout << "string" << x << "\n";
//     }
//     // Could make operator() template all are same anyway
//     // template<typename T>
//     // void operator()(const T& t){
//     //     std::cout << '[' << t << "]\n";
//     // }
//     // or void operator()(const auto& t)
//     // if we want different handling for different types we can use if constexpr
//     // if constexpr(std::is_same_v<T,int>) ...
// };

// struct IncrementVisitor{
//     void operator()(int& r){
//         ++r;
//     }
//     void operator()(double& d){
//         d *= d;
//     }
//     void operator()(std::string& d){
//         d += d;
//     }
// };

// struct PrintVisitor2{
//     void operator()(int& r){
//         std::cout << "int Alternatives\n";
//     }
//     void operator()(double& d){
//         std::cout << "double Alternatives\n";
//     }
//     void operator()(std::string& d){
//         std::cout << "string Alternatives\n";
//     }
//     void operator()(auto){
//         std::cout << "Other Alternatives\n";
//     }
// };

// auto main() -> int {
//     std::optional<std::string> op;
//     // std::optional<std::string> op{std::nullopt};
//     std:: cout << "HasValue: " << op.has_value() << "\n"; //false
//     std:: cout << "op == std::nullopt: " << (op == std::nullopt) << "\n"; //true
//     // op.value(); // throws exception
//     *op ;// does not throw exception, UB
//     op.value_or("Abdu");// Does not return reference, if empty returns "Abdu"
//     // std::optional<std::string&> op2; // Cant create optional of a reference;
//     std::string name0{"Abdu"};
//     std::optional<std::reference_wrapper<std::string>> op2{ref(name0)}; // Reference wrapper works, ADL
//     op2->get() += " Uysal";
//     std::cout << name0 << "\n";
//     std::optional x = 5; // CTAD is useful
//     std::optional opt2CTAD = ref(name0); // std::optional<std::reference_wrapper<std::string>>

//     // How to create optional<string> with default constructed string
//     std::optional<std::string> op3{std::string{}};// String will be constructed and moved to optional
//     // If string did not have move constructor, it would be copied, there is a better option
//     std::optional<std::string> op4{std::in_place}; // No copy, no move, string is constructed in place
//     //Arguments after std::inplace are perfect forwarded to std::string constructor
//     std::optional<std::string> op5{std::in_place,6,'A'};

//     auto op6{std::make_optional<std::string>(6,'A')}; // Same as above
//     auto op7{std::make_optional<std::string>()}; // Same as line42

//     std::cout << *op5 << "\n";

//     op7.reset(); // Optional is empty now , string is destroyed
//     op7 = std::nullopt; // Same as reset
//     op7 = std::optional<std::string>{}; // Same
//     op7 = {};

//     op7.emplace(6,'A'); // Resets , then creates string in place
//     // there is all type of operators to compare
//     op7 == op6;
//     op7 == "23";
//     x < 45;
//     std::optional<std::string> y;
//     std::cout << "Nullopt is smaller" << (y < op6) << "\n"; // Nullopt is always smaller
//     // Empty optional is equal to empty optional (nullopt)
    
//     // if(auto op = getPersonNick(5)){// Same as below
//     // if(auto op = getPersonNick(5);op){
//     if(auto op = getPersonNick(5);op->length()> 10){// UB on empty case, op is not checked if it is empty or not
//         std::cout<< "There is a nick with id =5 length > 10\n";
//         //do work
//     }

//     std::optional<std::string> opSrc{"Abdu"};
//     auto opDst = std::move(opSrc); // opSrc is on moved from state
//     std::cout << "opSrc.length() : " << opSrc->length() << "\n";
//     std::cout << "opSrc.has_value() " << opSrc.has_value() << " Value: <"<< *opSrc  << ">\n";
//      // True, it is moved but not destroyed, empty string
    
//     // optional has a bool flag + stored type , uses aligned storage
//     // so if stored type is 8 bytes, optional can be 16 bytes( depends on architecture)
//     std::cout << "Size of double : " << sizeof(double) << "\n";
//     std::cout << "Size of optional<double> : " << sizeof(std::optional<double>) << "\n";

//     // End of optional, time for std::variant ******************************

//     using std::cout, std::variant, std::endl, std::string, std::monostate;
//     variant<int,double,string> v;
//     variant<int,double,int> v2; // valid can have same type multiple times
//     variant<int,double,monostate> v3; // monostate if nullable variant. ie empty variant
//     // Variant is as large as largest type it can store, above case it is double
//     // Variant knows internal type unlike unions

//     variant<int,double> v4; // default initialized variants holds first type, int, needs default constructor
//     auto v4Val = std::get<0>(v4);
//     std::cout << v4Val << "\n";
//     variant<int,float,char> vx{'A'}; // holds char
//     // variant<int,float,char> vAmbiguity= 3.5; //

//     cout << vx.index() <<"\n"; // 2
//     vx = 3.5f;
//     cout << vx.index() <<"\n"; // 1

//     cout << "id vx holding int" <<  std::holds_alternative<int>(vx) << "\n"; // false
//     cout << "id vx holding float" <<  std::holds_alternative<float>(vx) << "\n"; // true

//     // in_place_index_t in_place_index
//     // in_place_type_t in_place_type
//     // variant<int,string,double> var{10,'A'};// Cant understand it is string constructor params
//     variant<int,string,double> var{std::in_place_index<1>, 10,'A'};
//     variant<int,string,double> var2{std::in_place_type<string>, 10,'A'};
//     variant<int,string,double> var3{std::in_place_type<string>}; // Default constructed string
//     variant<int,double,long> var5{34u}; // was expecting ambiguity here, but it is long
//     cout << std::holds_alternative<int>(var5) << "\n"; // false
//     cout << std::holds_alternative<double>(var5) << "\n"; // false
//     cout << std::holds_alternative<long>(var5) << "\n"; // true

//     variant<int,double,long,int> var6{std::in_place_index<3>,34}; // Stores the last int type
//     cout << "var6.index() : " << var6.index() << "\n"; // 3

//     // Variant holds stored data + index, so it is larger than largest type
//     // auto b = std::holds_alternative<std::string>(var6); // Compile time error
//     variant<int,double,long> var7{4.5};
//     try{
//         std::cout << std::get<0>(var7) << "\n"; // Throws bad_variant_access
//     }catch(const std::exception& ex){
//         std::cout << ex.what() << "\n"; // std::get: wrong index for variant
//     } // No throw
//     // std::cout << std::get<4>(var7) << "\n"; // Compile time error,

//     get<1>(var7) = 3.5f; // Works,get returns reference
//     get<double>(var7) = 3.2f; // Works,get returns reference
//     cout << get<double>(var7) << "\n"; // 3.2
    
//     double* value = get_if<double>(&var7);// Returns double* when type is double
//     // Normally we use visit, but without it we can have multiple if statements to do 
//     // different actions depeding on type using holds_alternative() or index().
//     variant<bool,string> var8("abdu"); // This holds bool in C++17, string in C++20+

//     enum idx: size_t{age,wage,name};
//     using Age = int;
//     using Wage = double;
//     using Name = string;
//     variant<Age,Wage,Name> var9{std::in_place_index<age>, 34};

//     cout << get<age>(var9) << "\n"; // 34
//     cout << get<Age>(var9) << "\n"; // 34
//     var9 = "abdu";
//     cout << get<name>(var9) << "\n"; // abdu
//     cout << get<Name>(var9) << "\n"; // abdu

//     var9.emplace<Name>(5,'A'); // Destroys old value
//     var9.emplace<Age>(5); // Destroys old value

//     variant<monostate,int,double,string> var10;
//     cout << var10.index() << "\n"; // 0
//     cout << "std::holds_alternative<monostate>(var10): "<< std::holds_alternative<monostate>(var10)<< "\n"; // 1
//     auto monostateVal =   get_if<monostate>(&var10);
//     cout << get_if<monostate>(&var10)<< "\n"; // 0

//     var10 = monostate{};
//     var10 = {}; // Same as above
//     var10.emplace<0>(); // Same as above
//     /////
//     variant<int,double,string> var11{"Abdu"};
//     PrintVisitor pr; // Functor class/struct
//     std::visit(pr,var11);
//     var11 = 5;
//     std::visit(PrintVisitor{},var11);
//     std::visit(IncrementVisitor{},var11);
//     std::visit(PrintVisitor{},var11);
//     var11 = 6.0;
//     std::visit(PrintVisitor{},var11);
//     std::visit(IncrementVisitor{},var11);
//     std::visit(PrintVisitor{},var11);
//     var11 = "Abdu";
//     std::visit(PrintVisitor{},var11);
//     std::visit(IncrementVisitor{},var11);
//     std::visit(PrintVisitor{},var11);

//     auto printVisitor = [](const auto& x){
//         std::cout << "[" << x << "]\n"; 
//     };
    
//     variant<int,char, long,double,string, std::bitset<16>> var13(std::in_place_index<4>, "Abc");
//     std::visit(PrintVisitor2{},var13);
//     var13 = std::bitset<16>{55};
//     std::visit(PrintVisitor2{},var13);
// }