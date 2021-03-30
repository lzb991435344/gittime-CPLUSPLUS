#include <chrono>    // std::chrono::seconds
#include <future>    // std::packaged_task
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

int work()
{
    this_thread::sleep_for(2s);
    return 42;
}

int main()
{
    //打包任务打包的是一个函数，模板参数就是一个函数类型
    //packaged_task只能移动，不能复制
    packaged_task<int()> task{work};
    //函数对象，既可以被调用，也可以传递给thread在新线程中移动
    auto fut = task.get_future();//得到打包任务的返回值，或者得知打包任务已经结束了
    scoped_thread th{move(task)};
    this_thread::sleep_for(1s);
    cout << "I am waiting now\n";
    cout << "Answer: " << fut.get() << '\n';
}
