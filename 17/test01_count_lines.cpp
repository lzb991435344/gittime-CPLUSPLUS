#include <algorithm>                   // std::transform
#include <fstream>                     // std::ifstream
#include <iostream>                    // std::cout/endl
#include <iterator>                    // std::distance
#include <numeric>                     // std::accumulate
#include <vector>                      // std::vector
#include <nvwa/istream_line_reader.h>  // nvwa::istream_line_reader

using namespace std;
using nvwa::istream_line_reader;


//函数式编程的特点
//1.会影响函数结果的只是函数的参数，对环境没有依赖
//2.返回的结果就是函数执行的唯一结果，不产生对环境的其他影响
int count_file(const char* name)
{
    ifstream ifs(name);
    istream_line_reader reader(ifs);
    return distance(reader.begin(), reader.end());
}

int count_lines(const char** begin, const char** end)
{
    vector<int> count(end - begin);
    //transform把一个范围内的对象转换成相同数量的另外一些对象，抽象功能 algorithm
    transform(begin, end, count.begin(), count_file);

    //accumulate 在指定的范围内，使用给定的初值和函数对象，从左往右对数值进行归并  numeric
    return accumulate(count.begin(), count.end(), 0);
}

int main(int argc, const char** argv)
{
    int total_lines = count_lines(argv + 1, argv + argc);
    cout << "Total lines: " << total_lines << endl;
}
