#include <chrono>    // std::chrono::seconds
#include <future>    // std::promise
#include <iostream>  // std::cout
#include <thread>    // std::thread/this_thread
#include <utility>   // std::forward/move

using namespace std;

class scoped_thread {
public:
    template <typename... Arg>
    scoped_thread(Arg&&... arg)
        : thread_(std::forward<Arg>(arg)...)
    {
    }
    scoped_thread(scoped_thread&& other)
        : thread_(std::move(other.thread_))
    {
    }
    ~scoped_thread()
    {
        if (thread_.joinable()) {
            thread_.join();
        }
    }

private:
    thread thread_;
};

void work(promise<int> prom)
{
    this_thread::sleep_for(2s);
    //不需要在一个函数结束的时候去设置future的值
    prom.set_value(42);
}

int main()
{
    //承诺量 promise<int> pro;
    //promise和future 结对出现，且只能使用一次
    promise<int> prom;
    auto fut = prom.get_future();

    scoped_thread th{work, move(prom)};
    cout << "I am waiting now\n";
    cout << "Answer: " << fut.get() << '\n';
}
