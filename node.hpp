/**
* @file node.hpp
* @author Lorenzo Basile
* @author Arianna Tasciotti
* @date February 2020
* @brief Header containing node struct implementation.
*/

#ifndef _node_hpp
#define _node_hpp

#include <memory>
#include <utility>

template <typename T>
struct node{
    
    /** @brief Unique pointer to the right child. */
     std::unique_ptr<node> right;
    
    /** @brief Unique pointer to the left child. */
     std::unique_ptr<node> left;
    
    /** @brief Raw pointer to the parent node. */
     node* parent;
    
    /** @brief Member variable of type T. */
     T element;
    
    
     using value_type=T;

   /**
    * @brief Constructs a node initializing left and right children to nullptr, parent to the input pointer to node, element to the input data.
    * @tparam elem const lvalue reference to the type of element.
    * @tparam p pointer to parent node.
    */
    
    node(const T& elem, node* p=nullptr) noexcept: right{nullptr}, left{nullptr}, parent{p}, element{elem}{}
    
   /**
    * @brief Constructs a node initializing left and right children to nullptr, parent to the input pointer to node, element to the input data using std::move.
    * @tparam elem rvalue reference to the type of element.
    * @tparam p pointer to parent node.
    */
    
    node(T&& elem, node* p=nullptr) noexcept: right{nullptr}, left{nullptr}, parent{p}, element{std::move(elem)}{}
    
   /**
    * @brief Copy constructor. It calls itself recursively.
    * @tparam elem const lvalue reference to node to be copied.
    * @tparam p pointer to parent node.
    */
    
    node(const node& n, node* p=nullptr): right{nullptr}, left{nullptr}, parent{p}, element{n.element} {
         if(n.right) right=std::make_unique<node>(*n.right, this);
         if(n.left) left=std::make_unique<node>(*n.left, this);
     }
    
   /**
    * @brief Destroys the node object.
    */
    
     ~node() noexcept = default;
    
   /**
    * @brief This function counts the number of right and left descendants of a node.
    * @return std::pair<int,int> number of right and left descendants.
    */

    std::pair<int, int> num_nodes() const noexcept{
        if(!right && !left ) return {0,0};
        else if(!right && left) return {0, 1+(left->num_nodes().first+left->num_nodes().second)};
        else if(right && !left) return {1+(right->num_nodes().first+right->num_nodes().second),0};
        else return {1+(right->num_nodes().first+right->num_nodes().second), 1+(left->num_nodes().first+left->num_nodes().second)};
    }

   /**
    * @brief This function checks if the subtree on whose root it is invoked is unbalanced and calls itself recursively on children nodes.
    * @return std::pair<bool,const node*> true,pointer to the node where unbalance is found or false,nullptr otherwise.
    */
    
    std::pair<bool,const node*> unbalanced_node() const noexcept{
           std::pair<bool,const node*> l{false,nullptr};
           std::pair<bool,const node*> r{false,nullptr};
           std::cout<<"rnum "<<num_nodes().first<<" lnum "<<num_nodes().second<<"\n";
           if(num_nodes().second>num_nodes().first+1 || num_nodes().first>num_nodes().second+1) return {true,this};
           if(right) {r=this->right->unbalanced_node(); if(r.first) return {true, r.second};}
           if(left) {l=this->left->unbalanced_node(); if(l.first) return {true, l.second};}
           return {false,nullptr};
           }

 };
 #endif
