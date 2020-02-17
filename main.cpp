#include <iostream>
#include <utility> //these two includes are not strictly necessary (already included in bst.hpp) but a user would surely include them
#include "bst.hpp"
#include <exception>
#include <map>

template <typename t>
bool compare(const t& a, const t& b) noexcept{  //std::less operator() but defined by us
    return a<b;
}

template <typename t>
class function_object{
    t parameter;
    public:
    function_object() noexcept: parameter{}{};
    explicit function_object(const t& p) noexcept: parameter{p}{};
    //basically std::less operator(), throwing if one of the items to compare is larger than a given parameter
    bool operator()(const t& a, const t& b) const {
        //just a test to verify how a comparison operator could throw
        if(a>parameter || b>parameter) throw std::invalid_argument{"Comparing an item larger than "+std::to_string(parameter)};
        return a<b;
    }
};

int main(){
    try{
        function_object<int> fun(1000000);
        bst<int,int,decltype(fun)> tree(fun); //building tree with fun as comparison operator
        
        /* ALTERNATIVES TO CONSTRUCT A TREE
        bst<int,int, decltype(fun)> tree(71); //this works if function_object's constructor is not marked explicit
        bst<int,int, decltype(fun)> tree(fun); //otherwise you have to pass a functional_object
        bst<int,int> tree; //default constructor for tree (with std::less)
        bst<int,int, decltype(compare<int>)(*)> tree(compare<int>); //constructing with a pointer to function
        */
        
        //TESTING OF EMPLACE AND INSERT
        tree.emplace(12,20);
        tree.insert({35,12});
        tree.insert(std::make_pair(40,10));
        tree.insert({33,10});
        tree.insert({33,15}); //shouldn't insert
        tree.insert({15,11});
        tree.insert({50,44});
        tree.emplace(40,9); //shouldn't insert
        tree.emplace(3,10);
        tree.emplace(9,12);
        tree.emplace(std::make_pair(13,7));
        tree.insert({17,30});
        tree.insert({2,4});
        tree.insert(std::make_pair(1,12));
        tree.insert({19,3});
        tree.emplace(21,71);
        tree.emplace(4,63);
        tree.emplace(5,26);
        //PUT TO OPERATOR TO PRINT TREE
        std::cout<<"Tree before erasing elements:"<<std::endl<<tree<<std::endl;
        //TESTING ERASE FUNCTION ON DIFFERENT KINDS OF NODES
        std::cout<<"Now erasing 12, 40, 15. \n";
        tree.erase(12); //root
        tree.erase(40); //right child
        tree.erase(15); //left child
        std::cout<<"Tree after erase:"<<std::endl<<tree<<std::endl;
        //TESTING BALANCE
        std::cout<<"Balancing tree \n";
        tree.balance();
        if(!tree.unbalanced()) std::cout<<"The tree is now balanced \n";
        //COPY CONSTRUCTOR
        std::cout<<"Constructing tree2 as copy of tree \n";
        auto tree2=tree;
        std::cout<<"Tree: \n"<<tree<<"\nTree2: \n"<<tree2<<std::endl;
        //TESTING CLEAR AND NON-SHALLOWNESS OF COPY
        std::cout<<"Clearing tree \n";
        tree.clear();
        //TREE IS CLEARED, TREE2 SHOULD STAY UNMODIFIED
        std::cout<<"Tree2: \n"<<tree2<<"\nTree: \n"<<tree<<std::endl;
        //MOVE CONSTRUCTOR
        std::cout<<"Constructing tree3 as move of tree2 \n";
        auto tree3=std::move(tree2);
        std::cout<<"Tree2: \n"<<tree2<<"\nTree3: \n"<<tree3<<std::endl;
        //TESTING FIND
        std::cout<<"Find: value for key 5: "<<(*tree3.find(5)).second<<std::endl;;
        //TESTING OF SUBSCRIPTING OPERATOR
        std::cout<<"Modifying value for key 4 to 19 via subscripting op \n";
        tree3[4]=19;
        std::cout<<"Subscripting op: value for key 4: "<<tree3[4]<<std::endl;
        //COPYING TREE3 IN A CONST TREE TO TEST CONST FIND
        const auto tree4=(*const_cast<decltype(&tree3)>(&tree3));
        std::cout<<"Calling const find to access value for key 21: "<<(*tree4.find(21)).second<<std::endl;
    }
    catch(const std::exception& e){
        std::cerr<<e.what()<<std::endl;
        return 1;
    }
    catch (...){
        std::cerr<<"Unknown exception. Aborting.\n";
        return 2;
    }
}
