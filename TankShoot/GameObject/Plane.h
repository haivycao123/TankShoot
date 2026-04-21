#ifndef Plane_h
#define Plane_h

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <memory>

class Plane : public Enemy {
private:
    float direction = 1.0f; //-1 la trai, +1 la phai

public:
    Plane();
    ~Plane() = default;
    void move(float deltaTime) override;
    std::vector<Bullet*> shoot() override;
    std::string getType();
};

#endif