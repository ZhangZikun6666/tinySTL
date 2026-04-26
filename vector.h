//
// Created by zzk11 on 26-4-16.
//

#pragma once
#include<cstddef>
#include<stdexcept>
#include<new>
#include"construct.h"
#include"allocator.h"
#include "uninitiallized.h"

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

public:
 	//Construct&Distruct
  	vector():begin_(nullptr),end_(nullptr),cap_(nullptr){}
    ~vector(){
		destroy(begin_,end_);
        allocator<T>::deallocate(begin_,cap_-begin_);
    }
    //capacity
    size_type size() const{ return end_-begin_;}

    size_type capacity() const{ return cap_-begin_;}

    bool empty() const{ return begin_==end_;}

    //Element access 元素访问
    reference operator[](size_type i){ return begin_[i];}
	const_reference operator[](size_type i) const{return begin_[i];}

    //Iterator 迭代器
    iterator begin(){ return begin_;}
    iterator end(){ return end_;}

    //core modifier
    void push_back(const T&val){
		if(end_==cap_){
			size_type old_size=size();
			size_type new_cap=(old_size==0)?1:2*old_size;
			pointer old_begin_=begin_;
        	pointer new_begin_=allocator<T>::allocate(new_cap);
			uninitialized_copy(begin_,begin_+old_size,new_begin_);
			destroy(old_begin_,old_begin_+old_size);
			allocator<T>::deallocate(old_begin_,cap_-begin_);
			begin_=new_begin_;
			end_=new_begin_+old_size;
			cap_=new_begin_+new_cap;
        }
  		construct(end_,val);
  		++end_;
    }
    void pop_back(){
		if(end_==begin_) {
			throw std::out_of_range("vector::pop_back");
		}
  		--end_;
  		destroy(end_);
  	}
public:
	void swap(vector& rhs) {
		std::swap(this->begin_,rhs.begin_);
		std::swap(this->end_,rhs.end_);
		std::swap(this->cap_,rhs.cap_);
	}
	vector(const vector& rhs): begin_(nullptr), end_(nullptr), cap_(nullptr) {
	    begin_ = allocator<T>::allocate(rhs.size());
	    end_=uninitialized_copy(rhs.begin_, rhs.end_, begin_);//这就是为什么uninitialized_copy有返回值
		cap_=begin_+rhs.size();
    }
	//假设我们这里传引用 直接把this和rhs swap会导致rhs被污染(假设rhs后面还有用)
	//但是如果直接传值 是调用默认拷贝构造函数创造临时对象 不会影响外部rhs
	vector& operator=(vector rhs){
		this->swap(rhs);
		return *this;
	}
};
}
