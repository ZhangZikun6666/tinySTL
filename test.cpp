//
// Created by zzk11 on 26-4-16.
//
#include<iostream>
#include"vector.h"
using namespace std;
int main(){
     cout<<"Hello world!"<<endl;
     tinySTL::vector<int> v;
     for(int i=0;i<10;i++) {
          v.push_back(i);
     }
     for(int i=0;i<v.size();i++) {
          cout<<v[i]<<endl;
     }
     return 0;
}
