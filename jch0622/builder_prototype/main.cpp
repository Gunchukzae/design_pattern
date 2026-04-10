#include <iostream>
#include <memory>

class AppleJuice
{
public:
    int m_Suger;
    int m_Apple;
    int m_Water;

public:
    AppleJuice() : m_Suger(0), m_Apple(0), m_Water(0) {}

public:
    virtual void SetVegetable(int number) = 0;
    virtual std::unique_ptr<AppleJuice> Clone() = 0;
    virtual void PrintList() = 0;

};

class CarrotAppleJuice : public AppleJuice
{
private:
    std::unique_ptr<int> m_carrot;

public:
    CarrotAppleJuice()
    {
        m_carrot = std::make_unique<int>(0);
    }

public:
    void SetVegetable(int number) override
    {
        *m_carrot = number;
    }
    std::unique_ptr<AppleJuice> Clone() override
    {
        std::unique_ptr<AppleJuice> juice = std::make_unique<CarrotAppleJuice>();
        juice->m_Suger = this->m_Suger;
        juice->m_Apple = this->m_Apple;
        juice->m_Water = this->m_Water;
        juice->SetVegetable(*this->m_carrot);

        return juice;
    }
    void PrintList() override
    {
        std::cout << "suger: " << m_Suger << std::endl;
        std::cout << "apple: " << m_Apple << std::endl;
        std::cout << "water: " << m_Water << std::endl;
        std::cout << "carrot: " << *m_carrot << std::endl;
    }
};

class OnionAppleJuice : public AppleJuice
{
private:
    std::unique_ptr<int> m_onion;

public:
    OnionAppleJuice()
    {
        m_onion = std::make_unique<int>(0);
    }

public:
    void SetVegetable(int number) override
    {
        *m_onion = number;
    }
    std::unique_ptr<AppleJuice> Clone() override
    {
        std::unique_ptr<AppleJuice> juice = std::make_unique<OnionAppleJuice>();
        juice->m_Suger = this->m_Suger;
        juice->m_Apple = this->m_Apple;
        juice->m_Water = this->m_Water;
        juice->SetVegetable(*this->m_onion);

        return juice;
    }
    void PrintList() override
    {
        std::cout << "suger: " << m_Suger << std::endl;
        std::cout << "apple: " << m_Apple << std::endl;
        std::cout << "water: " << m_Water << std::endl;
        std::cout << "onion: " << *m_onion << std::endl;
    }
};

class AppleJuiceBuilder
{
public:
    std::unique_ptr<AppleJuice> m_AppleJuice;

public:
    virtual void InputSuger(int number) = 0;
    virtual void InputApple(int number) = 0;
    virtual void InputWater(int number) = 0;
    virtual void InputVegetable(int number) = 0;
    virtual std::unique_ptr<AppleJuice> GetJuice()
    {
        return m_AppleJuice->Clone();
    }
};

class CarrotAppleJuiceBuilder : public AppleJuiceBuilder
{
public:
    CarrotAppleJuiceBuilder()
    {
        m_AppleJuice = std::make_unique<CarrotAppleJuice>();
    }

public:
    void InputSuger(int number) override
    {
        m_AppleJuice->m_Suger = number;
    }
    void InputApple(int number) override
    {
        m_AppleJuice->m_Apple = number;
    }
    void InputWater(int number) override
    {
        m_AppleJuice->m_Water = number;
    }
    void InputVegetable(int number) override
    {
        m_AppleJuice->SetVegetable(number);
    }
};

class OnionAppleJuiceBuilder : public AppleJuiceBuilder
{
public:
    OnionAppleJuiceBuilder()
    {
        m_AppleJuice = std::make_unique<OnionAppleJuice>();
    }

public:
    void InputSuger(int number) override
    {
        m_AppleJuice->m_Suger = number;
    }
    void InputApple(int number) override
    {
        m_AppleJuice->m_Apple = number;
    }
    void InputWater(int number) override
    {
        m_AppleJuice->m_Water = number;
    }
    void InputVegetable(int number) override
    {
        m_AppleJuice->SetVegetable(number);
    }
};


class AppleJuiceDirector
{
public:
    AppleJuiceBuilder* m_Builder;

public:
    void SetBuilder(AppleJuiceBuilder* builder)
    {
        m_Builder = builder;
    }

    void BuildNoSugerJuice()
    {
        m_Builder->InputApple(10);
        m_Builder->InputWater(100);
        m_Builder->InputVegetable(10);
    }

    void BuildWithSugerJuice()
    {
        m_Builder->InputSuger(100);
        m_Builder->InputApple(10);
        m_Builder->InputWater(100);
        m_Builder->InputVegetable(10);
    }
};

int main()
{
    std::unique_ptr<AppleJuiceBuilder> builder = std::make_unique<CarrotAppleJuiceBuilder>();
    builder->InputSuger(100);
    builder->InputApple(10);
    builder->InputWater(100);
    builder->InputVegetable(10);
    std::unique_ptr<AppleJuice> juice = builder->GetJuice();
    juice->PrintList();

    std::unique_ptr<AppleJuiceBuilder> builder2 = std::make_unique<OnionAppleJuiceBuilder>();
    AppleJuiceDirector director;
    director.SetBuilder(builder2.get());
    director.BuildNoSugerJuice();
    std::unique_ptr<AppleJuice> juice2 = builder2->GetJuice();
    juice2->PrintList();


    
}