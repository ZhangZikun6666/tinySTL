//
// Created by zzk11 on 26-4-21.
//

#pragma once
#include <new>
#include <cstddef>

namespace tinySTL {
template<class T>
class allocator {
public:
    using value_type=T;
    using pointer=T*;
    using size_type=std::size_t;
    static pointer allocate(size_type n) {
        if(n==0) return nullptr;
        return static_cast<pointer>(::operator new(sizeof(value_type)*n));
    }
    static void deallocate(pointer p,size_type n) {
        (void)n;
        ::operator delete(p);
    }
};

}