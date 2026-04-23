//
// Created by zzk11 on 26-4-23.
//
#pragma once
#include"construct.h"
namespace tinySTL {
    template<typename InputIterator,typename ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first,InputIterator last,ForwardIterator d_first){
        for(;first!=last;++first) {
            construct(&*d_first,*first);
            ++d_first;
        }
        return d_first;
    }
    template<class ForwardIterator,class T>
    void uninitialized_fill(ForwardIterator first,ForwardIterator last,const T &val) {
        for(;first!=last;++first) {
            construct(&*first,val);
        }
    }
    template<class ForwardIterator,class Size,class T>
    ForwardIterator uninitialized_fill_n(ForwardIterator first,const Size &n,const T& val) {
        while(n--){
            first=construct(&*first,val);
            ++first;
        }
        return first;
    }
}