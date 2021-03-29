#include <iostream>           // std::cout/endl
#include <numeric>            // std::accumulate
#include <utility>            // std::forward
#include <vector>             // std::vector
#include <nvwa/functional.h>  // nvwa::fmap

using namespace std;
using nvwa::fmap;

//递归终结，单个的compose
template <typename F>
auto compose(F f)
{
    //泛型的lamba表达式，保证参数可以转发到f
    return [f](auto&&... x) { return f(forward<decltype(x)>(x)...); };
}

template <typename F,
          typename... Args>
auto compose(F f, Args... other)
{
    //返回到f中
    return [f, other...](auto&&... x) {
        //使用f捕捉第一个函数对象，使用args捕捉后面的对象
        return f(compose(other...)(forward<decltype(x)>(x)...));
    };
}

int main()
{
    //平方的函数对象
    auto square_list = [](auto&& container) {
        return fmap([](int x) { return x * x; }, container);
    };

    //求和函数对象
    auto sum_list = [](auto&& container) {
        return accumulate(container.begin(), container.end(), 0);
    };
    auto squared_sum = compose(sum_list, square_list);
    vector v{1, 2, 3, 4, 5};
    cout << squared_sum(v) << endl; //55
}
