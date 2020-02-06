#include <iostream>
#include <utility> //these two includes are not necessary (already included in bst.hpp) but a user would surely include them
#include "bst.hpp"

struct foo{
    foo(){std::cout<<"Default \n";}
    foo(const foo&){std::cout<<"Copy \n";}
    foo(foo&&){std::cout<<"Move \n";}
};

#include <map>
int main(){
    //std::map<int,foo> albero;
    bst<int,int> albero;
    //const int c=4;
    //albero.insert(a);
    albero.emplace(34,20);
    //albero.insert({35,{}});
    //albero.insert(std::make_pair<const int,foo>(35,{}));
    //std::pair<const int,foo> a=std::make_pair<const int,foo>(35,{});
    //albero.insert(a);
    //const int a=5;
    //albero[a];
    //std::cout<<a;
    //std::cout << a.first << std::endl;
    albero.insert(std::make_pair(3,10));
    albero.insert(std::make_pair(1,10));
    bst<int,int> pippo=std::move(albero);
    //bst<int,int> pippo{albero};
    //albero.insert(std::make_pair(10,10));
    //albero.emplace(a);
    //albero.emplace(std::make_pair(33,10));
    //albero.insert(std::make_pair(6,10));
    //albero.insert(std::make_pair(50,10));
    //albero.insert(std::make_pair(9,10));
    //albero.insert(std::make_pair(5,10));
    //albero.print();
    //bst<int, int> pippo=std::move(albero);
    //std::cout<<std::endl<<pippo;
    //pippo.print();
    //pippo.balance();
    std::cout<<albero;
    (*(pippo.find(3))).second=4;
    //std::cout<<"\n \n";
    //std::cout<<"pippo:"<<std::endl<<pippo;
    //pippo.print();
    //std::cout<<(*pippo.find(5)).first;
    //std::cout<<" \n \n \n prova della erase: \n \n";
    //pippo.erase(33);
    //pippo.clear();
    std::cout<<"pippo:"<<std::endl<<pippo;
    return 0;
}
