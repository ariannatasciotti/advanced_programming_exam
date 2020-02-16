#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#include "bst.hpp"
#include <map>
#define max_size 100000000 // maximum number of nodes due to memory limitation

int main(int argc, char **argv){
    bst<int, double> tree;
    std::map<int,double> tree_map;
    std::vector<int> v;
    std::vector<double> d;
    long unsigned int count=0u;
    
    // if the user does not pass a size, exit
    if(argc!=2){
        std::cout<<"This program needs an argument (tree size) \n";
        return 1;
    }
    
    char* temp;
    
    // size of containers
    const std::size_t size=strtoul(argv[1],&temp,10);
    
    // if the user inserts a negative number (or a very big positive number), exit
    if(size>max_size){
        std::cout<<"Please insert a valid (reasonably small) positive integer size \n";
        return 2;
    }
    
    // if the user inserts 0 or not a number, the results are undefined
    if(size==0) std::cout<<"Please insert a valid integer size \n";
    
    double step=10./size;
    double oneoversize=1./size;
    
    std::size_t i;
    
    // initialize vector v with integers in range 0,size
    for(i=0; i<size; i++) v.emplace_back(i);
    
    // initialize vector d with doubles in range 0,10
    for(i=0; i<size; i++) d.emplace_back(i*step);
    
    // uniformly-distributed integer random number generator
    std::random_device rd;
    
    // random reorder of numbers in v and d
    std::shuffle(v.begin(), v.end(), rd);
    std::shuffle(d.begin(), d.end(), rd);
    
    // initialize bst tree and std::map data structure with vector v (keys) and vector d (values)
    for(i=0; i<size; i++) {
        tree_map.emplace(v[i],d[i]);
        tree.emplace(v[i],d[i]);

    }
    
    // timing unbalanced bst tree
    auto t=std::chrono::high_resolution_clock::now();
    for(i=0; i<size; i++) count+=(*tree.find(i)).first; //summing keys to make sure find() is performed
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t);
    std::cout<<"time with unbalanced tree: "<<elapsed.count()*oneoversize<<std::endl; // average over size of the tree
    //std::cout<<count<<std::endl;
    
    tree.balance(); // balance bst tree
    count=0;
    
    // timing balanced bst tree
    t=std::chrono::high_resolution_clock::now();
    for(i=0; i<size; i++) count+=(*tree.find(i)).first;
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t);
    std::cout<<"time with balanced tree: "<<elapsed.count()*oneoversize<<std::endl;
    //std::cout<<count<<std::endl;
    
    count=0;
    
    // timing std::map tree
    t=std::chrono::high_resolution_clock::now();
    for(i=0; i<size; i++) count+=(*tree_map.find(i)).first;
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t);
    std::cout<<"time with std::map: "<<elapsed.count()*oneoversize<<std::endl;
    //std::cout<<count;
    
    return 0;
}

