#include "Builder.h"

int Builder()
{
    Director director;

    SportsCarBuilder sportsBuilder;
    director.Construct(sportsBuilder);
    Car* sports = sportsBuilder.GetResult();
    sports->Print();
    delete sports;

    std::cout << std::endl;

    SUVCarBuilder suvBuilder;
    director.Construct(suvBuilder);
    Car* suv = suvBuilder.GetResult();
    suv->Print();
    delete suv;

    std::cout << std::endl;

    ElectricCarBuilder electricBuilder;
    director.Construct(electricBuilder);
    Car* electric = electricBuilder.GetResult();
    electric->Print();
    delete electric;

    return 0;
}