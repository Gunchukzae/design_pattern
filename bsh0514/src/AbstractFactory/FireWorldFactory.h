#pragma once

#include "AbstractFactory.h"

// ===== Concrete Products =====

class FireEnvironment : public Environment 
{
public:
    std::string getName() const override { return "Volcanic Inferno"; }
    std::string getColor() const override { return "#EF4444"; }
    std::string getDescription() const override 
    {
        return "A scorching landscape of molten lava and endless flames";
    }
    std::string getEffect() const override 
    {
        return "Intense heat deals 5 damage per second";
    }
};

class FireCharacter : public Character 
{
public:
    std::string getName() const override { return "Flame Knight"; }
    std::string getType() const override { return "Fire"; }
    int getHealth() const override { return 100; }
    int getPower() const override { return 110; }
    std::string getAbility() const override 
    {
        return "Inferno Blast (Unleashes a devastating wave of flames)";
    }
};

class FireTerrain : public Terrain 
{
public:
    std::string getName() const override { return "Volcanic Badlands"; }
    std::string getDifficulty() const override { return "Extreme"; }
    std::vector<std::string> getFeatures() const override 
    {
        return { "Lava rivers", "Active volcanoes", "Ash clouds", "Fire geysers" };
    }
};

class FireWeapon : public Weapon 
{
public:
    std::string getName() const override { return "Blazing Sword"; }
    int getDamage() const override { return 95; }
    std::string getSpecialEffect() const override 
    {
        return "Ignites enemies, causing burn damage over time";
    }
};

// ===== Concrete Factory =====

class FireWorldFactory : public WorldFactory 
{
public:
    std::unique_ptr<Environment> createEnvironment() const override 
    {
        return std::make_unique<FireEnvironment>();
    }

    std::unique_ptr<Character> createCharacter() const override 
    {
        return std::make_unique<FireCharacter>();
    }

    std::unique_ptr<Terrain> createTerrain() const override 
    {
        return std::make_unique<FireTerrain>();
    }

    std::unique_ptr<Weapon> createWeapon() const override 
    {
        return std::make_unique<FireWeapon>();
    }

    std::string getWorldName() const override { return "Fire World"; }
    std::string getWorldTheme() const override 
    {
        return "A blazing realm of eternal flames and volcanic fury";
    }
};
