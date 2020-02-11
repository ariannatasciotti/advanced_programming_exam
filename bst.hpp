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
    using node_t = node<std::pair<key_type, value_type>>;
    using iterator = _iterator <node_type, typename node_type::value_type>;
    using const_iterator = _iterator<node_type, const typename node_type::value_type>;
    cmp_op op;
    std::unique_ptr<node_type> root;

    template<typename ot>
    std::pair<iterator, bool> _insert(ot&& x){
           if(!root){
               root=std::make_unique<node_type>(std::forward<ot>(x), nullptr);
               return std::make_pair(iterator{root.get()}, true);
           }
           node_type* temp=root.get();
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

    
    //FIND MIN
    
    node_type* findmin(node_type* node){
        if(!node->left.get()){
            return node;
        } else{
            return this->findmin(node->left.get());
        }
    }
    
    // LEFT MOST
    
    node_type* leftmost(node_type* node){
        if(!node->right) return node->parent;
        else return findmin(node->right.get());
    }


    public:
    explicit bst(cmp_op x): op{x}{}
    explicit bst(node_type* r): root{r}{};
    bst() noexcept=default;
    ~bst() noexcept=default;


    /* COPY constructor and overload of operator = for deep copy */
    bst(const bst& b): op{b.op}, root{(!b.root)? nullptr:std::make_unique<node_type>(*b.root)} {std::cout<<"Copy \n";}
    bst& operator=(const bst& b){
        this->clear();
        op=b.op;
        if(b.root) root=std::make_unique<node_type>(*b.root);
        return *this;
    }

    /* MOVE constructor and overload of operator = */

    bst(bst&& b) noexcept: op{std::move(b.op)}, root{std::move(b.root)} {//move op
        std::cout<<"Move \n";
    }

    bst& operator=(bst&& b) noexcept{
        root=std::move(b.root);
        op=std::move(b.op);
        return *this;
    }

    // CLEAR

    void clear() noexcept{
        root.reset(nullptr);
    }


    iterator begin() noexcept {
        if(!root) return iterator{nullptr};
        node_type* temp=root.get();
        while(temp->left.get()) temp=temp->left.get();
        return iterator{temp};
        }

    iterator end() noexcept { return iterator{nullptr}; } //CONTROLLARE NOEXCEPT

    const_iterator begin() const noexcept{
        if(!root) return const_iterator{nullptr};
        node_type* temp=root.get();
        while(temp->left.get()) temp=temp->left.get();
        return const_iterator{temp};
        }

    const_iterator end() const noexcept { return const_iterator{nullptr}; }

    const_iterator cbegin() const noexcept {
        if(!root) return const_iterator{nullptr};
        node_type* temp=root.get();
        while(temp->left.get()) temp=temp->left.get();
        return const_iterator{temp};
        }

    const_iterator cend() const noexcept { return const_iterator{nullptr}; }



    /* INSERT LVALUE */

    std::pair<iterator, bool> insert(const pair_type& x){
        std::cout<<"insert lvalue"<<std::endl;
        return _insert(x);
    }

    /* INSERT RVALUE*/

    std::pair<iterator, bool> insert(pair_type&& x){
        std::cout<<"insert rvalue"<<std::endl;
        return _insert(std::move(x));
    }

    // EMPLACE

    template<class... Args>
    std::pair<iterator, bool> emplace(Args&&... args ){
        return _insert<pair_type>({std::forward<Args>(args)...});
    }


    // ITERATOR FIND

    iterator find(const key_type& x) noexcept{
        node_type* temp=root.get();
        while(temp){
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

    const_iterator find(const key_type& x) const noexcept{
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

    // PUT TO OPERATOR

    friend std::ostream& operator<<(std::ostream& os, const bst& x) {
        for(const_iterator i=x.begin(); i!=x.end(); ++i) {
            os<<(*i).first<<" "<<(*i).second<<std::endl;
            //os<<"pippo ";
        }
        return os;
    }

    /* SUBSCRIPTING OPERATOR LVALUE */

     value_type& operator[](const key_type& x){
        auto f=find(x);
        if(f!=end()) return (*f).second;
        auto p=_insert<pair_type>({x,value_type{}});
        return (*p.first).second;
     }

    /* SUBSCRIPTING OPERATOR RVALUE */

    value_type& operator[](key_type&& x){
        auto f=find(std::move(x));
        if(f!=end()) return (*f).second;
        auto p=_insert<pair_type>({std::move(x),value_type{}});
        return (*p.first).second;
    }

        
    // SIZE
               
    std::size_t size() const{
        size_t count=0;
        for(auto i=cbegin(); i!=cend(); ++i) ++count;
        return count;
    }
        

    // VECTORIZE

    std::vector<std::pair<key_type,value_type>> vectorize() const {
        std::vector<std::pair<key_type,value_type>> v;
        v.reserve(size());
        for(auto i=this->begin(); i!=this->end(); ++i) {
            v.emplace_back(*i);
        }
        return v;
    }

        
    // BALANCE

    void balance() {
        if (!unbalanced()) return;
        std::vector<std::pair<key_type,value_type>> v=this->vectorize();
        std::vector<std::pair<key_type,value_type>> temp;
        reorder(v, temp);
        this->clear();
        for(auto i : temp) this->insert(i);
    }

    // ERASE
        
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
            else if(p->left){
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
        
       /*
            if(!p->left && !p->right){
            if(p==root.get()) root.release();
            else if(p->parent->left.get()==p) p->parent->left.release();
            else p->parent->right.release();
        }

        else if(p->left && !p->right){
            p->left->parent=p->parent;
            if(p==root.get()) root=std::move(p->left);
            else if(p->parent->left.get()==p) p->parent->left=std::move(p->left);
            else p->parent->right=std::move(p->left);
        }
        else if(!p->left && p->right){
            p->right->parent=p->parent;
            if(p==root.get()) root=std::move(p->right);
            else if(p->parent->left.get()==p) p->parent->left=std::move(p->right);
            else p->parent->right=std::move(p->right);
        }

        else{
            node_type* min{this->findmin(p->right.get())};
            p->left->parent=min;
            min->left=std::move(p->left);
            p->right->parent=p->parent;
            if(p==root.get()) root=std::move(p->right);
            else if(p->parent->left.get()==p) p->parent->left=std::move(p->right);
            else p->parent->right=std::move(p->right);

        }*/


    bool unbalanced() const noexcept{
        auto a=root.get()->unbalanced();
        if(a.first){
            std::cout<<"Unbalance on node "<<a.second->element.first<<std::endl;
            return true;
            }
        return false;
    }

};
#endif
