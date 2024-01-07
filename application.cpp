#include "application.h"
#include <iostream>
#include <algorithm>


Application::Application()
{
    this->vectoroffunctions.push_back(std::bind(&Application::addNeighborHood, this));
    this->vectoroffunctions.push_back(std::bind(&Application::addMainPizzaShop, this));
    this->vectoroffunctions.push_back(std::bind(&Application::addBranchPizzaShop, this));
    this->vectoroffunctions.push_back(std::bind(&Application::delBranchPizzaShop, this));
    this->vectoroffunctions.push_back(std::bind(&Application::listShopsInNeighborHood, this));
    this->vectoroffunctions.push_back(std::bind(&Application::listAllBranches, this));
    this->vectoroffunctions.push_back(std::bind(&Application::nearestShop, this));
    this->vectoroffunctions.push_back(std::bind(&Application::nearestBrShop, this));
    this->vectoroffunctions.push_back(std::bind(&Application::availableShops, this));
     this->vectoroffunctions.push_back(std::bind(&Application::hasMostBranches, this));
}

void Application::run()
{

    std::string optionStr= "";
    HashTable<int> optMap;
    optMap.add("add-n" , 1);
    optMap.add("add-p" , 2);
    optMap.add("add-br" , 3);
    optMap.add("del-br" , 4);
    optMap.add("list-p" , 5);
    optMap.add("list-brs" , 6);
    optMap.add("near-p" , 7);
    optMap.add("near-br" , 8);
    optMap.add("avail-p" , 9);
    optMap.add("most-brs" , 10);
    while(optionStr !="exit"){
        std::cout<< "welcome to pizza shop map , type an option : \n";
        std::cout << "Add-N : Add NeighborHood\n";
        std::cout << "Add-P - Add Main Pizza Shop\n";
        std::cout << "Add-Br - Add Branch Pizza Shop\n";
        std::cout << "Del-Br - Delete Branch Pizza Shop\n";
        std::cout << "List-P - list of all pizza shop in a neighborhood\n";
        std::cout << "List-Brs - list of coordinates of all branches of a main pizza shop\n";
        std::cout << "Near-P - find the nearest pizza shop to specific point\n";
        std::cout << "Near-Br - find the nearest branch pizza shop to specific point\n";
        std::cout << "Avail-P - list of all available pizza shop in a circular area\n";
        std::cout << "Most-Brs - name of a pizza shop that has the most number of branches\n";

        std::cout << "Exit - exit from the program\n";
        std::cin >> optionStr;
        std::transform(optionStr.begin(), optionStr.end(), optionStr.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        if(!optMap.contains(optionStr)){
            if(optionStr!="exit")
            std::cout << "invalid option !\n";
            continue;
        }
        this->vectoroffunctions.at(optMap.value(optionStr) - 1)();
        std::cout << "Press Enter to continue...";
        while (std::cin.get() != '\n');
        while (std::cin.get() != '\n');
        std::cout << std::endl;
    }

}

void Application::addNeighborHood()
{
    NeighborHood nb;
    std::cout << "enter the name of the neighborhood : \n";
    std::cin >> nb.name;
    std::cout << "enter the coordinate of left top corner vertex of rectangle : \n";
    getCoordinate(nb.area.leftTopVertex.x,nb.area.leftTopVertex.y);
    std::cout << "enter the width of rectangle : ";
    std::cin >> nb.area.width;
    std::cout << "enter the height of rectangle : ";
    std::cin >> nb.area.height;
    m_neighborhoodsMap.add(nb.name,nb);
     std::cout << "inserted successfully\n";
}

void Application::addMainPizzaShop()
{
    std::cout << "enter the coordinate of main pizza shop : \n";
    int x,y;
    getCoordinate(x,y);
    Node * existed = m_kdTree.search(x,y);
    if(existed){
        std::cout << "another shop named : " << existed->shopName << "already exist at this point !\n";
        return;
    }
    std::cout << "enter the pizza shop name : ";
    std::string name;
    std::cin >> name;
    if(m_shopsMap.contains(name)){
          std::cout << "another shop with this name already exist !\n";
        return;
    }
    m_kdTree.insert(x,y,name);
    Shop s;
    s.name = name;
    s.coordinate.x = x;
    s.coordinate.y =y;
    s.isPrimary = true;
    m_shopsMap.add(name,s);
    std::cout << "inserted successfully\n";
}

void Application::addBranchPizzaShop()
{
    std::cout << "enter the coordinate of branch pizza shop : \n";
    int x,y;
    getCoordinate(x,y);
    Node * existed = m_kdTree.search(x,y);
    if(existed){
        std::cout << "another shop named : " << existed->shopName << "already exist at this point !\n";
        return;
    }
    std::cout << "enter the branch pizza shop name : ";
    std::string name;
    std::cin >> name;
    if(m_shopsMap.contains(name)){
        std::cout << "another shop with this name already exist !\n";
        return;
    }

    std::cout << "enter the main pizza shop name : ";
    std::string name2;
    std::cin >> name2;
    if(!m_shopsMap.contains(name2) || (m_shopsMap.contains(name2) && !m_shopsMap.value(name2).isPrimary)){
        std::cout << "no main pizza shop with this name exists !\n";
        return;
    }
    m_kdTree.insert(x,y,name);
    Shop s;
    s.name = name;
    s.coordinate.x = x;
    s.coordinate.y =y;
    s.isPrimary = false;
    s.PrimaryName = name2;
    m_shopsMap.add(name,s);
    //update the primary shop , branches vector
    m_shopsMap.value(name2).branches.push_back(s);
    std::cout << "inserted successfully\n";
}

void Application::delBranchPizzaShop()
{
    std::cout << "enter the coordinate of the branch pizza shop you wanna delete : \n";
    int x ,y;
    getCoordinate(x,y);
    Node * existed = m_kdTree.search(x,y);
    if(!existed){
        std::cout << "no shop exist in this coordinate !\n";
        return;
    }
    Shop s = m_shopsMap.value(existed->shopName);
    if(s.isPrimary){
        std::cout << "the shop you wanna delete is main and not a branch !\n";
        return;
    }
    //delete from the branches vector of its primary shop
    auto it =m_shopsMap.value(s.PrimaryName).branches.begin();
    for(; it != m_shopsMap.value(s.PrimaryName).branches.end();it++){
        if((*it).name == s.name)
            break;
    }
    m_shopsMap.value(s.PrimaryName).branches.erase(it);

    //delete from kdtree
    m_kdTree.remove(x,y);
    //delete from hash map
    m_shopsMap.remove(s.name);
    std::cout << "deleted successfully !\n";
}

void Application::listShopsInNeighborHood()
{
    std::cout << "enter name of the neighborhood you wanna search in : ";
    std::string name;
    std::cin >> name;
    if(!m_neighborhoodsMap.contains(name)){
        std::cout << "no neighborhood with this name exists !\n";
        return;
    }
    NeighborHood nh = m_neighborhoodsMap.value(name);
    std::vector<Node *> foundedNodes =m_kdTree.searchArea(nh.area);
    for(auto n: foundedNodes){
        Shop sh = m_shopsMap.value(n->shopName);
        std::cout << sh;
    }

}

void Application::listAllBranches()
{
    std::cout << "enter the name of a main pizza shop you that wanna see its branches :\n";
    std::string name;
    std::cin >> name;
    if(!m_shopsMap.contains(name)){
        std::cout << "no shop exist with this name !\n";
        return;
    }
    Shop s = m_shopsMap.value(name);
    if(!s.isPrimary){
        std::cout << "the shop is not a main shop and its branch itself!\n";
        return;
    }
    for(const auto& bs : s.branches)
        std::cout << bs.coordinate << " - ";
    std::cout << "\n";
}

void Application::nearestShop()
{
    std::cout << "enter coordinate of your point : \n";
    int x, y;
    getCoordinate(x,y);
    Node *nearestNode = m_kdTree.nearestNeighbor(x,y);
    if(nearestNode){
        std::cout << "nearest shop found : \n";
        std::cout << m_shopsMap.value(nearestNode->shopName);
    }
}

void Application::nearestBrShop()
{
    std::cout << "enter coordinate of your point : \n";
    int x, y;
    getCoordinate(x,y);
    std::cout << "enter name of the main pizza shop :";
    std::string name;
    std::cin >> name;
    if(!m_shopsMap.contains(name)){
        std::cout << "no shop exists with this name !\n";
        return;
    }
    Shop s = m_shopsMap.value(name);
    if(!s.isPrimary){
        std::cout << "the shop is not a main shop and its branch itself!\n";
        return;
    }
    if(s.branches.empty()){
        std::cout << "the shop does not have any branch !\n";
        return;
    }
    KdTree tempTree;
    tempTree.insert(s.coordinate.x,s.coordinate.y,s.name);
    for(const auto& bs : s.branches){
        tempTree.insert(bs.coordinate.x,bs.coordinate.y,bs.name);
    }
    Node *nearestNode = tempTree.nearestNeighbor(x,y);
    if(nearestNode){
        std::cout << "nearest shop found : \n";
        std::cout << m_shopsMap.value(nearestNode->shopName);
    }

}

void Application::availableShops()
{
    std::cout << "enter coordinate of center of the circular area :\n";
    Circle c;
    getCoordinate(c.centerVertex.x,c.centerVertex.y);
    std::cout << "enter the raduis of the circular area : ";
    std::cin >> c.raduis;
    std::vector<Node *> foundedNodes =m_kdTree.searchArea(c);
    for(auto n: foundedNodes){
        Shop sh = m_shopsMap.value(n->shopName);
        std::cout << sh;
    }
}

void Application::hasMostBranches()
{
    std::vector<Temp> countsInfo;
    for (const auto &s : m_shopsMap.getAsList()){
        countsInfo.push_back({s.name,s.branches.size()});
    }
    countingSort(countsInfo);
    if(countsInfo.empty())return;
    std::cout << "the shop that has most branch is : " << countsInfo[countsInfo.size() -1].name << " with " << countsInfo[countsInfo.size() -1].count << " number of branches\n";
}


void Application::getCoordinate(int &x, int &y)
{
    int tempX,tempY;
    std::cout << "enter x : ";
    std::cin >> tempX;
    x= tempX;
    std::cout << "enter y : ";
    std::cin >> tempY;
    y= tempY;
}

void Application::countingSort(std::vector<Temp> &countsInfo)
{
    std::size_t maxCount = 0;
    for (const auto& temp : countsInfo) {
        if (temp.count > maxCount) {
            maxCount = temp.count;
        }
    }

    std::vector<std::size_t> countingArray(maxCount + 1, 0);

    for (const auto& temp : countsInfo) {
        countingArray[temp.count]++;
    }

    for (std::size_t i = 1; i < countingArray.size(); ++i) {
        countingArray[i] += countingArray[i - 1];
    }
    std::vector<Temp> sortedCountsInfo(countsInfo.size());

    for (auto it = countsInfo.rbegin(); it != countsInfo.rend(); ++it) {
        sortedCountsInfo[countingArray[it->count] - 1] = *it;
        countingArray[it->count]--;
    }

    countsInfo.swap(sortedCountsInfo);
}
