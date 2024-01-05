#include <iostream>
#include "kdtree.h"


int main()
{
    KdTree tree;
 tree.insert(10,10);
    tree.insert(11,1);
    tree.insert(4,3);
    tree.insert(14,2);
    tree.insert(12,13);
    tree.insert(6,17);
    Node * temp = tree.nearestNeighbor(5,5);
    std::cout << temp->point.x << " "<< temp->point.y;

    return 0;
}
