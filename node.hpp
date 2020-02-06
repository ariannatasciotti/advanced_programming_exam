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

     //node(const T& elem, node* p=nullptr): right{nullptr}, left{nullptr}, parent{p}, element{elem}{}
     //node(T&& elem, node* p=nullptr): right{nullptr}, left{nullptr}, parent{p}, element{std::move(elem)}{}
     template <typename ot>
     node(ot&& elem, node* p=nullptr): right{nullptr}, left{nullptr}, parent{p}, element{std::forward<ot>(elem)}{}
     node(const node& n, node* p=nullptr): right{nullptr}, left{nullptr}, parent{p}, element{n.element} {
         if(n.right) right=std::make_unique<node>(*n.right, this);
         if(n.left) left=std::make_unique<node>(*n.left, this);
     }

    //overload operatore = ??

    ~node() noexcept = default;   // add noexcept

   /* void cancel(){
        if(this->left!=nullptr) {
            this->left->cancel();
            this->left.release();
        }
        if(this->right!=nullptr) {
            this->right->cancel();
            this->right.release();
        }
        if(this->parent!=nullptr) delete this;
    } */

 };
 #endif
