#ifndef KDTREE_H
#define KDTREE_H

struct Point {
    int x;
    int y;
    bool operator==(Point const& p2) const { return this->x == p2.x && this->y == p2.y; }

};
class Node {
    friend class KdTree;
public :
    Node(const Point &p){
        this->point.x = p.x;
        this->point.y = p.y;
        this->left = nullptr;
        this->right = nullptr;
    }
//private :
    Point point;
    Node * left;
    Node * right;

};

class KdTree
{
public:
    KdTree();
    ~KdTree();
    void insert(int x , int y);
    void remove(int x ,int y);
    Node* findMin(bool inXaxis);
    Node *search(int x ,int y);
    Node *nearestNeighbor(int x , int y);
    void clear();
    void inorder();

private :
    Node * insertRec(Node *root,const Point &p , unsigned int depth);
    Node * removeRec(Node *root ,const Point &p , unsigned int depth);
    Node * findMinRec(Node *root , bool inXaxis , unsigned int depth);
    Node * searchRec(Node *root , const Point &p , unsigned int depth);
    Node * nearestNeighborRec(Node *root,const Point &queryPoint,unsigned int depth);
    void inorderRec(Node *root);
    void clearRec(Node *root);
    Node *root;
    static Node* newNode(const Point &p);
    static int distance(const Point &p1,const Point &p2);
    static int distance(const Point &p , int xy, bool inXaxis);
};


#endif // KDTREE_H
