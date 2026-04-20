//
// Created by zzk11 on 26-4-16.
//

#pragma once
#include<cstddef>
#include<stdexcept>
#include<new>
#include"constuct.h"

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

public:
 	//Construct&Distruct
  	vector():begin_(nullptr),end_(nullptr),cap_(nullptr){}
    ~vector(){
		destroy(begin_,end_);
        deallocate(begin_);
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
        	pointer new_begin_=allocate(new_cap);
			for(size_type i=0;i<old_size;++i){
            	construct(new_begin_+i,old_begin_[i]);
			}
			destroy(old_begin_,old_begin_+old_size);
			deallocate(old_begin_);
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
};
}
