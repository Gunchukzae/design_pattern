#include "Facade.h"

// Client
int Facade() 
{
    HomeTheaterFacade theater;

    theater.watchMovie("인터스텔라");
    std::cout << "\n";
    theater.endMovie();

    return 0;
}