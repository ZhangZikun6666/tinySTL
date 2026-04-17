//
// Created by zzk11 on 26-4-16.
//

#pragma once
#include<cstddef>
#include<stdexcept>
#include<new>

namespace tinySTL{

template<typename T>
class vector{
public:
  	//类型别名 type aliases
 	using value_type = T;
    using size_type = std::size_t;
    using pointer = T*;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;

private:
  	pointer begin_; //data
    pointer end_;
    pointer cap_;
	//Memory primitives 内存操作
    //allocate raw memory for n objects of typeT,without constructing them
    pointer allocate(size_t n){
     	return static_cast<pointer>(::operator new(n*sizeof(T)));
    }
    //Release memory allocated by allocate
    void deallocate(pointer p){
      	::operator delete(p);
    }
    //Construct a T prokect in-place at address p
    void construct(pointer p,const T&val){
      new(p) T(val);
    }
    //
    void destroy(pointer p){
     	p->~T();
    }
};
}
