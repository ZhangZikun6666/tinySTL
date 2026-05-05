//
// Created by zzk11 on 26-4-16.
//
#include<iostream>
#include"vector.h"
using namespace std;
int main(){
     cout<<"Hello world!"<<endl;
     tinySTL::vector<int> v;
     //在没有手写构造函数的时候 v1=v2只会使用默认构造函数进行浅拷贝 这时候释放内存的时候由于两块内存的地址相同 就会发生double free
     for(int i=0;i<10;i++) {
          v.push_back(i);
     }
     for(int i=0;i<v.size();i++) {
          cout<<v[i]<<" ";
     }
     cout<<'\n';
     tinySTL::vector<int> v1;
     tinySTL::vector<int> v2;
     v1.push_back(1);
     v2=v1;
     cout<<v1[0]<<" "<<v2[0]<<'\n';
     v.erase(v.begin());
     for(int i=0;i<v.size();i++) {
          cout<<v[i]<<" ";
     }
     cout<<'\n';
     v.reserve(100);
     v.insert(v.begin(),999);
     for(int i=0;i<v.size();i++) {
          cout<<v[i]<<" ";
     }
     cout<<'\n'<<v.capacity()<<'\n';
     v={1,2,3,4,5};
     for(int i=0;i<v.size();i++) {
          cout<<v[i]<<" ";
     }
     return 0;
}
