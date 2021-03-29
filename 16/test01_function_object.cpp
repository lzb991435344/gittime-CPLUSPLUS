#include <functional>           // std::bind/bind2nd/function/plus
#include <iostream>             // std::cout/endl
#include <map>                  // std::map
#include <string>               // std::string
#include <vector>               // std::vector
#include <nvwa/c++_features.h>  // NVWA_USES_CXX17

using namespace std;

//使用struct
struct adder {
    adder(int n) : n_(n) {}

    //定义了()的运算方式
    int operator()(int x) const
    {
        return x + n_;
    }

private:
    int n_;
};

int main()
{
    using namespace std::placeholders;

    {
        //定义实际的函数对象 add_2可当做函数来进行使用
        adder add_2(2);
        cout << "Manual function object: " << add_2(5) << endl; //7
    }

#if !NVWA_USES_CXX17
    {   
        //传递一个函数对象过去，得到一个新的函数对象
        //function1   bind1st
        //function2   bind2nd

        //把参数2当做第二个参数绑定到函数对象plus<int> 上，它的operator()需要两个参数
        cout << "bind2nd: " << bind2nd(plus<int>(), 2)(5) << endl;
    }
#endif

#if NVWA_CXX11_MODE
    {
        auto add_2 = bind(plus<int>(), _1, 2);
        cout << "bind: " << add_2(5) << endl;
    }

    {
        auto add_2 = [](int x) { return x + 2; };
        cout << "Lambda: " << add_2(5) << endl;
    }

    {
        /*
        1.中括号开始
        2.有参数列表
        3.有函数体，return 语句
        4.一般无返回值    有则   [](int x) -> int {...}
        5.全局的唯一类型  使用auto
        6.可以没有名字
        7.立即进行求值
        8.多重初始化的问题
        */
        auto adder = [](int n) { return [n](int x) { return x + n; }; };
        cout << "Currying: " << adder(2)(5) << endl;
    }

    {
        //function 模板
        //函数对象放到function之后，外界可以观察到的只剩下参数，返回值类型和执行结果
        //缺点：耗资源

        //把函数对象放进一个map中，必须使用fucntion模板
        map<string, function<int(int, int)>> op_dict{
            {"+", [](int x, int y) { return x + y; }},
            {"-", [](int x, int y) { return x - y; }},
            {"*", [](int x, int y) { return x * y; }},
            {"/", [](int x, int y) { return x / y; }},
        };
        cout << "std::function: " << op_dict.at("+")(1, 6) << endl;
    }
#endif
}
