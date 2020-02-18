/**
* @file iterator.hpp
* @author Lorenzo Basile
* @author Arianna Tasciotti
* @date February 2020
* @brief Header containing _iterator class implementation.
*/

#ifndef _iterator_hpp
#define _iterator_hpp

#include "node.hpp"

template<typename node_t, typename pair_type>
class _iterator{

    /** @brief Raw pointer to a node of type node_t. */
    node_t* current;

    public:

    using value_type = pair_type;
    using reference = value_type&;
    using pointer = value_type*;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    /**
     * @brief Constructs a new _iterator setting current to the input pointer.
     * @tparam n input pointer to a node.
     */

    explicit _iterator(node_t* n) noexcept: current{n} {}

   /**
    * @brief Destroys the _iterator object.
    */

    ~_iterator() noexcept = default;

   /**
    * @brief Copy constructor.
    * @tparam i const lvalue reference to _iterator.
    */

    _iterator (const _iterator& i) noexcept: current{i.current} {}

   /**
    * @brief Copy assignment.
    * @tparam i const lvalue reference to _iterator.
    */

    _iterator& operator=(const _iterator& i) noexcept{
        current=i.current;
        return *this;
    }

   /**
    * @brief Dereference operator.
    * @return reference to the value stored in the node pointed by the iterator.
    */

    reference operator*() const noexcept{
        return current->element;
    }

   /**
    * @brief Pre-increment operator. It is used to traverse the tree from left to right.
    * @return _iterator& reference to _iterator.
    */

    _iterator& operator++() noexcept {
        if(current->right.get()){
            node_t* temp=current->right.get();
            while(temp->left.get()) temp=temp->left.get();
            current=temp;
        }
        else{
            node_t* temp=current;
            while(temp->parent && temp->parent->left.get() != temp) temp=temp->parent;
            current=temp->parent;
        }
        return *this;
     }

   /**
    * @brief Boolean equality operator.
    * @tparam a const lvalue reference to _iterator.
    * @return bool true if the iterators point to the same node.
    */

    bool operator==(const _iterator& a) const noexcept{
      return a.current == current;
    }

   /**
    * @brief Boolean inequality operator.
    * @tparam a const lvalue reference to _iterator.
    * @return bool true if the iterators point to different nodes.
    */

    bool operator!=(const _iterator& a) const noexcept{
      return !(a == *this);
    }
};
#endif
