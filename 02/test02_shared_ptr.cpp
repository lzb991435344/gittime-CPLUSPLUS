#include <stdio.h>      // printf/puts
#include "shape.h"      // shape/shape_type/create_shape
#include "smart_ptr.h"  // smart_ptr

int main()
{
    smart_ptr<circle> ptr1(new circle());
    printf("use count of ptr1 is %ld\n", ptr1.use_count());
    smart_ptr<shape> ptr2;
    printf("use count of ptr2 was %ld\n", ptr2.use_count());
    ptr2 = ptr1;
    printf("use count of ptr2 is now %ld\n", ptr2.use_count());
    if (ptr1) {
        puts("ptr1 is not empty");
    }
    /** dynamic_cast
        作用：将一个基类对象指针（或引用）cast到继承类指针
        将基类的指针或引用安全地转换成派生类的指针或引用，并用派生类的指针或
        引用调用非虚函数。如果是基类指针或引用调用的是虚函数无需转换就能在运行时调用派生类的虚函数。
    
    dynamic_cast< type* >(e) 
　       type必须是一个类类型且必须是一个有效的指针 
    dynamic_cast< type& >(e) 
        type必须是一个类类型且必须是一个左值 
    dynamic_cast< type&& >(e) 
         type必须是一个类类型且必须是一个右值

    */


    //当指针是智能指针时候，向下转换
    smart_ptr<circle> ptr3 = dynamic_pointer_cast<circle>(ptr2);
    printf("use count of ptr3 is %ld\n", ptr3.use_count());
}
