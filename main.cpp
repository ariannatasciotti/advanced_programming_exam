#include <iostream>
#include <utility> //these two includes are not strictly necessary (already included in bst.hpp) but a user would surely include them
#include "bst.hpp"
#include <exception>
#include <map>

struct foo{ //struct used for testing
    foo(){std::cout<<"Default \n";}
    foo(const foo&){std::cout<<"Copy \n";}
    foo(foo&&){std::cout<<"Move \n";}
};

template <typename t>
bool compare(const t& a, const t& b) noexcept{  //std::less operator() but defined by us
    return a<b;
}

template <typename t>
class function_object{
    int parameter;
    public:
    explicit function_object(const int p=0) noexcept: parameter{p}{};
    bool operator()(const t& a, const t& b) const { //basically std::less operator(), with a parameter printed every time
        if(a>parameter || b>parameter) throw std::string{"comparing an item larger than "+std::to_string(parameter)};
        return a>b;
    }
};

int main(){
    try{
        function_object<int> fun(13);
        bst<int,int, decltype(fun)> tree(fun); //default value for the parameter of functional object
        /*bst<int,int, decltype(compare<int>)(*)> tree(compare<int>);
        bst<int,int, decltype(fun)> tree(71); //this works if function_object's constructor is not marked explicit
        bst<int,int, decltype(fun)> tree(fun);*/ //otherwise you have to pass a functional_object
        //bst<int,int> tree;
        //TESTING OF EMPLACE AND INSERT
        tree.emplace(12,20);
        tree.insert({35,12});
        tree.insert(std::make_pair(40,10));
        tree.insert(std::make_pair(33,10));
        tree.insert(std::make_pair(33,15)); //shouldn't insert
        tree.insert(std::make_pair(15,11));
        tree.insert(std::make_pair(50,44));
        tree.insert(std::make_pair(40,9)); //shouldn't insert
        tree.insert(std::make_pair(3,10));
        tree.emplace(9,12);
        tree.emplace(std::make_pair(13,7));
        tree.insert(std::make_pair(17,30));
        tree.insert(std::make_pair(2,4));
        tree.insert(std::make_pair(1,12));
        tree.insert(std::make_pair(19,3));
        tree.insert(std::make_pair(21,71));
        tree.insert(std::make_pair(4,63));
        tree.insert(std::make_pair(5,26));
        //with the last modifications the code is robust to self-assignment
        tree=tree;
        //PUT TO OPERATOR TO PRINT TREE
        std::cout<<"tree before erasing elements:"<<std::endl<<tree<<std::endl;
        //TESTING ERASE FUNCTION ON DIFFERENT KINDS OF NODES
        tree.erase(12); //root
        tree.erase(40); //right child
        tree.erase(15); //left child
        std::cout<<"tree after erase:"<<std::endl<<tree<<std::endl;
        //TESTING BALANCE
        tree.balance();
        if(!tree.unbalanced()) std::cout<<"The tree is now balanced \n";
        //COPY CONSTRUCTOR
        std::cout<<"Constructing tree2 as copy of tree \n";
        auto tree2=tree;
        std::cout<<"tree: \n"<<tree<<"\ntree2: \n"<<tree2<<std::endl;
        //TESTING CLEAR AND NON-SHALLOWNESS OF COPY
        std::cout<<"Clearing tree \n";
        tree.clear(); //TREE IS CLEARED, TREE2 SHOULD STAY UNMODIFIED
        tree.balance();
        std::cout<<"tree2: \n"<<tree2<<"\ntree: \n"<<tree<<std::endl;
        //MOVE CONSTRUCTOR
        std::cout<<"Constructing tree3 as move of tree2 \n";
        auto tree3=std::move(tree2);
        std::cout<<"tree2: \n"<<tree2<<"\ntree3: \n"<<tree3<<std::endl;
        //TESTING FIND
        std::cout<<"Value for key 5: "<<(*tree3.find(5)).second<<std::endl;
        //TESTING OF SUBSCRIPTING OPERATOR
        tree3[4]=19;
        std::cout<<"Value for key 4: "<<tree3[4]<<std::endl;
    }
    catch(const std::string& s){
        std::cerr<<s<<std::endl;
        return 1;
    }
    catch(const std::exception& e){
        std::cerr<<e.what()<<std::endl;
        return 2;
    }
    catch (...){
        std::cerr<<"Unknown exception. Aborting.\n";
        return 3;
    }
}
