#include <iostream>
#include <memory>
#include <string>

// Abstract Products
class Chair {
public:
    virtual ~Chair() {}
    virtual std::string sitOn() const = 0;
};

class Sofa {
public:
    virtual ~Sofa() {}
    virtual std::string layOn() const = 0;
};

class Table {
public:
    virtual ~Table() {}
    virtual std::string putOn() const = 0;
};

// Concrete Products - Modern Style
class ModernChair : public Chair {
public:
    std::string sitOn() const override {
        return "Sitting on a modern chair with sleek design";
    }
};

class ModernSofa : public Sofa {
public:
    std::string layOn() const override {
        return "Laying on a modern sofa with minimalist style";
    }
};

class ModernTable : public Table {
public:
    std::string putOn() const override {
        return "Putting items on a modern glass table";
    }
};

// Concrete Products - Victorian Style
class VictorianChair : public Chair {
public:
    std::string sitOn() const override {
        return "Sitting on a Victorian chair with ornate carvings";
    }
};

class VictorianSofa : public Sofa {
public:
    std::string layOn() const override {
        return "Laying on a Victorian sofa with velvet upholstery";
    }
};

class VictorianTable : public Table {
public:
    std::string putOn() const override {
        return "Putting items on a Victorian wooden table with intricate details";
    }
};

// Abstract Factory
class FurnitureFactory {
public:
    virtual ~FurnitureFactory() {}
    virtual std::unique_ptr<Chair> createChair() const = 0;
    virtual std::unique_ptr<Sofa> createSofa() const = 0;
    virtual std::unique_ptr<Table> createTable() const = 0;
};

// Concrete Factories
class ModernFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<ModernChair>();
    }
    
    std::unique_ptr<Sofa> createSofa() const override {
        return std::make_unique<ModernSofa>();
    }
    
    std::unique_ptr<Table> createTable() const override {
        return std::make_unique<ModernTable>();
    }
};

class VictorianFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<VictorianChair>();
    }
    
    std::unique_ptr<Sofa> createSofa() const override {
        return std::make_unique<VictorianSofa>();
    }
    
    std::unique_ptr<Table> createTable() const override {
        return std::make_unique<VictorianTable>();
    }
};

// Client Code
void furnishRoom(const FurnitureFactory& factory) {
    auto chair = factory.createChair();
    auto sofa = factory.createSofa();
    auto table = factory.createTable();
    
    std::cout << chair->sitOn() << std::endl;
    std::cout << sofa->layOn() << std::endl;
    std::cout << table->putOn() << std::endl;
}

int main() {
    std::cout << "=== Modern Furniture Style ===" << std::endl;
    ModernFurnitureFactory modernFactory;
    furnishRoom(modernFactory);
    
    std::cout << "\n=== Victorian Furniture Style ===" << std::endl;
    VictorianFurnitureFactory victorianFactory;
    furnishRoom(victorianFactory);
    
    return 0;
}
