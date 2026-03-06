#pragma once

#include <iostream>
#include <string>

class Car
{
public:
    std::string engine;
    std::string body;
    std::string wheels;

    void Print()
    {
        std::cout << "Engine: " << engine << std::endl;
        std::cout << "Body: " << body << std::endl;
        std::cout << "Wheels: " << wheels << std::endl;
    }
};

class CarBuilder
{
public:
    virtual void BuildEngine() = 0;
    virtual void BuildBody() = 0;
    virtual void BuildWheels() = 0;
    virtual Car* GetResult() = 0;

    virtual ~CarBuilder() = default;
};

class SportsCarBuilder : public CarBuilder
{
private:
    Car* car;

public:
    SportsCarBuilder()
    {
        car = new Car();
    }

    void BuildEngine() override
    {
        car->engine = "V8 Engine";
    }

    void BuildBody() override
    {
        car->body = "Sports Body";
    }

    void BuildWheels() override
    {
        car->wheels = "18 inch wheels";
    }

    Car* GetResult() override
    {
        return car;
    }
};

class SUVCarBuilder : public CarBuilder
{
private:
    Car* car;

public:
    SUVCarBuilder()
    {
        car = new Car();
    }

    void BuildEngine() override
    {
        car->engine = "V6 Engine";
    }

    void BuildBody() override
    {
        car->body = "SUV Body";
    }

    void BuildWheels() override
    {
        car->wheels = "20 inch Offroad wheels";
    }

    Car* GetResult() override
    {
        return car;
    }
};

class ElectricCarBuilder : public CarBuilder
{
private:
    Car* car;

public:
    ElectricCarBuilder()
    {
        car = new Car();
    }

    void BuildEngine() override
    {
        car->engine = "Electric Motor";
    }

    void BuildBody() override
    {
        car->body = "Electric Body";
    }

    void BuildWheels() override
    {
        car->wheels = "17 inch Eco wheels";
    }

    Car* GetResult() override
    {
        return car;
    }
};

class Director
{
public:
    void Construct(CarBuilder& builder)
    {
        builder.BuildEngine();
        builder.BuildBody();
        builder.BuildWheels();
    }
};
