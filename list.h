#pragma once
#include<cstddef>
#include"allocator.h"
#include"construct.h"

namespace tinySTL{
template <typename T>
//链表节点结构体
struct list_node{
    list_node* prev;
    list_node* next;
    T data;
};

template <typename T>
//链表迭代器
struct list_iterator{
    using reference=T&;
    using pointer=T*;
    //迭代器的内部是一个真正的节点指针
    list_node<T>* node_;
    //结构体构造函数
    list_iterator(list_node<T>* x):node_(x){}

    //重载解引用操作符
    reference operator*() const{
        //直接返回节点里的data
        return node_->data;
    }
    //重载->操作符 这个操作符只会用来访问数据里的字段 也就是data里面的数据(比如姓名 年龄etc.)
    //外界是不会看到所谓的next prev等等
    pointer operator->() const{
        //这里要返回存储数据的对象T data的原生指针 也就是返回T*
        return &(operator*());
    }

    //重载前置递增操作符 ++it
    list_iterator& operator++(){
        node_=node_->next;
        return *this;
        //this是一个指针 这里要返回一个引用所以要*解引用
    }
    list_iterator& operator--(){
        node_=node_->prev;
        return *this;
    }
    bool operator==(const list_iterator& rhs){
        return rhs.node_==node_;
    }
    bool operator!=(const list_iterator& rhs){
        return rhs.node_!=node_;
    }
};
//链表本体
template<typename T>
class list{
public:
    using value_type=T;
    using size_type=std::size_t;
    using pointer=T*;
    using reference=T&;
    using iterator=list_iterator<T>;
private:
    list_node<T>* node_; //哨兵节点 通过实现头尾相接从根源上避免段错误的产生
    size_type size_;

    //初始化辅助函数
    void empty_initialize(){
        //node_是一个指针 这个node_所指向的空间是一个哨兵节点 他的前后都指向自己
        //从根源上避免访问野指针的bug
        node_=new list_node<T>; 
        node_->prev=node_;
        node_->next=node_;
        size_=0;
    }
public:
    list(){ empty_initialize(); }
    bool empty() const{
        return size_==0;
    }

    size_t size() const{
        return size_;
    }
    //begin():用第一个真实节点构造迭代器返回
    iterator begin() noexcept{
        return iterator(node_->next);
    }
    //end():用哨兵节点自己构造一个迭代器返回
    iterator end() noexcept{
        return iterator(node_);
    }

};

}