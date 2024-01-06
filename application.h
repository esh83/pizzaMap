#ifndef APPLICATION_H
#define APPLICATION_H
#include "kdtree.h"
#include "hashtable.h"
#include "schemma.h"


class Application
{
public:
    Application() = default;
    void run();

private :
    KdTree m_kdTree;
    HashTable<Shop> m_shopsMap;
    HashTable<NeighborHood> m_neighborhoodsMap;
    void addNeighborHood();
    static void getCoordinate(int &x,int &y);

};

#endif // APPLICATION_H
