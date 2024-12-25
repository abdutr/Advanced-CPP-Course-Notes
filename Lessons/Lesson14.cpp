// #include <algorithm>
// #include <bitset>
// #include <cmath>
// #include <cstring>
// #include <functional>
// #include <iostream>
// #include <iterator>
// #include <string>
// #include <optional>
// #include <strings.h>
// #include <tuple>
// #include <type_traits>
// #include <utility>
// #include <variant>
// #include <format>
// #include <set>
// #include <list>
// #include <any>
// #include <complex>
// #include <compare>

// #include "fmt/core.h"
// #include "fmt/format.h"

// #include "utils.hpp"

//  using namespace std;


//  std::ostream& Hex(std::ostream& os){
//     os.setf(ios::hex,ios::basefield);
//     return os;
//  }

// //  std::ostream& Seperated(std::ostream& os, int count=30){
// //     os << "\n" << string(count,'-') << "\n";
// //     return os;
// //  }

//  class Seperated{
// private:
//     int count;
// public:

//     Seperated(int count=30):count{count}{}

//     friend ostream& operator<<(ostream& inStream,const Seperated& sep){
//         return inStream << "\n" << string(sep.count,'-') << "\n";
//     }

//  };

//  class Person{
// private:

// string name;
// int id;

// public:
// Person(string name,int id):name{name},id{id}{}
// string getName()const { return name;}
// int getId()const { return id;}

//  };

//  // We support printing name, ID or both
//  template<>
//  class std::formatter<Person>{
// public:
//     // or short version parse(auto& ctx) 
//      constexpr auto parse(format_parse_context& ctx){
//         auto iter{ctx.begin()};
//         auto iterEnd{ctx.end()};

//         if(iter == iterEnd || *iter =='}'){
//             mFType = FormatType::All; // default print all
//             return iter;
//         }

//         switch(*iter){
//             case 'n': mFType = FormatType::Name; break;
//             case 'i': mFType = FormatType::Id; break;
//             case 'a': mFType = FormatType::All; break;
//             default: throw format_error("Person format error!");
//         }

//         ++iter;
//         if (iter != iterEnd && *iter != '}'){
//             throw format_error("Person format error!");
//         }
//         return iter;
//         // must return location of } 
//     }

//      constexpr auto format(const Person& person,std::format_context& ctx) const{
//         using enum FormatType;
//         switch(mFType){
//             case Name: return format_to(ctx.out(),"{}", person.getName());
//             case Id: return format_to(ctx.out(),"{}", person.getId());
//             case All: return format_to(ctx.out(),"{} {}", person.getName(), person.getId());
//         }
//         // Call format_to to print
//     }

//     private:
//     enum class FormatType{Name,Id,All};
//     FormatType mFType;
//  };

// auto main() -> int {
// /*
//     C had 
//     prinf(const char*pfm,...)
//     sprintf(char *buf,char *pfm,...)
//     fprintf(FILE8,const char* pfm,...)

//     Problems: Variadic functions are not type safe

//     sprintf is very fast compared to iostream
//     iostream is type safe, extendable for custom types with overloading
//     but can be quite verbose with global state( which is not optimal)
//     iostream streams has ios_base::fmtflags specifying formatting
// */
//     cout.setf(ios::boolalpha); // To set unset flags this can be used
//     cout.unsetf(ios::boolalpha);

//     cout.flags(cout.flags() | ios::boolalpha); // another approach to set flags
//     cout.flags(cout.flags() & (~ios::boolalpha)); // another approach to unset flags

//     // Also cout is shared global object so we need to revert after we use custom formatting to
//     // not affect other parts; or : 
//     ostream os(cout.rdbuf());
//     os.setf(ios::boolalpha); // Now this local object wont affect cout state
//     int iVal{2354};
//     double dVal{2345.678};

//     cout.setf(ios::hex,ios::basefield);
//     cout << iVal << " "; 
//     cout.setf(ios::uppercase);
//     cout.setf(ios::scientific,ios::floatfield);
//     cout << dVal<< "\n";
//     cout.unsetf(ios::scientific);
//     cout.unsetf(ios::floatfield);
//     cout.unsetf(ios::hex);
//     cout.setf(ios::dec);
//     // To go back to default
//     cout.clear(); 
//     // Above is absolutely terrible, there is another way to do this with iostream

//     /*
//     class ostream{
//         public:
//         ostream& operator<<(ostream& (*fp)(ostream&)){
//             return fp(*this); 
//         }
//     }

//     So ostream << has overload which takes function ptr , which takes and returns a ostream ref 
//     (to support chaining)
//     */

//     cout << 36752  << " " << Hex << 36752 << "\n"; 
//     // for manipualtor custom objects can be used when parameters are needed like below : 
//     cout << 36752  << " " << Seperated(25) << 36752 << "\n"; 

//     // Still iostream is slow and complex, hideous


//     // std/fmt format to rescue

//     auto str = format("Weather is terrible as this is default in Ireland"); // Returns string
//     auto name = "Abdu";
//     auto count = 6;
//     cout << format("Today {} bought {} books.\n",name,count);
//     // Has support for indexed usage: 
//     cout << format("{1} book were bought by {0}.{0} likes books\n",name,count);

//     for(int i{0};i<16;++i){
//         cout << format("{0:d} {0:#X} {0:c}    ",i);
//         if (i != 0 && i %8 ==0) cout <<"\n";
//     }
//     cout <<"\n";


//     // Format specifier is like this ; 
//     // [[fill]align] [sign][#][0][width][.precision][type]
//     // # enables show base mode when used together with type
//     // {3:_<}
//     // default fill is empty space, above we used _
//     //for alignemnt <(left) or >(right) or ^(middle) , default alignment is different for different types.
//     int x{4680};
//     cout << format("|{{{}}}|\n",x);
//     cout << format("|{:12}|\n",x);
//     cout << format("|{:<12}|\n",x);
//     cout << format("|{:^12}|\n",x);
//     cout << format("|{:_^+12}|\n",x);
//     int width =7; // Lets say runtime value
//     cout << format("|{:_^{}}|\n",x,width);

//     cout << format("|{:+}|\n",x); // 3 Sign options , puts + sign
//     cout << format("|{:-}|\n",x);
//     cout << format("|{: }|\n",x); // Places " " for for + case

//     cout << format("|{:+}|\n",-x); // 3 Sign options , puts + sign
//     cout << format("|{:-}|\n",-x);
//     cout << format("|{: }|\n",-x);

//     cout << format("|{:#012d}|\n",x);
//     cout << format("|{:#012X}|\n",x);



//     cout << format("|{}|\n",dVal);
//     cout << format("|{:g}|\n",dVal); // General 
//     cout << format("|{:e}|\n",dVal); // Scientific
//     cout << format("|{:f}|\n",dVal); // fixed
//     cout << format("|{:a}|\n",dVal); // hexfloat G/E/F/A version just capitalize X or e etc.


//     cout << format("|{}|\n",true); // For bool default is true/false
//     cout << format("|{:d}|\n",true);

//     //For pointers there is no default formatting
//     // cout << format("|{}|\n", &x) // Compile time error
//     cout << format("|{}|\n",(void*)&x); // For void* there is default formatting
//     // # not supported for ptr
//     // cout << format("|{0:#}|\n",(void*)&x);

//     cout << format("|{:p}|\n", nullptr);
//     int* ptr =nullptr;
//     // Below should work according to instructor but does not work in my env due to compile error
//     // According to not trustable gemini :
//     //      For libstdc++, there is no specialization of std::formatter for pointer types. 
//     //      However, libc++ does provide these specializations. 
//     //      By default, if you're using Clang, it's using the system's libstdc++ implementation.
//     //       If you switch to libc++, then it works perfectly.
//     // cout << format("|{:p}|\n",ptr);
//     // cout << format("|{:p}|\n",&x);

//     cout << format("|{}|\n",name);
//     cout << format("|{:24.3}|\n",name);// Default is left alignment
//     cout << format("|{:>24.3}|\n",name); // Precision can be used to print some part of the string

//     int num{345'123'435};
//     format_to(ostream_iterator<char>(cout),"|{:^#16X}|",num); // Writes to given address/iter
//     format_to(back_inserter(str),"|{:^#16X}|\n",num); // Writes to given address/iter
//     cout << format("{}",str);
//     cout.clear(); 
//     // There us locale support for format
//     cout.setf(ios::dec);
//     cout << 123.456 << "\n";
//     cout << 345 << "\n";
//     cout << "--------------\n";
//     cout << format("{:L}\n",4.56);
//     cout << format("{:L}\n",123345);

//     // locale::global(locale{""}); // Changed locale to somewhere, then :L will use it

//     cout << format("{:L}\n",4.56);

//     // Locale can be send to format as well
//     // cout << format(std::locale("turkish"),"|{}|",4.56); // Works but dont know current supported locales

//     int bigNum = 2134346346;
//     // Length of str if it was created with provided format
//     auto len = formatted_size("{:#X}",bigNum); 
    
//     cout << "len = " << len << "\n";

//     array<char,15> ar{};
//     auto res = format_to_n(ar.data(),ar.size()-1,"{} {}","abdu","uysal");

//     for(auto c:ar){
//         cout << c;
//     }
//     cout << "\n";

//     cout << "res.size = " << res.size <<"\n";
//     cout << "index = " << res.out-ar.data() <<"\n";


//     // To support format for custom type we need explicit specialization for std::formatter
//     Person a{"Abdu",1};
//     cout << format("{:n}\n",a);
//     cout << format("{:i}\n",a);
//     cout << format("{:a}\n",a);
// }
