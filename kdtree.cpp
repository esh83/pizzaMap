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



void KdTree::insert(int x, int y  ,const std::string& shopName)
{
    Point p{x,y};
    this->root = insertRec(this->root,p , shopName,0);
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

Node *KdTree::nearestNeighbor(int x, int y)
{
    Point p{x,y};
    return nearestNeighborRec(this->root,p,0);
}

std::vector<Node *> KdTree::searchArea(const Rectangle &area)
{
    std::vector<Node *> pts;
    searchAreaRec(this->root,area,pts,0);
    return pts;
}

std::vector<Node *> KdTree::searchArea(const Circle &area)
{
    std::vector<Node *> pts;
    searchAreaRec(this->root,area,pts,0);
    return pts;
}

void KdTree::inorder()
{
    inorderRec(this->root);
}

void KdTree::clear()
{
    clearRec(this->root);
}

Node* KdTree::insertRec(Node *root, const Point &p ,const std::string& shopN, unsigned int depth)
{
    //depth starting from 0 and even depths 0,2,4,... are splitted using X axis , others using Y

    if(root == nullptr) return newNode(p , shopN);

    bool splitByX = depth %2 ==0;
    if(splitByX){
        if(p.x > root->point.x)
            root->right = insertRec(root->right , p ,shopN , depth +1);
        else
            root->left = insertRec(root->left , p,shopN, depth +1);
    }
    else {
        if(p.y > root->point.y)
            root->right = insertRec(root->right , p ,shopN, depth +1);
        else
            root->left = insertRec(root->left , p,shopN, depth +1);
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

Node * KdTree::nearestNeighborRec(Node *root, const Point &queryPoint, unsigned int depth)
{
    //query point exist in the tree
    if(queryPoint.x == root->point.x && queryPoint.y == root->point.y) return root;
    //reaching a leaf node
    if(!root->right && !root->left) return root;

    bool splitByX = depth % 2 ==0;
    Node *nearestNode = nullptr;
    bool recursedLeft = false;
    //recurse down to a leaf node
    if(splitByX){
        if(queryPoint.x < root->point.x) {
            if(root->left){
                nearestNode = nearestNeighborRec(root->left,queryPoint,depth+1);
                recursedLeft = true;
            }else{
                 nearestNode = nearestNeighborRec(root->right,queryPoint,depth+1);
            }

        }else {
            if(root->right){
                 nearestNode = nearestNeighborRec(root->right,queryPoint,depth+1);
            }else{
                 nearestNode = nearestNeighborRec(root->left,queryPoint,depth+1);
                 recursedLeft = true;
            }


        }

    }else{

        if(queryPoint.y < root->point.y) {
            if(root->left){
                 nearestNode = nearestNeighborRec(root->left,queryPoint,depth+1);
                 recursedLeft = true;
            }else{
                 nearestNode = nearestNeighborRec(root->right,queryPoint,depth+1);
            }

        }else {
            if(root->right){
                 nearestNode = nearestNeighborRec(root->right,queryPoint,depth+1);
            }else{
                 nearestNode = nearestNeighborRec(root->left,queryPoint,depth+1);
                 recursedLeft = true;
            }


        }

    }
    //check if root node is neareer than nearestNode
    if(nearestNode && distance(root->point ,  queryPoint) < distance(nearestNode->point,queryPoint))
        nearestNode = root;

    //check for left or right subtree that may have potential for closer node
    if(recursedLeft && root->right){

        if(splitByX){
             //check for the potential
             if(nearestNode && distance(queryPoint,root->point.x , true) <  distance(nearestNode->point , queryPoint)){
                Node *tempNearestNode = nearestNeighborRec(root->right,queryPoint,depth+1);
                //replace if closer node is found
                if(distance(tempNearestNode->point,queryPoint) < distance(nearestNode->point,queryPoint))
                    nearestNode = tempNearestNode;
             }

        }else{
             //check for the potential
             if(nearestNode && distance(queryPoint,root->point.y , false) <  distance(nearestNode->point , queryPoint)){
                Node *tempNearestNode = nearestNeighborRec(root->right,queryPoint,depth+1);
                //replace if closer node is found
                if(distance(tempNearestNode->point,queryPoint) < distance(nearestNode->point,queryPoint))
                    nearestNode = tempNearestNode;
             }
        }

    }else if(root->left){

        if(splitByX){
             //check for the potential
             if(nearestNode && distance(queryPoint,root->point.x , true) <  distance(nearestNode->point , queryPoint)){
                Node *tempNearestNode = nearestNeighborRec(root->left,queryPoint,depth+1);
                //replace if closer node is found
                if(distance(tempNearestNode->point,queryPoint) < distance(nearestNode->point,queryPoint))
                    nearestNode = tempNearestNode;
             }

        }else{
             //check for the potential
             if(nearestNode && distance(queryPoint,root->point.y , false) <  distance(nearestNode->point , queryPoint)){
                Node *tempNearestNode = nearestNeighborRec(root->left,queryPoint,depth+1);
                //replace if closer node is found
                if(distance(tempNearestNode->point,queryPoint) < distance(nearestNode->point,queryPoint))
                    nearestNode = tempNearestNode;
             }
        }

    }


    return nearestNode;

}

void KdTree::searchAreaRec(Node *root, const Rectangle &area, std::vector<Node *> &pts, unsigned int depth)
{
    if(!root) return;
    bool splitByX = depth % 2 ==0;
    bool isInArea = (root->point.x  > area.leftTopVertex.x) && (root->point.x  < area.leftTopVertex.x + area.width) && (root->point.y  < area.leftTopVertex.y) && (root->point.y  > area.leftTopVertex.y - area.height);
    if(isInArea) pts.push_back(root);
    if(splitByX){
        bool hasRightIntersect = (area.leftTopVertex.x + area.width) > root->point.x;
        bool hasLeftIntersect = area.leftTopVertex.x < root->point.x;
        if(hasRightIntersect){
             searchAreaRec(root->right,area,pts,depth+1);
        }
        if(hasLeftIntersect){
             searchAreaRec(root->left,area,pts,depth+1);
        }
    }else{
        bool hasTopIntersect = area.leftTopVertex.y > root->point.y;
        bool hasBottomIntersect = (area.leftTopVertex.y - area.height) < root->point.y;
        if(hasTopIntersect){
             searchAreaRec(root->right,area,pts,depth+1);
        }
        if(hasBottomIntersect){
             searchAreaRec(root->left,area,pts,depth+1);
        }
    }
}

void KdTree::searchAreaRec(Node *root, const Circle &area, std::vector<Node *> &pts, unsigned int depth)
{
    if(!root) return;
    bool splitByX = depth % 2 ==0;
    bool isInArea = ((root->point.x - area.centerVertex.x) * (root->point.x - area.centerVertex.x) + (root->point.y - area.centerVertex.y) * (root->point.y - area.centerVertex.y)) < area.raduis * area.raduis;
    if(isInArea) pts.push_back(root);
    if(splitByX){
        bool hasRightIntersect = (area.centerVertex.x + area.raduis) > root->point.x;
        bool hasLeftIntersect = (area.centerVertex.x - area.raduis) < root->point.x;
        if(hasRightIntersect){
             searchAreaRec(root->right,area,pts,depth+1);
        }
        if(hasLeftIntersect){
             searchAreaRec(root->left,area,pts,depth+1);
        }
    }else{
        bool hasTopIntersect = (area.centerVertex.y + area.raduis) > root->point.y;
        bool hasBottomIntersect = (area.centerVertex.y - area.raduis) < root->point.y;
        if(hasTopIntersect){
             searchAreaRec(root->right,area,pts,depth+1);
        }
        if(hasBottomIntersect){
             searchAreaRec(root->left,area,pts,depth+1);
        }
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

Node *KdTree::newNode(const Point &p , const std::string &shopN)
{
    return new Node(p ,shopN);

}

int KdTree::distance(const Point &p1, const Point &p2)
{
    return ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));

}

int KdTree::distance(const Point &p, int xy, bool inXaxis)
{
    if(inXaxis) return ((p.x - xy) * (p.x - xy));
    else  return ((p.y - xy) * (p.y - xy));

}


