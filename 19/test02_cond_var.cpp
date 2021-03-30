#include <chrono>              // std::chrono::seconds
#include <condition_variable>  // std::condition_variable
#include <functional>          // std::ref
#include <iostream>            // std::cout
#include <mutex>               // std::mutex/unique_lock
#include <thread>              // std::thread/this_thread
#include <utility>             // std::forward/move

using namespace std;

class scoped_thread {
public:
    //可变模板 +  完美转发：实现了参数在传递过程中保持其值属性的功能
    template <typename... Arg>
    scoped_thread(Arg&&... arg)
        : thread_(std::forward<Arg>(arg)...)
    {
    }
    //移动构造函数
    scoped_thread(scoped_thread&& other)
        : thread_(std::move(other.thread_))
    {
    }
    ~scoped_thread() //析构函数
    {
        if (thread_.joinable()) {
            thread_.join();
        }
    }

private:
    thread thread_;
};

void work(condition_variable& cv,
          int& result)
{
    this_thread::sleep_for(2s);
    result = 42;
    cv.notify_one();
}

int main()
{
    condition_variable cv;
    mutex cv_mut;
    int result;

    //ref模板的使用：告知Thread构造函数，我们需要传递条件变量和结果变量作为引用
    //Thread默认复制或者移动的所有参数作为线程函数的参数
    scoped_thread th{work, ref(cv), ref(result)};
    cout << "I am waiting now\n";
    unique_lock lock{cv_mut};
    cv.wait(lock);
    cout << "Answer: " << result << '\n';
}
