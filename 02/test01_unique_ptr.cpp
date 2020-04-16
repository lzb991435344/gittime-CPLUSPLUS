#include <utility>  // std::swap/move
#include "shape.h"  // shape/shape_type/create_shape

template <typename T>
class smart_ptr {
public:
    //explicit关键字只对有一个参数的类构造函数有效
    //explicit关键字的作用就是防止类构造函数的隐式自动转换
    //使用nullptr表示空指针
    explicit smart_ptr(T* ptr = nullptr)
        : ptr_(ptr) {}
    ~smart_ptr()
    {
        delete ptr_;
    }
    smart_ptr(smart_ptr&& other)
    {
        ptr_ = other.release();
    }
    smart_ptr& operator=(smart_ptr rhs)
    {
        rhs.swap(*this);
        return *this;
    }

    T* get() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    operator bool() const { return ptr_; }
    T* release()
    {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
    void swap(smart_ptr& rhs)
    {
        using std::swap;
        //swap就是通过引用来交换a，b的值。
        swap(ptr_, rhs.ptr_);
    }

private:
    T* ptr_;
};

int main()
{
    smart_ptr<shape> ptr1{create_shape(shape_type::circle)};

    //explict关键字作用，不能隐式转换
    //smart_ptr<shape> ptr2{ptr1};             // Cannot compile
    smart_ptr<shape> ptr3;
    //ptr3 = ptr1; 

    //std::move并不能移动任何东西，它唯一的功能是将一个左值强制转化为右值引用，
    //继而可以通过右值引用使用该值，以用于移动语义                            // Cannot compile
    ptr3 = std::move(ptr1);                  // OK
    smart_ptr<shape> ptr4{std::move(ptr3)};  // OK
}
