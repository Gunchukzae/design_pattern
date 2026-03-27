#include <vector>
#include <memory>
#include <string>
#include <iostream>

class Component
{
public:
    int m_x = 0;
    int m_y = 0;
public:
    virtual void Add(std::unique_ptr<Component>&& obj) {}
    virtual void Delete() {}
    virtual void Move(const int x, const int y) = 0;
    virtual void Print() = 0;
};

class Text : public Component
{
public:
    std::string m_content;

public:
    Text(const std::string content) : m_content(content) {}
    void Move(const int x, const int y)
    {
        m_x += x;
        m_y += y;
    }

    void Print()
    {
        std::cout << m_x << ", " << m_y << " - " << m_content << std::endl;
    }
};

class Image : public Component
{
public:
    std::string m_filepath;

public:
    Image(const std::string& path) : m_filepath(path) {}
    void Move(const int x, const int y)
    {
        m_x += x;
        m_y += y;
    }

    void Print()
    {
        std::cout << m_x << ", " << m_y << " - " << m_filepath << std::endl;
    }
};

class Graph : public Component
{
public:
    std::vector<std::pair<int, int>> m_vecData;

public:
    Graph(const std::vector<std::pair<int, int>>& vecData) : m_vecData(vecData){}
    void Move(const int x, const int y)
    {
        m_x += x;
        m_y += y;
    }

    void Print()
    {
        std::cout << m_x << ", " << m_y << " - " << std::endl;

        for (const auto& data : m_vecData)
        {
            std::cout << "[" << data.first << ", " << data.second << "]" << std::endl;
        }
    }
};

class Composite : public Component
{
private:
    std::vector<std::unique_ptr<Component>> vecComponent;

public:
    void Add(std::unique_ptr<Component>&& component)
    {
        vecComponent.emplace_back(std::move(component));
    }

    void Delete()
    {
        vecComponent.clear();
    }

    void Move(const int x, const int y)
    {
        for (auto& component : vecComponent)
        {
            component->Move(x, y);
        }
    }

    void Print()
    {
        std::cout << "-- Component --" << std::endl;
        for (auto& component : vecComponent)
        {
            component->Print();
        }
    }
};

int main()
{
    auto composite = std::make_unique<Composite>();
    {
        auto image = std::make_unique<Image>("Image");
        image->Move(2, 2);
        composite->Add(std::move(image));
        
        auto data = std::vector<std::pair<int, int>>{{1,1}, {2,2}, {3,3}};
        auto graph = std::make_unique<Graph>(data);
        graph->Move(2, 7);
        composite->Add(std::move(graph));
        
    }

    auto root = std::make_unique<Composite>();
    {
        root->Add(std::make_unique<Text>("title"));
        root->Add(std::move(composite));
    }

    root->Print();

    root->Move(-1, -1);
    std::cout << std::endl;
    root->Print();   

}

/*
output

-- Component --
0, 0 - title
-- Component --
2, 2 - Image
2, 7 -
[1, 1]
[2, 2]
[3, 3]

-- Component --
-1, -1 - title
-- Component --
1, 1 - Image
1, 6 -
[1, 1]
[2, 2]
[3, 3]


*/