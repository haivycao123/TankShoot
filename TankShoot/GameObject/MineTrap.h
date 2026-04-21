#ifndef MineTrap_h
#define MineTrap_h

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <memory>
class MineTrap : public Enemy {
public:
    MineTrap();
    ~MineTrap() = default;
    void move(float deltaTime) override; //Di chuyen thang
    std::vector<Bullet*> shoot() override;
    std::string getType();
};

#endif