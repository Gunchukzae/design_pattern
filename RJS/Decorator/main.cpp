#include <iostream>
#include <string>
#include <memory>

class ICharacter {
public:
    virtual std::string getName() const = 0;
    virtual int getHP() const = 0;
    virtual int getAttack() const = 0;
    virtual int getDefense() const = 0;
    virtual void printStats() const = 0;
    virtual ~ICharacter() = default;
};

class Warrior : public ICharacter {
public:
    std::string getName() const override { return "용사"; }
    int getHP()      const override { return 100; }
    int getAttack()  const override { return 20; }
    int getDefense() const override { return 10; }

    void printStats() const override {
        std::cout << "[" << getName() << "] "
            << "HP:" << getHP()
            << " ATK:" << getAttack()
            << " DEF:" << getDefense() << "\n";
    }
};

class EquipmentDecorator : public ICharacter {
protected:
    std::shared_ptr<ICharacter> character_;

public:
    explicit EquipmentDecorator(std::shared_ptr<ICharacter> c)
        : character_(std::move(c)) {
    }

    std::string getName() const override { return character_->getName(); }
    int getHP()      const override { return character_->getHP(); }
    int getAttack()  const override { return character_->getAttack(); }
    int getDefense() const override { return character_->getDefense(); }

    void printStats() const override { character_->printStats(); }
};

class SwordDecorator : public EquipmentDecorator {
public:
    explicit SwordDecorator(std::shared_ptr<ICharacter> c)
        : EquipmentDecorator(std::move(c)) {
    }

    std::string getName() const override {
        return character_->getName() + " + 전설의검";
    }
    int getAttack() const override {
        return character_->getAttack() + 15;
    }

    void printStats() const override {
        std::cout << "[" << getName() << "] "
            << "HP:" << getHP()
            << " ATK:" << getAttack() << "(+15)"
            << " DEF:" << getDefense() << "\n";
    }
};

class ArmorDecorator : public EquipmentDecorator {
public:
    explicit ArmorDecorator(std::shared_ptr<ICharacter> c)
        : EquipmentDecorator(std::move(c)) {
    }

    std::string getName() const override {
        return character_->getName() + " + 미스릴갑옷";
    }
    int getDefense() const override {
        return character_->getDefense() + 20;
    }

    void printStats() const override {
        std::cout << "[" << getName() << "] "
            << "HP:" << getHP()
            << " ATK:" << getAttack()
            << " DEF:" << getDefense() << "(+20)\n";
    }
};

class MagicRingDecorator : public EquipmentDecorator {
public:
    explicit MagicRingDecorator(std::shared_ptr<ICharacter> c)
        : EquipmentDecorator(std::move(c)) {
    }

    std::string getName() const override {
        return character_->getName() + " + 마법반지";
    }
    int getHP()     const override { return character_->getHP() + 50; }
    int getAttack() const override { return character_->getAttack() + 10; }

    void printStats() const override {
        std::cout << "[" << getName() << "] "
            << "HP:" << getHP() << "(+50)"
            << " ATK:" << getAttack() << "(+10)"
            << " DEF:" << getDefense() << "\n";
    }
};

int main() {
    std::cout << "=== 던전 입장 전 장비 장착 ===\n\n";

    std::shared_ptr<ICharacter> hero = std::make_shared<Warrior>();
    std::cout << "▶ 장비 없음\n";
    hero->printStats();

    std::cout << "\n▶ 검 장착\n";
    hero = std::make_shared<SwordDecorator>(hero);
    hero->printStats();

    std::cout << "\n▶ 갑옷 추가 장착\n";
    hero = std::make_shared<ArmorDecorator>(hero);
    hero->printStats();

    std::cout << "\n▶ 마법반지까지 장착 (풀세팅)\n";
    hero = std::make_shared<MagicRingDecorator>(hero);
    hero->printStats();

    std::cout << "\n=== 던전 입장! ===\n";
    return 0;
}