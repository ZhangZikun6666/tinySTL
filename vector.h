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
	void swap(vector& rhs) noexcept {
		std::swap(this->begin_,rhs.begin_);
		std::swap(this->end_,rhs.end_);
		std::swap(this->cap_,rhs.cap_);
	}
	vector(const vector& rhs): begin_(nullptr), end_(nullptr), cap_(nullptr) {
	    begin_ = allocator<T>::allocate(rhs.size());
	    end_=uninitialized_copy(rhs.begin_, rhs.end_, begin_);//这就是为什么uninitialized_copy有返回值
		cap_=begin_+rhs.size();
    }
	//这里如果直接传值 1.是调用默认拷贝构造函数创造临时对象 不会影响外部rhs 2.同时不需要防止自我赋值
	//拷贝赋值函数用于接受左值
	vector& operator=(const vector &rhs){
		if(&rhs!=this) {
			vector tmp(rhs);
			this->swap(tmp);
		}
		return *this;
	}

	//移动构造函数 &&表示右值引用 也就是马上会消亡
	vector(vector&& rhs) noexcept:begin_(nullptr),end_(nullptr),cap_(nullptr){
		this->swap(rhs);
	}
	//移动赋值运算符用于接受std::move所产生的右值
	//如果使用传统的移动赋值 会先把自己的内存 deallocate 掉。转身去抢 rhs 的内存（但 rhs就是自己，内存已经被清空了）最终把一个空指针塞给自己，导致数据完全丢失。
    vector &operator=(vector&& rhs) noexcept{
		if(this!=&rhs) this->swap(rhs);
		return *this;
	}
public:
	iterator erase(iterator pos) {
		if(pos==end_) return pos;
		for(iterator it=pos+1;it!=end_;++it) {
			*(it-1)=*it;
		}
		--end_;
		destroy(end_);//end_原本指向的内存就是空的 --之后就是因为erase而空出来的内存 直接destroy即可
		return pos;
	}
	iterator insert(iterator pos,const T& val) {
		size_type offset=pos-begin_;
		if(end_!=cap_) {
			if(pos==end_) {
				push_back(val);
			}
			else {
				value_type lastVal=*(end_-1);
				construct(end_,lastVal);
				for(iterator it=end_-1;it!=pos;--it) {
					*it=*(it-1);
				}
				*pos=val;
				++end_;
			}
			return pos;
		}else {
			size_type old_size=size();
			size_type new_size=(size()==0)?1:2*size();
			pointer new_begin=allocator<T>::allocate(new_size);
			uninitialized_copy(begin_,begin_+offset,new_begin);
			construct(new_begin+offset,val);
			uninitialized_copy(begin_+offset,end_,new_begin+offset+1);
			destroy(begin_,end_);
			allocator<T>::deallocate(begin_,cap_-begin_);
			begin_=new_begin;
			cap_=new_begin+new_size;
			end_=new_begin+old_size+1;
			return new_begin+offset;
		}

	}
};
}
