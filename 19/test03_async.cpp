#include <chrono>    // std::chrono::seconds
#include <future>    // std::async
#include <iostream>  // std::cout
#include <thread>    // std::this_thread

using namespace std;

int work()
{
    this_thread::sleep_for(2s);
    return 42;
}

int main()
{
    //async返回一个未来量，work函数不用关心条件变量之间的事情
    //返回的类型为  functure<int>  返回结果是返回值或者异常
    //ps： 1.1个future 只能调用一个get函数，多调用会产生未定义的行为
    auto fut = async(launch::async, work);
    cout << "I am waiting now\n";
    cout << "Answer: " << fut.get() << '\n';
}
