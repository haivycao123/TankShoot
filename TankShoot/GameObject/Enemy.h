#ifndef Enemy_h
#define Enemy_h

#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector> // Cần thiết cho std::vector trong hàm shoot()
#include "../Configuration/GameConfig.h"
#include "../ResourceManagement/ResourceManager.h"
#include "Bullet.h"


class Enemy {
protected:
    std::shared_ptr<sf::Texture> texture; // Sử dụng shared_ptr vì các đối tượng dùng chung texture
    sf::Sprite sprite;
    sf::Vector2f position;
    float speed = 0.0f; // pixel/s
    int hp;
    float shootCooldown;
    float shootTimer = 0.0f;
    std::string type;

    bool isActive_ = true;     //  Cờ trạng thái hoạt động
    bool isDestroyed_ = false; //  Cờ trạng thái đã bị hủy 

    float hitEffectTimer; // Bộ đếm thời gian cho hiệu ứng đỏ, > 0 màu đỏ, <= 0 màu gốc


public:
    Enemy(const std::shared_ptr<sf::Texture>& tex);
    virtual ~Enemy() = default;

    // Các hàm này giờ là của Enemy
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window);

    virtual void move(float deltaTime) = 0;
    virtual std::vector<Bullet*> shoot() = 0; // Hàm thuần ảo

    virtual void takeDamage(int damage);
    bool isAlive() const; 

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }
    sf::Vector2f getPosition() const { return position; }
    int getHp() const { return hp; }

    void setPosition(float x, float y);
    void setSpeed(float newSpeed);

    virtual bool isBoss() { return false; };
    std::string getType();

protected:
    bool canShoot() const { return shootTimer >= shootCooldown; }
};

#endif