#include "Analysis.h"
#include "Design.h"
#include <memory>

class ProductBaseFactory
{
public:
    virtual std::shared_ptr<AnalysisBase> CreateAnalysis() = 0;
    virtual std::shared_ptr<DesignBase> CreateDesign() = 0;
};

class BridgeFactory : public ProductBaseFactory
{
public:
    std::shared_ptr<AnalysisBase> CreateAnalysis() override
    {
        return std::make_shared<AnalysisMec>();
    }

    std::shared_ptr<DesignBase> CreateDesign() override
    {
        return std::make_shared<DesignCivil>();
    }
};

class MAXFactory : public ProductBaseFactory
{
public:
    std::shared_ptr<AnalysisBase> CreateAnalysis() override
    {
        return std::make_shared<AnalysisFes>();
    }

    std::shared_ptr<DesignBase> CreateDesign() override
    {
        return std::make_shared<DesignGen>();
    }
};

void ClientCode(std::shared_ptr<ProductBaseFactory> productFactory)
{
    std::shared_ptr<AnalysisBase> analysis = productFactory->CreateAnalysis();
    std::shared_ptr<DesignBase> design = productFactory->CreateDesign();

    analysis->Execute();
    design->ExecuteDesign();
    design->ExportReport();
}

int main()
{
    std::string productType;
    std::cin >> productType;
    std::shared_ptr<ProductBaseFactory> productFactory;

    if (productType.compare("MAX") == 0)
        productFactory = std::make_shared<MAXFactory>();
    else
        productFactory = std::make_shared<BridgeFactory>();

    ClientCode(productFactory);
}