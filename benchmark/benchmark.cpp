#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#include "bst.hpp"
#include <map>

int main(int argc, char **argv){
    bst<int, double> tree;
    std::map<int,double> tree_map;
    std::vector<int> v;
    std::vector<double> d;
    long unsigned int count=0u;
    if(argc!=2) return 1;
    const std::size_t size=atoi(argv[1]);
    double step=10./size;
    double oneoversize=1./size;
    std::size_t i;
    for(i=0; i<size; i++) v.emplace_back(i);
    for(i=0; i<size; i++) d.emplace_back(i*step);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
    std::shuffle(d.begin(), d.end(), g);
    for(i=0; i<size; i++) {
        tree_map.emplace(v[i],d[i]);
        tree.emplace(v[i],d[i]);

    }
    auto t=std::chrono::high_resolution_clock::now(); //start of time measurement
    for(i=0; i<size; i++) count+=(*tree.find(i)).first;
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t); //end of time measurement
    std::cout<<"time with unbalanced tree: "<<elapsed.count()*oneoversize<<std::endl;
    //std::cout<<count<<std::endl;
    tree.balance();
    count=0;
    t=std::chrono::high_resolution_clock::now();
    for(i=0; i<size; i++) count+=(*tree.find(i)).first;
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t);
    std::cout<<"time with balanced tree: "<<elapsed.count()*oneoversize<<std::endl;
    //std::cout<<count<<std::endl;
    count=0;
    t=std::chrono::high_resolution_clock::now();
    for(i=0; i<size; i++) count+=(*tree_map.find(i)).first;
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t);
    std::cout<<"time with std::map: "<<elapsed.count()*oneoversize<<std::endl;
    //std::cout<<count;

	return 0;
}
