#include <iostream>
#include <string>
#include <memory>

// Abstract Products
class Camera {
public:
    virtual void snap() = 0;
    virtual ~Camera() = default;
};

class Button {
public:
    virtual void press() = 0;
    virtual ~Button() = default;
};

class ID {
public:
    virtual void verify() = 0;
    virtual ~ID() = default;
};

// Concrete Products for Apple
class AppleCamera : public Camera {
public:
    void snap() override {
        std::cout << "iPhone Camera\n";
    }
};

class AppleButton : public Button {
public:
    void press() override {
        std::cout << "Apple Button\n";
    }
};

class AppleID : public ID {
public:
    void verify() override {
        std::cout << "FaceID\n";
    }
};

// Concrete Products for Galaxy
class GalaxyCamera : public Camera {
public:
    void snap() override {
        std::cout << "Galaxy Camera\n";
    }
};

class GalaxyButton : public Button {
public:
    void press() override {
        std::cout << "Galaxy Button\n";
    }
};

class GalaxyID : public ID {
public:
    void verify() override {
        std::cout << "Fingerprint\n";
    }
};

// Abstract Factory
class PhoneFactory {
public:
    //factory methods
    virtual std::unique_ptr<Camera> createCamera() = 0;
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<ID> createID() = 0;
    virtual ~PhoneFactory() = default;
};

// Concrete Factories
class AppleFactory : public PhoneFactory {
public:
    std::unique_ptr<Camera> createCamera() override {
        return std::make_unique<AppleCamera>();
    }

    std::unique_ptr<Button> createButton() override {
        return std::make_unique<AppleButton>();
    }

    std::unique_ptr<ID> createID() override {
        return std::make_unique<AppleID>();
    }
};

class GalaxyFactory : public PhoneFactory {
public:
    std::unique_ptr<Camera> createCamera() override {
        return std::make_unique<GalaxyCamera>();
    }

    std::unique_ptr<Button> createButton() override {
        return std::make_unique<GalaxyButton>();
    }

    std::unique_ptr<ID> createID() override {
        return std::make_unique<GalaxyID>();
    }
};

// Client Code
class SmartPhone {
private:
    std::unique_ptr<Camera> cam;
    std::unique_ptr<Button> btn;
    std::unique_ptr<ID> id;

public:
    SmartPhone(PhoneFactory& factory) {
        cam = factory.createCamera();
        btn = factory.createButton();
        id = factory.createID();
    }

    void use() {
        cam->snap();
        btn->press();
        id->verify();
    }
};

int main() {

    std::string myChoice = "Apple";

    std::unique_ptr<PhoneFactory> factory;

    if (myChoice == "Apple") {
        factory = std::make_unique<AppleFactory>();
    }
    else if (myChoice == "Galaxy") {
        factory = std::make_unique<GalaxyFactory>();
    }
    else {
        std::cerr << "Unknown brand!" << std::endl;
        return 1;
    }

    SmartPhone myPhone(*factory);
    myPhone.use();

    return 0;
}