#include <iostream>
#include <string>
#include <memory>

// Product
class SmartPhone {
public:
    std::string brand;
    std::string modelName;
    int battery;
    int cameraCount;
    bool hasGPS;

    void showInfo() {
        std::cout << "[" << brand << " - " << modelName << "]\n"
            << "배터리: " << battery << "mAh\n"
            << "카메라: " << cameraCount << "개\n"
            << "GPS: " << (hasGPS ? "지원" : "미지원") << "\n" << std::endl;
    }
};

// Builder Interface
class PhoneBuilder {
public:
    virtual ~PhoneBuilder() = default;
    virtual void reset() = 0;
    virtual void setModel() = 0;
    virtual void setBattery(bool isHighEnd) = 0;
    virtual void setCamera(bool isHighEnd) = 0;
    virtual void setGPS(bool isHighEnd) = 0;
    virtual std::unique_ptr<SmartPhone> getResult() = 0;
};

// Concrete Builder (iPhone & Galaxy)
class IPhoneBuilder : public PhoneBuilder {
private:
    std::unique_ptr<SmartPhone> phone;
public:
    IPhoneBuilder() { reset(); }
    void reset() override {
        phone = std::make_unique<SmartPhone>();
        phone->brand = "Apple";
    }
    void setModel() override { phone->modelName = "iPhone 시리즈"; }

    void setBattery(bool isHighEnd) override {
        phone->battery = isHighEnd ? 4352 : 3279;
    }
    void setCamera(bool isHighEnd) override {
        phone->cameraCount = isHighEnd ? 3 : 2;
    }
    void setGPS(bool isHighEnd) override {
        phone->hasGPS = true;
    }

    std::unique_ptr<SmartPhone> getResult() override {
        return std::move(phone);
    }
};

class GalaxyBuilder : public PhoneBuilder {
private:
    std::unique_ptr<SmartPhone> phone;
public:
    GalaxyBuilder() { reset(); }
    void reset() override {
        phone = std::make_unique<SmartPhone>();
        phone->brand = "Samsung";
    }
    void setModel() override { phone->modelName = "Galaxy 시리즈"; }

    void setBattery(bool isHighEnd) override {
        phone->battery = isHighEnd ? 5000 : 3500;
    }
    void setCamera(bool isHighEnd) override {
        phone->cameraCount = isHighEnd ? 4 : 1;
    }
    void setGPS(bool isHighEnd) override {
        phone->hasGPS = isHighEnd;
    }

    std::unique_ptr<SmartPhone> getResult() override {
        return std::move(phone);
    }
};

// Director
class Director {
public:
    void constructPremium(PhoneBuilder& builder) {
        builder.reset();
        builder.setModel();
        builder.setBattery(true);
        builder.setCamera(true);
        builder.setGPS(true);
    }

    void constructBudget(PhoneBuilder& builder) {
        builder.reset();
        builder.setModel();
        builder.setBattery(false);
        builder.setCamera(false);
        builder.setGPS(false);
    }
};

// Client Code
int main() {
    Director director;

    IPhoneBuilder iPhoneBuilder;

    director.constructPremium(iPhoneBuilder);
    auto pro = iPhoneBuilder.getResult();
    pro->showInfo();

    director.constructBudget(iPhoneBuilder);
    auto se = iPhoneBuilder.getResult();
    se->showInfo();

    GalaxyBuilder galaxyBuilder;

    director.constructPremium(galaxyBuilder);
    auto ultra = galaxyBuilder.getResult();
    ultra->showInfo();

    director.constructBudget(galaxyBuilder);
    auto seriesA = galaxyBuilder.getResult();
    seriesA->showInfo();

    return 0;
}