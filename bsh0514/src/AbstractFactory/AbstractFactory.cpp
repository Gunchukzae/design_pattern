#include <iostream>

#include "AbstractFactory.h"
#include "FireWorldFactory.h"
#include "IceWorldFactory.h"

void RunAbstractFactory(const WorldFactory& factory)
{
    auto env = factory.createEnvironment();
    auto character = factory.createCharacter();
    auto terrain = factory.createTerrain();
    auto weapon = factory.createWeapon();

    std::cout << "[World]\n";
    std::cout << "  " << factory.getWorldName() << "\n\n";

    std::cout << "[Theme]\n";
    std::cout << "  " << factory.getWorldTheme() << "\n\n";

    env->print(std::cout);
    std::cout << "\n";

    character->print(std::cout);
    std::cout << "\n";

    terrain->print(std::cout);
    std::cout << "\n";

    weapon->print(std::cout);
    std::cout << "\n";
}

int AbstractFactory()
{
    FireWorldFactory fireFactory;
    IceWorldFactory iceFactory;

    RunAbstractFactory(fireFactory);
    std::cout << "--------------------------------------------------------------------------------\n\n";
    RunAbstractFactory(iceFactory);

    return 0;
}
