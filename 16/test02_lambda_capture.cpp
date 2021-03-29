#include <chrono>    // std::chrono::milliseconds
#include <iostream>  // std::cout
#include <sstream>   // std::ostringstream
#include <string>    // std::string
#include <thread>    // std::thread/this_thread

using namespace std;


//按值捕获值
int get_count()
{
    static int count = 0;
    return ++count;
}

class task {
public:
    task(int data) : data_(data) {}
    auto lazy_launch()
    {
        //按值捕获外围对象 *this
        //mutable 捕获的内容可更改
        //count = get_count() 在生成lamba表达式时计算并储存等号后的表达式的结果
        return [*this, count = get_count()]() mutable {
            ostringstream oss;
            oss << "Done work " << data_ << " (No. " << count
                << ") in thread " << this_thread::get_id() << '\n';
            msg_ = oss.str();
            calculate();
        };
    }
    void calculate()
    {
        this_thread::sleep_for(100ms);
        cout << msg_;
    }

private:
    int data_;
    string msg_;
};

int main()
{
    auto t = task{37};
    //多线程既复制了任务对象，也可以进行独立运算
    thread t1{t.lazy_launch()};
    thread t2{t.lazy_launch()};
    t1.join();
    t2.join();
}
