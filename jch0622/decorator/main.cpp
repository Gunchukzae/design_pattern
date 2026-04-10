#include <vector>
#include <memory>
#include <string>
#include <iostream>

class Component
{
public:
    virtual ~Component() = default;

    virtual void Execute() = 0;
    
};

class Decorator : public Component
{
public:
    std::unique_ptr<Component> m_component;

public:
    Decorator(std::unique_ptr<Component>&& component) : m_component(std::move(component)) {}

    void Execute() override
    {
        m_component->Execute();
    }
};

class ConcreteComponent : public Component
{
public:
    void Execute() override
    {
        std::cout << "Final!";
        std::cout << std::endl;

    }
};

class DecoratorHit : public Decorator
{
public:

    DecoratorHit(std::unique_ptr<Component>&& component) : Decorator(std::move(component)) {}

    void Execute() override
    {
        std::cout << "Hit! ";
        Decorator::Execute();
    }
};

class DecoratorRun : public Decorator
{
public:
    DecoratorRun(std::unique_ptr<Component>&& component) : Decorator(std::move(component)) {}

    void Execute() override
    {
        std::cout << "Run! ";
        Decorator::Execute();
    }
};

int main()
{
    std::unique_ptr<Component> component = std::make_unique<ConcreteComponent>();
    component->Execute();

    std::unique_ptr<Component> decoratorHit = std::make_unique<DecoratorHit>(std::move(component));
    decoratorHit->Execute();

    std::unique_ptr<Component> decoratorRun = std::make_unique<DecoratorRun>(std::move(decoratorHit));
    decoratorRun = std::make_unique<DecoratorRun>(std::move(decoratorRun));
    decoratorRun = std::make_unique<DecoratorRun>(std::move(decoratorRun));
    decoratorRun->Execute();
}