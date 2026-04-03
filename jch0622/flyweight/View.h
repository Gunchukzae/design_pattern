#pragma once
#include <iostream>
#include <memory>
#include "Section.h"

class ViewFrame
{
public:
    void draw(const Node& node) const
    {
        std::cout << "Position: " << node.x << ", " << node.y << ", " << node.z << std::endl;
        
        const auto& section = node.sectionType;
        if (!section) return;
        
        std::cout << "Section Type: " << (section->sectType == SectionType::H ? "H-Beam" : "C-Channel") << std::endl;
        std::cout << "  Height: " << section->height << ", WidthUpper: " << section->widthUpper 
                  << ", WidthLower: " << section->widthLower << std::endl;
        std::cout << "  ThicknessWeb: " << section->thicknessWeb << ", ThicknessUpper: " << section->thicknessUpper 
                  << ", ThicknessLower: " << section->thicknessLower << std::endl;
        
        if (section->sectType == SectionType::H)
            drawHBeam(section);
        else
            drawCChannel(section);
        std::cout << std::endl;
    }
    
private:
    void drawHBeam(const std::shared_ptr<const Section>& section) const
    {
        int wu = std::max(4, int(section->widthUpper / 10));
        int wl = std::max(4, int(section->widthLower / 10));
        int tw = std::max(2, int(section->thicknessWeb / 5));
        int webH = std::max(2, int(section->height / 50));
        int flangeW = std::max(wu, wl);
        int padL = (flangeW - tw) / 2;
        int padR = flangeW - tw - padL;

        // Upper flange
        std::cout << "  +" << std::string(flangeW, '-') << "+" << std::endl;
        std::cout << "  |" << std::string(flangeW, '#') << "|  <- Upper flange" << std::endl;
        std::cout << "  +" << std::string(padL, '-') << "+" << std::string(tw, ' ') << "+" << std::string(padR, '-') << "+" << std::endl;
        // Web
        for (int i = 0; i < webH; ++i)
            std::cout << "  " << std::string(padL + 1, ' ') << "|" << std::string(tw - 2, ' ') << "|" << (i == 0 ? "  <- Web" : "") << std::endl;
        // Lower flange
        std::cout << "  +" << std::string(padL, '-') << "+" << std::string(tw, ' ') << "+" << std::string(padR, '-') << "+" << std::endl;
        std::cout << "  |" << std::string(flangeW, '#') << "|  <- Lower flange" << std::endl;
        std::cout << "  +" << std::string(flangeW, '-') << "+" << std::endl;
    }

    void drawCChannel(const std::shared_ptr<const Section>& section) const
    {
        int wu = std::max(4, int(section->widthUpper / 10));
        int wl = std::max(4, int(section->widthLower / 10));
        int tw = std::max(1, int(section->thicknessWeb / 10));
        int webH = std::max(2, int(section->height / 50));
        int flangeW = std::max(wu, wl);

        // Top flange
        std::cout << "  +" << std::string(flangeW, '-') << "+" << std::endl;
        std::cout << "  |" << std::string(flangeW, '#') << "|  <- Top flange" << std::endl;
        std::cout << "  +" << std::string(tw, '-') << "+" << std::string(flangeW - tw, ' ') << std::endl;
        // Web
        for (int i = 0; i < webH; ++i)
            std::cout << "  |" << std::string(tw, ' ') << "|" << (i == 0 ? "  <- Web" : "") << std::endl;
        // Bottom flange
        std::cout << "  +" << std::string(tw, '-') << "+" << std::string(flangeW - tw, ' ') << std::endl;
        std::cout << "  |" << std::string(flangeW, '#') << "|  <- Bottom flange" << std::endl;
        std::cout << "  +" << std::string(flangeW, '-') << "+" << std::endl;
    }
};
