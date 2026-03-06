#include <iostream>

class DesignBase
{
public:
    virtual void ExecuteDesign() = 0;
    virtual void ExportReport() = 0;
};

class DesignGen : public DesignBase
{
public:
    void ExecuteDesign() override
    {
        std::cout << "Execute Gen Design" << std::endl;
    }

    void ExportReport() override
    {
        std::cout << "Export Gen Report" << std::endl;
    }
};

class DesignCivil : public DesignBase
{
public:
    void ExecuteDesign() override
    {
        std::cout << "Execute Civil Design" << std::endl;
    }

        void ExportReport() override
    {
        std::cout << "Export Civil Report" << std::endl;
    }
};