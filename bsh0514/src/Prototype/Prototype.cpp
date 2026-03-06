#include "Prototype.h"

int Prototype() 
{
    PrototypeRegistry registry;
    registry.Register("red_circle", std::make_unique<Circle>("red", 10.0));
    registry.Register("tri", std::make_unique<Polygon>("triangle", std::vector<int>{1,2,3}));

    // 1) Circle
    auto c1 = registry.Create("red_circle");
    auto c2 = registry.Create("red_circle");
    c1->Draw();
    c2->Draw();

    // 2) Polygon
    auto p1 = registry.Create("tri");
    auto p2 = registry.Create("tri");

    auto* poly1 = dynamic_cast<Polygon*>(p1.get());
    if (poly1) poly1->PushPoint(99);

    p1->Draw(); // tri points={1,2,3,99}
    p2->Draw(); // tri points={1,2,3} - p1과 p2는 독립된 객체이므로 p1의 변경이 p2에 영향 없음

    return 0;
}