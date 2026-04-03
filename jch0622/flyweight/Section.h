#pragma once
#include <memory>
#include <vector>
#include <tuple>

class ViewFrame;

enum class SectionType : unsigned int
{
    H = 0,
    C
};

struct Section
{
    SectionType sectType;
    double height;
    double widthUpper;
    double widthLower;
    double thicknessWeb;
    double thicknessUpper;
    double thicknessLower;

    std::vector<double> property;

    Section(SectionType st, double h, double wu, double wl, double tw, double tu, double tl)
        : sectType(st), height(h), widthUpper(wu), widthLower(wl), thicknessWeb(tw), thicknessUpper(tu), thicknessLower(tl) {}

    bool operator<(const Section& s) const
    {
        return std::tie(sectType, height, widthUpper, widthLower, thicknessWeb, thicknessUpper, thicknessLower) <
               std::tie(s.sectType, s.height, s.widthUpper, s.widthLower, s.thicknessWeb, s.thicknessUpper, s.thicknessLower);
    }
};

struct Node
{
    double x;
    double y;
    double z;
    std::shared_ptr<const Section> sectionType;

    void draw(const ViewFrame& viewFrame) const;
};
