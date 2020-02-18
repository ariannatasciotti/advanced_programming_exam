/**
* @file bst.hpp
* @author Lorenzo Basile
* @author Arianna Tasciotti
* @date February 2020
* @brief Header containing bst class implementation.
*/


#ifndef _bst_hpp
#define _bst_hpp

#include <utility>
#include <memory>
#include "node.hpp" //already included by iterator header, here for clarity
#include "iterator.hpp"
#include <vector>


  /**
   * @brief A utility for the function balance(): given a vector ordered in some way, this function builds another vector containing "moving" median values.
   * Given a vector, the function stores in another vector the median element of the previous vector and removes from the vector the median value. Then, it calls itself
   * recursively on right and left subvectors, until the size of the vector is equal to one.
   * @tparam v lvalue reference to std::vector<T> input vector.
   * @tparam median lvalue reference to std::vector<T> vector in which the previous is reordered.
   */

template <typename T>
void reorder(std::vector<T>& v, std::vector<T>& median){
    if(v.size()==0) return;
    auto value=v[v.size()/2];
    median.emplace_back(value);
    v.erase(v.begin()+v.size()/2);
    if(v.size()>1) {
        std::vector<T> right_s(v.end()-v.size()/2, v.end());
        reorder(right_s,median);
        std::vector<T> left_s(v.begin(), v.begin()+v.size()/2+v.size()%2);
        reorder(left_s,median);
    }
    if(v.size()==1) median.emplace_back(v[0]);
}

template <typename key_type, typename value_type, typename cmp_op=std::less<key_type>>
class bst{

    using pair_type = std::pair<const key_type, value_type>;
    using node_type = node<pair_type>;
    using iterator = _iterator <node_type, typename node_type::value_type>;
    using const_iterator = _iterator<node_type, const typename node_type::value_type>;

    /** @brief Comparison operator for bst. */
    cmp_op op;

    /** @brief Unique pointer to the root node. */
    std::unique_ptr<node_type> root;

   /**
    * @brief A utility function called by insert and emplace functions. It calls _find to know if the key is already present in the tree; if it is not, it looks for the right place to insert the new node and allocates it.
    * @tparam x<ot> input pair.
    * @return std::pair<iterator,bool> iterator to the new node, true or iterator to already existing node, false.
    */

    template<typename ot>
    std::pair<iterator, bool> _insert(ot&& x){
    auto f=_find(x.first);
    if(f) return std::make_pair(iterator{f}, false);
    if(!root){
        root=std::make_unique<node_type>(std::forward<ot>(x), nullptr);
        return std::make_pair(iterator{root.get()}, true);
    }
    auto temp=root.get();
    while((op(temp->element.first,x.first) && temp->right) || (op(x.first,temp->element.first) && temp->left)){
        if(op(temp->element.first,x.first)) temp=temp->right.get();
        else temp=temp->left.get();
    }
    if(op(temp->element.first,x.first)){
        temp->right=std::make_unique<node_type>(std::forward<ot>(x), temp);
        return std::make_pair(iterator{temp->right.get()}, true);
    }
    else {
        temp->left=std::make_unique<node_type>(std::forward<ot>(x), temp);
        return std::make_pair(iterator{temp->left.get()}, true);
    }
    }


   /**
    * @brief A utility function implemented to return a pointer instead of an iterator. It performs a binary search of a given key starting from the root.
    * @tparam x const lvalue reference to key.
    * @return node_type* pointer to the node containing the key or nullptr.
    */

    node_type* _find (const key_type& x)const {
        node_type* temp=root.get();
        while(temp){
            key_type key=temp->element.first;
            if(!(op(key, x) || op(x, key))){
                return temp;
            }
            else if(op(key, x)){
                temp=temp->right.get();
            }
            else{
                temp=temp->left.get();
            }
        }
        return nullptr;
    }

   /**
    * @brief A utility function implemented to find the leftmost node of a subtree, given a pointer to its root.
    * @tparam node input pointer to a node.
    * @return node_type* pointer to the leftmost node.
    */

    node_type* findmin(node_type* node)const noexcept{
        if(!node->left.get()){
            return node;
        } else{
            return findmin(node->left.get());
        }
    }

   /**
    * @brief A utility function implemented to find the place to attach the left child of the node to be erased, called by function erase.
    * @tparam node input pointer to a node.
    * @return node_type* pointer to the leftmost node of the right subtree or to parent.
    */

    node_type* leftmost(node_type* node)const noexcept{
        if(!node->right) return node->parent;
        else return findmin(node->right.get());
    }

    public:

   /**
    * @brief Constructs a new bst object with a comparison operator of type cmp_op.
    * @tparam x object of type cmp_op.
    */

    explicit bst(cmp_op x) noexcept: op{x}{}

   /**
    * @brief Constructs a new bst object.
    */

    bst() noexcept=default;

   /**
    * @brief Destroys the bst object.
    */

    ~bst() noexcept=default;



   /**
    * @brief Copy constructor.
    * Creates a deep copy of a bst tree calling the copy constructor of node.
    * @tparam b const lvalue reference to the tree to be copied.
    */

    bst(const bst& b): op{b.op}, root{(!b.root)? nullptr:std::make_unique<node_type>(*b.root)} {}

   /**
    * @brief Copy assignment.
    * @tparam b const lvalue reference to the tree to be copied.
    * @return bst&.
    */

    bst& operator=(const bst& b){
        if(this!=&b){
            this->clear();
            op=b.op;
            if(b.root) root=std::make_unique<node_type>(*b.root);
        }
        return *this;
    }

   /**
    * @brief Move constructor.
    * @tparam b rvalue reference to the tree to be moved.
    */

    bst(bst&& b) noexcept: op{std::move(b.op)}, root{b.root.release()} {}

   /**
    * @brief Move assignment.
    * @tparam b rvalue reference to the tree to be moved.
    * @return bst&.
    */

    bst& operator=(bst&& b) noexcept{
        root.reset(b.root.release());
        op=std::move(b.op);
        return *this;
    }

   /**
    * @brief This function empties out the tree, releasing the memory occupied by the nodes. root is set to nullptr.
    */

    void clear() noexcept{
        root.reset(nullptr);
    }

   /**
    * @brief Overloaded function that returns an iterator pointing to the leftmost node of the tree.
    * @return iterator pointing to the leftmost node.
    */

    iterator begin() noexcept {
        if(!root) return iterator{nullptr};
        node_type* temp=root.get();
        while(temp->left.get()) temp=temp->left.get();
        return iterator{temp};
        }

   /**
    * @brief Overloaded function that returns an iterator pointing to one node after the rightmost one.
    * @return iterator pointing to one node after the rightmost one.
    */

    iterator end() noexcept { return iterator{nullptr}; }

   /**
    * @brief Overloaded function that returns a const iterator pointing to the leftmost node of the tree.
    * @return const iterator pointing to the leftmost node.
    */

    const_iterator begin() const noexcept{
        if(!root) return const_iterator{nullptr};
        node_type* temp=root.get();
        while(temp->left.get()) temp=temp->left.get();
        return const_iterator{temp};
        }

   /**
    * @brief Overloaded function that returns a const iterator pointing to one node after the rightmost one.
    * @return const iterator pointing to one node after the rightmost one.
    */

    const_iterator end() const noexcept { return const_iterator{nullptr}; }

   /**
    * @brief This function returns a const iterator pointing to the leftmost node of the tree.
    * @return const iterator pointing to the leftmost node.
    */

    const_iterator cbegin() const noexcept {
        if(!root) return const_iterator{nullptr};
        node_type* temp=root.get();
        while(temp->left.get()) temp=temp->left.get();
        return const_iterator{temp};
        }

   /**
    * @brief This function returns a const iterator pointing to one node after the rightmost one.
    * @return const iterator pointing to one node after the rightmost one.
    */

    const_iterator cend() const noexcept { return const_iterator{nullptr}; }

   /**
    * @brief Overloaded function that inserts a new node with the given pair, calling _insert.
    * @tparam x const lvalue reference to the pair to be inserted in the tree.
    * @return std::pair<iterator,bool> returned by _insert.
    */

    std::pair<iterator, bool> insert(const pair_type& x){
        return _insert(x);
    }

   /**
    * @brief Overloaded function that inserts a new node with the given pair, calling _insert using std::move.
    * @tparam x rvalue reference to the pair to be inserted in the tree.
    * @return std::pair<iterator,bool> returned by _insert.
    */

    std::pair<iterator, bool> insert(pair_type&& x){
        return _insert(std::move(x));
    }

   /**
    * @brief This function inserts a new node both with a std::pair <key,value> and with a key and a value.
    * @tparam args a std::pair or key and value.
    * @return std::pair<iterator,bool> returned by _insert.
    */

    template<class... Args>
    std::pair<iterator, bool> emplace(Args&&... args ){
        return _insert<pair_type>({std::forward<Args>(args)...});
    }


   /**
    * @brief Overloaded function that searches for a node in the tree, given a key.
    * @tparam x const lvalue reference to the key to look for.
    * @return iterator pointing to the node containing the key or to nullptr if the key is not found.
    */

    iterator find(const key_type& x) {
        return iterator{_find(x)};
    }


   /**
    * @brief Overloaded function that searches for a node in the tree, given a key.
    * @tparam x const lvalue reference to the key to look for.
    * @return const iterator pointing to the node containing the key or to nullptr if the key is not found.
    */

    const_iterator find(const key_type& x) const{
        return const_iterator{_find(x)};
    }

   /**
    * @brief Friend operator that prints the tree in order (from left to right) using const iterators.
    * @param os output stream object.
    * @tparam x const lvalue reference to binary search tree.
    * @return std::ostream& output stream object.
    */

    friend std::ostream& operator<<(std::ostream& os, const bst& x) noexcept {
        for(const auto& i: x) {
            os<<i.first<<" "<<i.second<<std::endl;
        }
        return os;
    }

   /**
    * @brief Overloaded operator that looks for a key to return the corresponding value. If the key is not present in the tree, it inserts a node with that key and a
    * default value.
    * @tparam x const lvalue reference to key.
    * @return value_type& value mapped by the key.
    */

     value_type& operator[](const key_type& x){
        auto f=find(x);
        if(f!=end()) return (*f).second;
        auto p=_insert<pair_type>({x,value_type{}});
        return (*p.first).second;
     }

   /**
    * @brief Overloaded operator that looks for a key to return the corresponding value. If the key is not present in the tree, it inserts a node with that key and a
    * default value.
    * @tparam x rvalue reference to key.
    * @return value_type& value mapped by the key.
    */

    value_type& operator[](key_type&& x){
        auto f=find(std::move(x));
        if(f!=end()) return (*f).second;
        auto p=_insert<pair_type>({std::move(x),value_type{}});
        return (*p.first).second;
    }


   /**
    * @brief This function counts the number of nodes in the tree.
    * @return std::size_t number of nodes in the tree.
    */

    std::size_t size() const noexcept{
        size_t count=0;
        for(auto i=cbegin(); i!=cend(); ++i) ++count;
        return count;
    }


   /**
    * @brief This function stores in a vector the pairs key,value stored in nodes of the tree.
    * @return std::vector<std::pair<key_type,value_type>> vector containing the pairs stored in the nodes of the tree.
    */

    std::vector<std::pair<key_type,value_type>> vectorize() const {
        std::vector<std::pair<key_type,value_type>> v;
        v.reserve(size());
        for(const auto& i: *this) {
            v.emplace_back(i);
        }
        return v;
    }


   /**
    * @brief This function balances the tree by calling vectorize, reorder, clear and _insert. At first, it stores the nodes of the tree in a vector calling vectorize; then, the
    * vector is reordered calling reorder. Finally, after calling clear to empty out the tree, the pairs are reinserted calling _insert.
    */

    void balance() {
        #ifdef TEST
        if (!unbalanced()) return;
        #endif
        std::vector<std::pair<key_type,value_type>> v=vectorize();
        std::vector<std::pair<key_type,value_type>> temp;
        reorder(v, temp);
        clear();
        for(const auto& i : temp) _insert(i);
    }

   /**
    * @brief This function erases the node with the key given as input (if present) from the tree. At first, it calls _find to have a pointer to the node that has to be
    * erased; then, it calls leftmost in order to know where the possible left child of the node to erase has to be attached. There are three possible cases: the node to
    * erase is the root, it is a left child or it is a right child. In all these cases, the ownership of the node that has to be erased is released and two subcases can arise:
    * if the node that is being erased has a right child, it substitutes the parent and the possible left child is attached to the leftmost node of the right subtree, otherwise
    * the left child substitues the parent. Finally, the pointer to the node that is being erased is used to delete the node.
    * @tparam x const lvalue reference to key.
    */

    void erase(const key_type& x) {
        node_type* p{_find(x)};
        if(!p) return;
        auto l=leftmost(p);
        if(p==root.get()){
            root.release();
            if(p->right){
                p->right->parent=nullptr;
                root.reset(p->right.release());
                if(p->left){
                    p->left->parent=l;
                    l->left.reset(p->left.release());
                }
            }
            if(p->left){
                p->left->parent=nullptr;
                root.reset(p->left.release());
            }
        }
        else if(p->parent->left.get()==p){
            p->parent->left.release();
            if(p->right){
                p->right->parent=p->parent;
                p->parent->left.reset(p->right.release());
            }
            if(p->left){
                p->left->parent=l;
                l->left.reset(p->left.release());
            }
        }
        else{
            p->parent->right.release();
            if(p->left){
                p->left->parent=l;
                if(p->right) l->left.reset(p->left.release());
                else l->right.reset(p->left.release());
            }
            if(p->right){
                p->right->parent=p->parent;
                p->parent->right.reset(p->right.release());
            }
        }
        delete p;
    }

   /**
    * @brief This function checks if the tree is unbalanced by calling the function unbalanced_node of struct node.
    * @return bool true if the tree is unbalanced.
    */

    bool unbalanced() const noexcept{
        if(!root) return false;
        auto a=root.get()->unbalanced_node();
        if(a.first){
            std::cout<<"Unbalance on node "<<a.second->element.first<<std::endl;
            return true;
            }
        return false;
    }
};
#endif
