#ifndef APPLICATION_H
#define APPLICATION_H
#include "kdtree.h"
#include "hashtable.h"
#include "schemma.h"
#include <vector>
#include <functional>


class Application
{
public:
    Application();
    void run();

private :
    KdTree m_kdTree;
    HashTable<Shop> m_shopsMap;
    HashTable<NeighborHood> m_neighborhoodsMap;
    void addNeighborHood();
    void addMainPizzaShop();
    void addBranchPizzaShop();
     void delBranchPizzaShop();
    void listShopsInNeighborHood();
     void listAllBranches();
    void nearestShop();
     void nearestBrShop();
    void availableShops();
     void hasMostBranches();
    static void getCoordinate(int &x,int &y);
     typedef std::function<void()> ffptr;

    std::vector<ffptr> vectoroffunctions;
     struct Temp {
         std::string name;
         std::size_t count;
     };
     void countingSort(std::vector<Temp>& countsInfo);

};

#endif // APPLICATION_H
