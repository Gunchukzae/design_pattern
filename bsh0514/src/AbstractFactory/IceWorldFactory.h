#pragma once

#include "AbstractFactory.h"

// ===== Concrete Products =====

class IceEnvironment : public Environment 
{
public:
    std::string getName() const override { return "Frozen Wasteland"; }
    std::string getColor() const override { return "#60A5FA"; }
    std::string getDescription() const override 
    {
        return "A harsh frozen landscape covered in eternal snow and ice";
    }
    std::string getEffect() const override 
    {
        return "Freezing cold reduces movement speed by 30%";
    }
};

class IceCharacter : public Character 
{
public:
    std::string getName() const override { return "Frost Warrior"; }
    std::string getType() const override { return "Ice"; }
    int getHealth() const override { return 120; }
    int getPower() const override { return 85; }
    std::string getAbility() const override 
    {
        return "Ice Shield (Creates a protective barrier of frozen ice)";
    }
};

class IceTerrain : public Terrain 
{
public:
    std::string getName() const override { return "Glacial Mountains"; }
    std::string getDifficulty() const override { return "Hard"; }
    std::vector<std::string> getFeatures() const override 
    {
        return { "Frozen lakes", "Ice caves", "Snowstorms", "Glaciers" };
    }
};

class IceWeapon : public Weapon 
{
public:
    std::string getName() const override { return "Frostbite Blade"; }
    int getDamage() const override { return 75; }
    std::string getSpecialEffect() const override 
    {
        return "Freezes enemies on hit, slowing their attacks";
    }
};

// ===== Concrete Factory =====

class IceWorldFactory : public WorldFactory 
{
public:
    std::unique_ptr<Environment> createEnvironment() const override 
    {
        return std::make_unique<IceEnvironment>();
    }

    std::unique_ptr<Character> createCharacter() const override 
    {
        return std::make_unique<IceCharacter>();
    }

    std::unique_ptr<Terrain> createTerrain() const override 
    {
        return std::make_unique<IceTerrain>();
    }

    std::unique_ptr<Weapon> createWeapon() const override 
    {
        return std::make_unique<IceWeapon>();
    }

    std::string getWorldName() const override { return "Ice World"; }
    std::string getWorldTheme() const override 
    {
        return "A frozen realm of eternal winter and crystalline beauty";
    }
};
