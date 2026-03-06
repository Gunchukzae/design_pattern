#include <iostream>

class AnalysisBase
{
public:
    virtual void Execute() = 0;
};

class AnalysisFes : public AnalysisBase
{
public:
    void Execute() override
    {
        std::cout << "Execute fes" << std::endl;
    }
};

class AnalysisMec : public AnalysisBase
{
public:
    AnalysisMec() : m_bSelectMode(false) {}

    void Execute() override
    {
        std::string strMode = m_bSelectMode? "with selected." : "all.";
        std::cout << "Execute mec " << strMode << std::endl;
    }

    bool GetSelecteMode() const
    {
        return m_bSelectMode;
    }

    void SetSelectMode(bool isSelectMode)
    {
        m_bSelectMode = isSelectMode;
    }

public:
    bool m_bSelectMode;
};