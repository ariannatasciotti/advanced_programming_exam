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
    //albero.emplace(12,20);
    albero.insert({35,12});
    //albero.insert(std::make_pair(40,10));
    //albero.insert(std::make_pair(33,10));
    //albero.insert(std::make_pair<const int,foo>(35,{}));
    //std::pair<const int,foo> a=std::make_pair<const int,foo>(35,{});
    //albero.insert(a);
    //const int a=5;
    //albero[a];
    //std::cout<<a;
    //std::cout << a.first << std::endl;
    albero.insert(std::make_pair(33,10));
    albero.insert(std::make_pair(15,10));
    //bst<int,int> pippo=std::move(albero);
    //bst<int,int> pippo{albero};
        albero.insert(std::make_pair(50,10));
    albero.insert(std::make_pair(40,10));
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
    std::cout<<"albero prima di erase:"<<std::endl<<albero<<std::endl;

    //albero.print();
    //bst<int, int> pippo=std::move(albero);/*
    //std::cout<<std::endl<<pippo;
    //pippo.print();
    //albero.unbalanced();
    //pippo.balance();
    albero.erase(1);
    std::cout<<"albero dopo erase:"<<std::endl<<albero<<std::endl;
    /*std::cout<<"albero dopo erase:"<<std::endl<<albero<<std::endl;
    bst<int,int> pippo=std::move(albero);
    std::cout<<"pippo dopo la move:"<<pippo<<std::endl;
    (*(pippo.find(3))).second=4;
    pippo.balance();
    if(!pippo.unbalanced()) std::cout<<pippo[35];
    //pippo.unbalanced();
    //std::cout<<"\n \n";*/
    //std::cout<<"pippo:"<<std::endl<<pippo;
    //pippo.print();
    //std::cout<<(*pippo.find(5)).first;
    //std::cout<<" \n \n \n prova della erase: \n \n";
    //pippo.erase(35);
    //std::cout<<"pippo dopo la balance:"<<std::endl<<pippo;
    //pippo.clear();
    return 0;
}
