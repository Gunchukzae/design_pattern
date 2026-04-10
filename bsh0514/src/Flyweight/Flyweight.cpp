#include "Flyweight.h"

int Flyweight() 
{
    Forest forest;

    // 나무 6그루를 심지만, 종류는 2가지뿐
    forest.plantTree(10, 20,  "소나무", "초록", "pine.png");
    forest.plantTree(30, 50,  "소나무", "초록", "pine.png");
    forest.plantTree(70, 80,  "소나무", "초록", "pine.png");
    forest.plantTree(15, 35,  "단풍나무", "빨강", "maple.png");
    forest.plantTree(55, 90,  "단풍나무", "빨강", "maple.png");
    forest.plantTree(95, 10,  "단풍나무", "빨강", "maple.png");

    forest.render();
    forest.printStats();

    return 0;
}