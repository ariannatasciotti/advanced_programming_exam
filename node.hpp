#ifndef _node_hpp
#define _node_hpp

#include <memory>
#include <utility>

template <typename T>
struct node{
     std::unique_ptr<node> right;
     std::unique_ptr<node> left;
     node* parent;
     T element;
     using value_type=T;

    
    node(const T& elem, node* p=nullptr) noexcept: right{nullptr}, left{nullptr}, parent{p}, element{elem}{}
    
     node(T&& elem, node* p=nullptr) noexcept: right{nullptr}, left{nullptr}, parent{p}, element{std::move(elem)}{}
    
     node(const node& n, node* p=nullptr): right{nullptr}, left{nullptr}, parent{p}, element{n.element} {
         if(n.right) right=std::make_unique<node>(*n.right, this);
         if(n.left) left=std::make_unique<node>(*n.left, this);
     }
    
    
     ~node() noexcept = default;
    
    //NUM_NODES (returns the number of right and left nodes wrt the root stored in a pair)

    std::pair<int, int> num_nodes() const noexcept{
        if(!right && !left ) return {0,0};
        else if(!right && left) return {0, 1+(left->num_nodes().first+left->num_nodes().second)};
        else if(right && !left) return {1+(right->num_nodes().first+right->num_nodes().second),0};
        else return {1+(right->num_nodes().first+right->num_nodes().second), 1+(left->num_nodes().first+left->num_nodes().second)};
    }

    //UNBALANCED (returns bool (unbalanced) and pointer to unbalanced node)
    
    std::pair<bool,const node*> unbalanced() const noexcept{
           std::pair<bool,const node*> l{false,{}};
           std::pair<bool,const node*> r{false,{}};
           std::cout<<"rnum "<<num_nodes().first<<" lnum "<<num_nodes().second<<"\n";
           if(num_nodes().second>num_nodes().first+1 || num_nodes().first>num_nodes().second+1) return {true,this};
           if(right) {r=this->right->unbalanced(); if(r.first) return {true, r.second};}
           if(left) {l=this->left->unbalanced(); if(l.first) return {true, l.second};}
           return {false,{}};
           }

 };
 #endif
