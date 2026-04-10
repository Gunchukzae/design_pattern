#include <iostream>
#include <algorithm>
#include "Section.h"
#include "View.h"

struct SectionFactory
{
private:
    std::vector<std::shared_ptr<const Section>> m_vecSect;

public:
    std::shared_ptr<const Section> GetSectType(SectionType sectType, double height, double widthUpper, double widthLower, double thicknessWeb, double thicknessUpper, double thicknessLower)
    {
        auto it = std::find_if(m_vecSect.begin(), m_vecSect.end(),
        [&](const std::shared_ptr<const Section>& s)
        {
            return s->sectType == sectType &&
            s->height == height &&
            s->widthUpper == widthUpper &&
            s->widthLower == widthLower &&
            s->thicknessWeb == thicknessWeb &&
            s->thicknessUpper == thicknessUpper &&
            s->thicknessLower == thicknessLower;
        });

        if (it != m_vecSect.end())
            return *it;

        auto newSect = std::make_shared<const Section>(sectType, height, widthUpper, widthLower, thicknessWeb, thicknessUpper, thicknessLower);
        m_vecSect.push_back(newSect);
        return newSect;
    }
};

void Node::draw(const ViewFrame& viewFrame) const
{
    viewFrame.draw(*this);
}

int main()
{
    SectionFactory factory;

    auto sect1 = factory.GetSectType(SectionType::H, 300, 200, 200, 10, 15, 15);
    auto sect2 = factory.GetSectType(SectionType::C, 100, 100, 100, 10, 20, 20);
    auto sect3 = factory.GetSectType(SectionType::C, 100, 100, 100, 10, 20, 20);

    std::cout << sect1.get() << std::endl;
    std::cout << sect2.get() << std::endl;
    std::cout << sect3.get() << std::endl;

    Node e1{0, 0, 0, sect1};
    Node e2{1000, 0, 0, sect1};
    Node e3{0, 1000, 0, sect2};

    ViewFrame viewFrame;
    e1.draw(viewFrame);
    e2.draw(viewFrame);
    e3.draw(viewFrame);
}

/*

// output
0x218043b2890
0x218043b2c10
0x218043b2c10
Position: 0, 0, 0
Section Type: H-Beam
  Height: 300, WidthUpper: 200, WidthLower: 200
  ThicknessWeb: 10, ThicknessUpper: 15, ThicknessLower: 15
  +--------------------+
  |####################|  <- Upper flange
  +---------+  +---------+
            ||  <- Web
            ||
            ||
            ||
            ||
            ||
  +---------+  +---------+
  |####################|  <- Lower flange
  +--------------------+

Position: 1000, 0, 0
Section Type: H-Beam
  Height: 300, WidthUpper: 200, WidthLower: 200
  ThicknessWeb: 10, ThicknessUpper: 15, ThicknessLower: 15
  +--------------------+
  |####################|  <- Upper flange
  +---------+  +---------+
            ||  <- Web
            ||
            ||
            ||
            ||
            ||
  +---------+  +---------+
  |####################|  <- Lower flange
  +--------------------+

Position: 0, 1000, 0
Section Type: C-Channel
  Height: 100, WidthUpper: 100, WidthLower: 100
  ThicknessWeb: 10, ThicknessUpper: 20, ThicknessLower: 20
  +----------+
  |##########|  <- Top flange
  +-+
  | |  <- Web
  | |
  +-+
  |##########|  <- Bottom flange
  +----------+
*/