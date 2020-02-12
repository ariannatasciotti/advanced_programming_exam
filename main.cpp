#include <iostream>
#include <utility> //these two includes are not strictly necessary (already included in bst.hpp) but a user would surely include them
#include "bst.hpp"
#include <map>

struct foo{
    foo(){std::cout<<"Default \n";}
    foo(const foo&){std::cout<<"Copy \n";}
    foo(foo&&){std::cout<<"Move \n";}
};

int main(){
    bst<int,int> albero;
    //PROVE DI EMPLACE E INSERT
    albero.emplace(12,20);
    albero.insert({35,12});
    albero.insert(std::make_pair(40,10));
    albero.insert(std::make_pair(33,10));
    albero.insert(std::make_pair(33,15)); //shouldn't insert
    albero.insert(std::make_pair(15,10));
    albero.insert(std::make_pair(50,10));
    albero.insert(std::make_pair(40,10)); //shouldn't insert
    albero.insert(std::make_pair(3,10));
    albero.emplace(9,12);
    albero.emplace(std::make_pair(13,10));
    albero.insert(std::make_pair(17,10));
    albero.insert(std::make_pair(2,10));
    albero.insert(std::make_pair(1,10));
    albero.insert(std::make_pair(19,10));
    albero.insert(std::make_pair(21,10));
    albero.insert(std::make_pair(4,10));
    albero.insert(std::make_pair(5,10));
    //PROVA DI PUT TO
    std::cout<<"albero prima di erase:"<<std::endl<<albero<<std::endl;
    //PROVA DI ERASE
    albero.erase(12); //root
    albero.erase(40); //right child
    albero.erase(15); //left child
    std::cout<<"albero dopo erase:"<<std::endl<<albero<<std::endl;
    //PROVA DI BALANCE
    albero.balance();
    albero.unbalanced();
    //PROVA COPY
    bst<int,int> albero2=albero;
    std::cout<<"albero1: \n"<<albero<<"\n albero2: \n"<<albero2<<std::endl;
    //PROVA MOVE
    bst<int,int> albero3=std::move(albero2);
    std::cout<<"albero2: \n"<<albero2<<"\n albero3: \n"<<albero3<<std::endl;
    //PROVA SUBSCRIPTING OP
    albero3[4]=19;
    std::cout<<albero3[4];
    //PROVA CLEAR E VERIFICA NON SHALLOWNESS DELLA COPY
    albero3.clear();
    std::cout<<"albero3: \n"<<albero2<<"\n albero: \n"<<albero<<std::endl;
    std::cout<<"provo il non const \n";
    (*albero.begin()).second=4;
    std::cout<<albero;
    albero.find(40);
    return 0;
}
