#include <iostream>  // std::cout/endl

using namespace std;

//可变模板实现编译器递归


//单个参数
template <typename T>
constexpr auto sum(T x)
{
    return x;
}

//多个参数
//一个个参数减少，最终回到单个参数的函数调用
template <typename T1, typename T2, typename... Targ> //一些列类型的模板
constexpr auto sum(T1 x, T2 y, Targ... args)
{
    return sum(x + y, args...);
}

int main()
{
    short x = 12345;
    auto result = sum(1, 2, 3.5, x);
    //类型不必相同，只要能应用 + 号就行
    /*
    模板展开
    sum(1 + 2, 3.5, x)
    sum(3 + 3.5, x)
    sum(6.5 +  x)
    6.5 + x
    */
    cout << result << endl;
}
