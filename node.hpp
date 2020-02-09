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

    int rnum() const noexcept{ //right descendants
        if(!right) return 0;
        return 1+(right->rnum()+right->lnum());
    }
    int lnum() const noexcept{ //left descendants
        if(!left) return 0;
        return 1+(left->rnum()+left->lnum());
    }

    std::pair<bool,const node*> unbalanced() const noexcept{ //returns bool (unbalanced) and node* (pointer to unbalanced node)
        std::pair<bool,const node*> l{false,{}};
        std::pair<bool,const node*> r{false,{}};
        std::cout<<"rnum "<<rnum()<<" lnum "<<lnum()<<"\n";
        if(lnum()>rnum()+1 || rnum()>lnum()+1) return {true,this};
        if(right) {r=this->right->unbalanced(); if(r.first) return {true, r.second};}
        if(left) {l=this->left->unbalanced(); if(l.first) return {true, l.second};}
        return {false,{}};
        }

    //overload operatore = ??

    ~node() noexcept = default;   // add noexcept

 };
 #endif
