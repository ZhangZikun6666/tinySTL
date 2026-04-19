//
// Created by zzk11 on 26-4-19.
//

#pragma once;
#include <new>

namespace tinySTL {
    template <typename T,typename ValueType>
    void construct(T* p,const ValueType& value) {
        //强制调用头文件new里面的placement new 防止调用其他重载
        new(static_cast<void*>(p)) ValueType(value);
    }
    template <typename T>
    void destroy(T* pointer) {
        if(pointer!=nullptr) {
            pointer->~T();
        }
    }
    template <typename ForwardIterator>
    void destroy(ForwardIterator first,ForwardIterator last) {
        for(;first!=last;++first) {
            //传入的迭代器可能有多种类型 如果是vector 那就是指针 但如果是链表就不是
            //而destroy函数只能接受指针 所以我们使用*first获取对象本身之后取地址获取获取对象的实际指针
            destroy(&*first);
        }
    }

}