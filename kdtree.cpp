#include "kdtree.h"
#include <iostream>

KdTree::KdTree()
{
    this->root = nullptr;
}

KdTree::~KdTree()
{
    clear();
}



void KdTree::insert(int x, int y)
{
    Point p{x,y};
    this->root = insertRec(this->root,p,0);
    //std::cout << "new node inserted : ( " << p.x << " , " << p.y << " )" << std::endl;
}



void KdTree::remove(int x, int y)
{
    Point p{x,y};
    this->root = removeRec(this->root,p,0);
    //std::cout << "node removed : ( " << p.x << " , " << p.y << " )" << std::endl;
}

Node *KdTree::findMin(bool inXaxis)
{
    return  findMinRec(this->root,inXaxis , 0);
}

Node *KdTree::search(int x, int y)
{
    Point p{x,y};
    return searchRec(this->root,p,0);
}

void KdTree::inorder()
{
    inorderRec(this->root);
}

void KdTree::clear()
{
    clearRec(this->root);
}

Node* KdTree::insertRec(Node *root, const Point &p , unsigned int depth)
{
    //depth starting from 0 and even depths 0,2,4,... are splitted using X axis , others using Y

    if(root == nullptr) return newNode(p);

    bool splitByX = depth %2 ==0;
    if(splitByX){
        if(p.x > root->point.x)
            root->right = insertRec(root->right , p , depth +1);
        else
            root->left = insertRec(root->left , p, depth +1);
    }
    else {
        if(p.y > root->point.y)
            root->right = insertRec(root->right , p , depth +1);
        else
            root->left = insertRec(root->left , p, depth +1);
    }
    return root;
}

Node *KdTree::removeRec(Node *root, const Point &p, unsigned int depth)
{

    if(!root) return nullptr;
    bool splitByX = depth %2 ==0;

    if(p.x == root->point.x && p.y == root->point.y){
        //point to be deleted founded
        if (root->right)
        {
            Node *min = findMinRec(root->right, splitByX , depth+1);
            // Copy the minimum to root
            root->point.x = min->point.x;
            root->point.y = min->point.y;

            root->right = removeRec(root->right, min->point, depth+1);
        }
        else if (root->left)
        {
            Node *min = findMinRec(root->left, splitByX,depth+1);
            root->point.x = min->point.x;
            root->point.y = min->point.y;
            root->right = removeRec(root->left, min->point, depth+1);
            root->left = nullptr;
        }
        else // If node to be deleted is leaf node
        {
            delete root;
            return nullptr;
        }
        return root;
    }
    if(splitByX){
        if (p.x < root->point.x)
            root->left = removeRec(root->left, p, depth+1);
        else
            root->right = removeRec(root->right, p, depth+1);
        return root;
    }else{
        if (p.y < root->point.y)
            root->left = removeRec(root->left, p, depth+1);
        else
            root->right = removeRec(root->right, p, depth+1);
        return root;
    }

}

Node *KdTree::findMinRec(Node *root, bool inXaxis, unsigned int depth)
{
    if(!root) return nullptr;
    bool splitByX = depth %2 ==0;
    if(splitByX == inXaxis){
        if(!root->left) return root;
        return findMinRec(root->left , inXaxis , depth+1);
    }else{
        Node * minLeft = findMinRec(root->left , inXaxis,depth+1);
        Node * minRight = findMinRec(root->right , inXaxis,depth+1);
        Node * currentMin = root;
        if(inXaxis){
            if(minLeft && minLeft->point.x < currentMin->point.x)
                currentMin = minLeft;
            if(minRight && minRight->point.x < currentMin->point.x)
                currentMin = minRight;
        }else{
            if(minLeft&& minLeft->point.y < currentMin->point.y)
                currentMin = minLeft;
            if(minRight && minRight->point.y < currentMin->point.y)
                currentMin = minRight;
        }
        return currentMin;
    }
}

Node *KdTree::searchRec(Node *root, const Point &p, unsigned int depth)
{
    if(!root) return nullptr;
    if(root->point.x == p.x && root->point.y == p.y) return root;
    bool splitByX = depth % 2 ==0;
    if(splitByX){
        if(p.x > root->point.x)
            return searchRec(root->right,p,depth+1);
        else
            return searchRec(root->left,p,depth+1);
    }else{
        if(p.y > root->point.y)
            return searchRec(root->right,p,depth+1);
        else
            return searchRec(root->left,p,depth+1);
    }
}

void KdTree::inorderRec(Node *root)
{
    if(root){
        inorderRec(root->left);
        std::cout << "( " << root->point.x << " , " << root->point.y << " )" << std::endl;
        inorderRec(root->right);
    }
}

void KdTree::clearRec(Node *root)
{
    if(root){
        clearRec(root->left);
        clearRec(root->right);
        delete root;
    }
}

Node *KdTree::newNode(const Point &p)
{
    return new Node(p);

}


