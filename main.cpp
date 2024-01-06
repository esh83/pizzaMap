#include <iostream>
#include "kdtree.h"
#include "hashtable.h"
#include "schemma.h"


int main()
{
//    KdTree tree;
// tree.insert(10,10);
//    tree.insert(11,1);
//    tree.insert(4,3);
//    tree.insert(14,2);
//    tree.insert(12,13);
//    tree.insert(6,17);
//    Node * temp = tree.nearestNeighbor(5,5);
//    std::cout << temp->point.x << " "<< temp->point.y;
//    std::cout << "\n\n\n ......\n";
//    for( auto pt :tree.searchArea(Circle(1,1,5))){
//        std::cout << pt->point.x << " " <<pt->point.y << std::endl;
//    }
    std::cout << "\n\n";

HashTable<Shop> ht;
    Shop s1;
s1.name = "shop1";
    Shop s2;
    s1.name = "shop2";
    ht.add("a" , s1);
    ht.add("b" , s2);
    ht.add("c" , s1);
    ht.add("d" , s1);
    ht.add("e" , s1);
    ht.add("r" , s1);
    ht.add("f" , s1);
    ht.add("g" , s1);
    ht.add("h" , s1);
    ht.add("i" , s1);
    ht.add("n" , s1);


ht.printSelf();


    return 0;
}
