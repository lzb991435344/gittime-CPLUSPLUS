#include <algorithm>  // std::sort
#include <iostream>   // std::cout/endl
#include <string>     // std::string
#include <tuple>      // std::tuple/get
#include <vector>     // std::vector

using namespace std;

//多个固定数量，固定类型的组合
using num_tuple = tuple<int, string, string>;

ostream& operator<<(ostream& os, const num_tuple& value)
{
    os << get<0>(value) << ',' << get<1>(value) << ',' << get<2>(value);
    return os;
}

int main()
{
    vector<num_tuple> vn{{1, "one", "un"},
                         {2, "two", "deux"},
                         {3, "three", "trois"},
                         {4, "four", "quatre"}};
    get<2>(vn[0]) = "une";

    //使用高阶函数
    sort(vn.begin(), vn.end(),
         [](auto&& x, auto&& y) { return get<2>(x) < get<2>(y); });
    for (auto&& value : vn) {
        cout << value << endl;
    }
    //取得项数 tuple_size_v
    constexpr auto size = tuple_size_v<num_tuple>;
    cout << "Tuple size is " << size << endl;
}
