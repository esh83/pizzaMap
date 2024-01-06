#include "application.h"
#include <iostream>

void Application::run()
{
    enum{
        ADD_NEIGHBORHOOD = 1,

    };
    int option = 0;
    while(option !=-1){
        std::cout<< "welcome to pizza shop map , select an option : \n";
        std::cout << "1 - Add NeighborHood\n";
        std::cin >> option;
        switch(option){
        case ADD_NEIGHBORHOOD:
            this->addNeighborHood();
            break;

        default:
            std::cout << "option not recognized !\n";
        }
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
