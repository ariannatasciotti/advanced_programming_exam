#ifndef _bst_hpp
#define _bst_hpp

#include "node.hpp" //useless (included by iterator header), here for clarity
#include "iterator.hpp"
#include <vector>

template <typename T>
void reorder(std::vector<T>& v, std::vector<T>& median){
    auto value=v[v.size()/2];
    median.push_back(value);
    v.erase(v.begin()+v.size()/2);
    if(v.size()>1) {
        std::vector<T> right_s(v.end()-v.size()/2, v.end());
        reorder(right_s,median);
        std::vector<T> left_s(v.begin(), v.begin()+v.size()/2+v.size()%2);
        reorder(left_s,median);
    }
    if(v.size()==1) median.push_back(v[0]);
}

template <typename key_type, typename value_type, typename cmp_op=std::less<key_type>>
class bst{
    using pair_type = std::pair<const key_type, value_type>;
    using node_type = node<pair_type>;
    using iterator = _iterator <node_type, typename node_type::value_type>;
    using const_iterator = _iterator<node_type, const typename node_type::value_type>;
    cmp_op op;
    std::unique_ptr<node_type> root;
    public:
    template<typename ot>
    std::pair<iterator, bool> _insert(ot&& x){
           std::cout<<"In _insert \n";
           if(root==nullptr){
               root=std::make_unique<node_type>(std::forward<ot>(x), nullptr);
               //root.reset(new node_type{x,nullptr});
               return std::make_pair(iterator{root.get()}, true); // root non è unique
           }
           node_type* temp=root.get(); // root non è unique
           while((op(temp->element.first,x.first) && temp->right != nullptr) || (op(x.first,temp->element.first) && temp->left != nullptr)){
               if(op(temp->element.first,x.first)) temp=temp->right.get();
               else temp=temp->left.get();
           }
                 if(!(op(temp->element.first,x.first) || op(x.first,temp->element.first)))
                    return std::make_pair(iterator{temp}, false);
                 else{
                 if(op(temp->element.first,x.first)){
                   temp->right=std::make_unique<node_type>(std::forward<ot>(x), temp);
                   return std::make_pair(iterator{temp->right.get()}, true);

                   }
                 else {
                   temp->left=std::make_unique<node_type>(std::forward<ot>(x), temp);
                   return std::make_pair(iterator{temp->left.get()}, true);

                   }
                 }
    }

    // FIND PUNTATORE
    node_type* _find(const key_type& x){
        node_type* temp=root.get();
        while(temp!=nullptr){
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

    //public:
    bst(cmp_op x): op{x}{}
    bst(node_type* r): root{r}{};
    bst()=default;
    ~bst() noexcept = default;


    /* COPY constructor and overload of operator = for deep copy */
    bst(const bst& b): op{b.op}, root{(b.root==nullptr)? nullptr:std::make_unique<node_type>(*b.root)} {}
    bst& operator=(const bst& b){
        this->clear();
        op=b.op;
        if(b.root!=nullptr) root=std::make_unique<node_type>(*b.root);
        return *this;
    }

    /* MOVE constructor and overload of operator = */

    bst(bst&& b): op{b.op}, root{nullptr} {//move op
        root.swap(b.root);
    }

    bst& operator=(bst&& b){
        this->clear();
        this->swap(b.root);
        //this->swap(b.op);
        op=std::move(b.op);
        //root=std::move(b.root);
        return *this;
    }
    /* per ora non necessaria
    std::size_t size(){
        size_t count=0;
        for(const_iterator i=cbegin(); i!=cend(); ++i) ++count;
        return count;
    }*/

    // CLEAR

    void clear(){
        root.reset(nullptr);
    }


    iterator begin() noexcept {
        if(root==nullptr) return iterator{nullptr};
        node_type* temp=root.get();
        while(temp->left.get() != nullptr) temp=temp->left.get();
        return iterator{temp};
        }
    iterator end() noexcept { return iterator{nullptr}; } //CONTROLLARE NOEXCEPT

    const_iterator begin() const noexcept{
        if(root==nullptr) return const_iterator{nullptr};
        node_type* temp=root.get();
        while(temp->left.get() != nullptr) temp=temp->left.get();
        return const_iterator{temp};
        }
    const_iterator end() const noexcept { return const_iterator{nullptr}; }

    const_iterator cbegin() const noexcept {
        if(root==nullptr) return const_iterator{nullptr};
        node_type* temp=root.get();
        while(temp->left.get() != nullptr) temp=temp->left.get();
        return const_iterator{temp};
        }
    const_iterator cend() const noexcept { return const_iterator{nullptr}; }



    /* INSERT LVALUE */

    std::pair<iterator, bool> insert(const pair_type& x){
        std::cout<<"In lvalue insert \n";
        return _insert(x);
    }

    /* INSERT RVALUE*/

    std::pair<iterator, bool> insert(pair_type&& x){
        std::cout<<"In rvalue insert \n";
        return _insert(std::move(x));
    }

    // EMPLACE

    template<class... Args>
    std::pair<iterator, bool> emplace(Args&&... args ){
        return _insert<pair_type>({std::forward<Args>(args)...});
    }


    // ITERATOR FIND

    iterator find(const key_type& x){
        node_type* temp=root.get();
        while(temp!=nullptr){
            key_type key=temp->element.first;
            if(!(op(key, x) || op(x, key))){
                return iterator{temp};
            }
            else if(op(key, x)){
                temp=temp->right.get();
            }
            else{
                temp=temp->left.get();
            }
        }
        return this->end();
    }


    // CONST_ITERATOR FIND

    const_iterator find(const key_type& x) const{
        node_type* temp=root.get();
        while(temp!=nullptr){
            key_type key=temp->element.first;
            if(!(op(key, x) || op(x, key))){
                return const_iterator{temp};
            }
            else if(op(key, x)){
                temp=temp->right.get();
            }
            else{
                temp=temp->left.get();
            }
        }
        return this->cend();
    }

    /* SUBSCRIPTING OPERATOR LVALUE */

     value_type& operator[](const key_type& x){
         std::cout<<"lvalue subscript";
         if(find(x)!=end()) return (*find(x)).second;
         else {
             _insert<pair_type>({x,value_type{}});
             return (*find(x)).second;
         }
     }

    /* SUBSCRIPTING OPERATOR RVALUE */

    value_type& operator[](key_type&& x){
        std::cout<<"rvalue subscript";
        if(find(x)!=end()) return (*find(x)).second;
        else {
            _insert<pair_type>({x,value_type{}});
            return (*find(x)).second;
        }
    }

    // PUT TO OPERATOR

    friend std::ostream& operator<<(std::ostream& os, const bst& x) {
        for(const_iterator i=x.begin(); i!=x.end(); ++i) {
            os<<(*i).first<<" "<<(*i).second<<std::endl;
            //os<<"pippo ";
        }
        return os;
    }

    /* VECTORIZE*/

    std::vector<std::pair<key_type,value_type>> vectorize() const {
        std::vector<std::pair<key_type,value_type>> v;
        for(const_iterator i=this->begin(); i!=this->end(); ++i) {
            v.push_back(*i);
        }
        return v;
    }

    /* BALANCE */

    void balance() {
        std::vector<std::pair<key_type,value_type>> v=this->vectorize();
        std::vector<std::pair<key_type,value_type>> temp;
        reorder(v, temp);
        this->clear();
        for(auto i : temp) this->insert(i);
    }

    void print(){
        if(root) std::cout<<root->element.first<<std::endl;
        if(root->right) std::cout<<root->right->element.first<<std::endl;
        if(root->left) std::cout<<root->left->element.first<<std::endl;
    }

    void erase(const key_type& x){
        node_type* p{_find(x)};      // è un problema se p non è const e quindi potrebbe modificare l'albero?
        if(p==nullptr) return;
        bst<key_type, value_type, cmp_op> temp(p);
        if(temp.root.get()==root.get()) root.release();
        else if(temp.root.get()->parent->left.get()==temp.root.get()) temp.root.get()->parent->left.release();
        else temp.root.get()->parent->right.release();
        temp.root->parent=nullptr;
        std::vector<std::pair<key_type,value_type>> v=temp.vectorize();
        for(auto i=v.begin(); i!=v.end(); ++i) if(op((*i).first, x) || op(x, (*i).first)) this->insert(*i);
    }

};
#endif
