#ifndef _iterator_hpp
#define _iterator_hpp

#include "node.hpp"

template<typename node_t, typename T>
class _iterator{
    node_t* current;

    public:

    using value_type = T;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    _iterator(node_t* n) noexcept: current{n} {}

    _iterator (const _iterator& i) noexcept: current{i.current} {}

    _iterator& operator=(const _iterator& i) noexcept{
        current=i.current;
        return *this;
    }

    reference operator*() const noexcept{
        return current->element;
    }
    
    _iterator& operator++() noexcept {
        if(current->right.get()!=nullptr){
            node_t* temp=current->right.get();
            while(temp->left.get() != nullptr) temp=temp->left.get();
            current=temp;
        }
        else{
            node_t* temp=current; 
            while(temp->parent != nullptr && temp->parent->left.get() != temp) temp=temp->parent;
            current=temp->parent;
        }
        return *this;
     }


    bool operator==(const _iterator& a) const noexcept{
      return a.current == current;
    }

    bool operator!=(const _iterator& a) const noexcept{
      return !(a == *this);
    }
};
#endif
