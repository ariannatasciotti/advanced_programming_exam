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
    bst<int,foo> albero;
    const int b=3;
    const int c=4;
    std::pair<const int, foo> a=std::make_pair<const int, foo>(10,{});
    albero.insert(a);
    albero[2];
 /*   auto a = std::make_pair(37,20);
    //albero.insert(std::make_pair<const int,foo>(35,{}));
    albero.emplace(35,20);
    //std::pair<int,foo> a{35,{}}; //=std::make_pair(35,{});
    //albero.insert(a);
    //std::cout << a.first << std::endl;
    albero.insert(std::make_pair(3,10));
    albero.insert(std::make_pair(1,10));
    /*albero.insert(std::make_pair(10,10));
    albero.emplace(a);
    albero.emplace(std::make_pair(33,10));
    albero.insert(std::make_pair(6,10));
    albero.insert(std::make_pair(50,10));
    albero.insert(std::make_pair(9,10));
    albero.insert(std::make_pair(5,10));
   // albero.print();
    bst<int, int> pippo=std::move(albero);
    std::cout<<std::endl<<pippo;
    pippo.print();
    //pippo.balance();
    //std::cout<<albero;
    std::cout<<"\n \n";
    std::cout<<"pippo:"<<std::endl<<pippo;
    pippo.print();
    //std::cout<<(*pippo.find(5)).first;
    std::cout<<" \n \n \n prova della erase: \n \n";
    //pippo.erase(33);
    //pippo.clear();
    std::cout<<"pippo:"<<std::endl<<pippo;
*/
    return 0;
}
