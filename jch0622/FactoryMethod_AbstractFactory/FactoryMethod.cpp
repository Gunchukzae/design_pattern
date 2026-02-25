#include "Analysis.h"
#include <memory>

class AnalysisBaseFactory
{
public:
    virtual std::shared_ptr<AnalysisBase> CreateAnalysis() = 0;
    void ExecuteAnalysis()
    {
        std::shared_ptr<AnalysisBase> analysis = this->CreateAnalysis();
        analysis->Execute();
    }
};

class AnalysisFesFactory : public AnalysisBaseFactory
{
public:
    std::shared_ptr<AnalysisBase> CreateAnalysis() override
    {
        return std::make_shared<AnalysisFes>();
    }

};

class AnalysisMecFactory : public AnalysisBaseFactory
{
public:
    std::shared_ptr<AnalysisBase> CreateAnalysis() override
    {
        return std::make_shared<AnalysisMec>();
    }
};

void ClientCode(std::shared_ptr<AnalysisBaseFactory> analaysis)
{
    analaysis->ExecuteAnalysis();
}

int main()
{
    std::string solverType;
    std::cin >> solverType;
    std::shared_ptr<AnalysisBaseFactory> analysisFactory;

    if (solverType.compare("mec") == 0)
        analysisFactory = std::make_shared<AnalysisMecFactory>();
    else
        analysisFactory = std::make_shared<AnalysisFesFactory>();

    ClientCode(analysisFactory);
}




// void ClientCode(std::string solverType)
// {
//     std::shared_ptr<AnalysisBase> analysis;
//     if (solverType.compare("mec") == 0)
//         analysis = std::make_shared<AnalysisMec>();
//     else
//         analysis = std::make_shared<AnalysisFes>();

//     analysis->Execute();
// }

// int main()
// {
//     std::string solverType;
//     std::cin >> solverType;

//     ClientCode(solverType);
// }