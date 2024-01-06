#ifndef SCHEMMA_H
#define SCHEMMA_H
#include <string>
#include <vector>

struct Point {
    int x;
    int y;
    bool operator==(Point const& p2) const { return this->x == p2.x && this->y == p2.y; }

};

struct Rectangle{
    Rectangle() =default;
    Rectangle(int x ,int y , int width, int height){
        this->leftTopVertex.x = x;
        this->leftTopVertex.y = y;
        this->width = width;
        this->height = height;

    }
    Point leftTopVertex;
    int width;
    int height;
};


struct Circle{
    Circle() =default;
    Circle(int x ,int y , int raduis){
        this->centerVertex.x = x;
        this->centerVertex.y = y;
        this->raduis = raduis;
    }
    Point centerVertex;
    int raduis;
};


struct Shop{
    Point coordinate;
    std::string name;
    bool isPrimary;
    std::string PrimaryName;
    std::vector<Shop> branches;
};

struct NeighborHood{
    NeighborHood() = default;
    NeighborHood(int x ,int y , int width, int height ,const std::string &name){
        this->area.leftTopVertex.x = x;
         this->area.leftTopVertex.y = y;
        this->area.height = height;
         this->area.width = width;
        this->name = name;
    }
    Rectangle area;
    std::string name;
};



#endif // SCHEMMA_H
