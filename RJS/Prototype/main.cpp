#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

// Base Prototype (Interface)
class PhoneComponent {
public:
    virtual ~PhoneComponent() = default;
    virtual std::unique_ptr<PhoneComponent> clone() const = 0;
    virtual void use() const = 0;
};

// Concrete Prototypes (Apple & Galaxy)
class AppleCamera : public PhoneComponent {
public:
    std::unique_ptr<PhoneComponent> clone() const override {
        return std::make_unique<AppleCamera>(*this);
    }
    void use() const override { std::cout << "iPhone Camera: Snap!\n"; }
};

class GalaxyCamera : public PhoneComponent {
public:
    std::unique_ptr<PhoneComponent> clone() const override {
        return std::make_unique<GalaxyCamera>(*this);
    }
    void use() const override { std::cout << "Galaxy Camera: High-res Snap!\n"; }
};

// Prototype Registry
class PrototypeRegistry {
private:
    std::unordered_map<std::string, std::unique_ptr<PhoneComponent>> items;

public:
    void addItem(std::string id, std::unique_ptr<PhoneComponent> prototype) {
        items[id] = std::move(prototype);
    }

    std::unique_ptr<PhoneComponent> getByID(std::string id) {
        if (items.find(id) != items.end()) {
            return items[id]->clone();
        }
        return nullptr;
    }
};

// Client Code
int main() {
    PrototypeRegistry registry;

    registry.addItem("iPhone_Cam", std::make_unique<AppleCamera>());
    registry.addItem("Galaxy_Cam", std::make_unique<GalaxyCamera>());

    auto myCam1 = registry.getByID("iPhone_Cam");
    if (myCam1) myCam1->use();

    auto myCam2 = registry.getByID("Galaxy_Cam");
    if (myCam2) myCam2->use();

    return 0;
}