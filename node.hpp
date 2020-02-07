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
     //template <typename ot>
     //node(ot&& elem, node* p=nullptr): right{nullptr}, left{nullptr}, parent{p}, element{std::forward<ot>(elem)}{}
     node(const node& n, node* p=nullptr): right{nullptr}, left{nullptr}, parent{p}, element{n.element} {
         if(n.right) right=std::make_unique<node>(*n.right, this);
         if(n.left) left=std::make_unique<node>(*n.left, this);
     }

    int rnum(){ //right descendants
        if(right==nullptr) return 0;
        return 1+(right->rnum()+right->lnum());
    }
    int lnum(){ //left descendants
        if(left==nullptr) return 0;
        return 1+(left->rnum()+left->lnum());
    }

    std::pair<bool,node*> unbalanced(){ //returns bool (unbalanced) and node* (pointer to unbalanced node)
        std::pair<bool,node*> l{false,{}};
        std::pair<bool,node*> r{false,{}};
        std::cout<<"rnum "<<rnum()<<" lnum "<<lnum()<<"\n";
        if(lnum()>rnum()+1 || rnum()>lnum()+1) return {true,this};
        if(right!=nullptr) {r=this->right->unbalanced(); if(r.first) return {true, r.second};}
        if(left!=nullptr) {l=this->left->unbalanced(); if(l.first) return {true, l.second};}
        return {false,{}};
        }

    //overload operatore = ??

    ~node() noexcept = default;   // add noexcept

 };
 #endif
