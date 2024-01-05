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
    tree.remove(10,10);
    tree.remove(11,1);

    tree.inorder();
    return 0;
}
