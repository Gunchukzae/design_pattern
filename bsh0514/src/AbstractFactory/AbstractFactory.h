#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ostream>

// ====== Product Interfaces ======

class Environment 
{
public:
    virtual ~Environment() = default;
    virtual std::string getName() const = 0;
    virtual std::string getColor() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getEffect() const = 0;

    virtual void print(std::ostream& os) const 
    {
        os << "[Environment]\n";
        os << "  Name: " << getName() << "\n";
        os << "  Color: " << getColor() << "\n";
        os << "  Description: " << getDescription() << "\n";
        os << "  Effect: " << getEffect() << "\n";
    }
};

class Character 
{
public:
    virtual ~Character() = default;
    virtual std::string getName() const = 0;
    virtual std::string getType() const = 0;
    virtual int getHealth() const = 0;
    virtual int getPower() const = 0;
    virtual std::string getAbility() const = 0;

    virtual void print(std::ostream& os) const 
    {
        os << "[Character]\n";
        os << "  Name: " << getName() << "\n";
        os << "  Type: " << getType() << "\n";
        os << "  Health: " << getHealth() << "\n";
        os << "  Power: " << getPower() << "\n";
        os << "  Ability: " << getAbility() << "\n";
    }
};

class Terrain 
{
public:
    virtual ~Terrain() = default;
    virtual std::string getName() const = 0;
    virtual std::string getDifficulty() const = 0;
    virtual std::vector<std::string> getFeatures() const = 0;

    virtual void print(std::ostream& os) const 
    {
        os << "[Terrain]\n";
        os << "  Name: " << getName() << "\n";
        os << "  Difficulty: " << getDifficulty() << "\n";
        os << "  Features:\n";
        for (const auto& f : getFeatures()) 
        {
            os << "    - " << f << "\n";
        }
    }
};

class Weapon 
{
public:
    virtual ~Weapon() = default;
    virtual std::string getName() const = 0;
    virtual int getDamage() const = 0;
    virtual std::string getSpecialEffect() const = 0;

    virtual void print(std::ostream& os) const 
    {
        os << "[Weapon]\n";
        os << "  Name: " << getName() << "\n";
        os << "  Damage: " << getDamage() << "\n";
        os << "  SpecialEffect: " << getSpecialEffect() << "\n";
    }
};

// ====== Abstract Factory ======

class WorldFactory 
{
public:
    virtual ~WorldFactory() = default;

    virtual std::unique_ptr<Environment> createEnvironment() const = 0;
    virtual std::unique_ptr<Character> createCharacter() const = 0;
    virtual std::unique_ptr<Terrain> createTerrain() const = 0;
    virtual std::unique_ptr<Weapon> createWeapon() const = 0;

    virtual std::string getWorldName() const = 0;
    virtual std::string getWorldTheme() const = 0;
};

// 핵심: “서로 연관된 제품군(product family)”을 일관된 조합으로 생성하는 인터페이스 제공
// Base가 “공통 속성 부여”도 할 수는 있지만, 패턴의 본질은 제품군 전체의 생성 규칙을 통일
// 호환되는 구성요소들(Environment / Character / Terrain / Weapon)을 같은 팩토리에서 세트로 뽑게 하는 것
