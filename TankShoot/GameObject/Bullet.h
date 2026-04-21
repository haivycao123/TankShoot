#ifndef Bullet_h
#define Bullet_h

#include <SFML/Graphics.hpp>
#include "../Configuration/GameConfig.h"
#include <memory>
#include "../ResourceManagement/ResourceManager.h"
#include <iostream>

enum class BulletType { Normal, Laser, Fan };

class Bullet {
private:
    std::shared_ptr<sf::Texture> texture; //Dung shared_ptr vi cac bullet/explosion dung chung texture
    sf::Sprite sprite;
    sf::Vector2f position;
    float speed = BulletSpeed;
    int damage = 1;
    sf::Vector2f direction; // (0,-1) player ban len, (0,1) enemy ban xuong
    BulletType type;
    float lazerWarningTime = LazerWarningTime;
    float lazerTimer = 0.0f;
    bool m_active; // THÊM: Biến này để theo dõi trạng thái hoạt động của đạn
    // THÊM: Các biến cho thời gian sống của laser
    float m_laserDuration;    // Tổng thời gian laser tồn tại (ví dụ 2 giây)
    float m_laserElapsedTime; // Thời gian đã trôi qua kể từ khi laser được tạo
    bool isFiredByBoss_ = false;

    float m_hitDelayTimer;
    

public:
    Bullet(std::string textureName, BulletType bulletType, sf::Vector2f dir, float spd, int dmg);
    virtual ~Bullet() = default;
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOutOfBounds() const;

    int getDamage() const { return damage; }
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); } //Tra ve thong tin vi tri, kich thuoc de xu ly va cham
    sf::Vector2f getPosition() const { return position; };

    void setPosition(float x, float y);
    void setSpeed(float newSpeed);

    bool isAlive() const;
    void markForRemoval();

    sf::Vector2f getDirection() { return direction; }

    bool getIsFiredByBoss() const { return isFiredByBoss_; }
    void setFiredByBoss() { isFiredByBoss_ = true; }

    float getHitDelayTimer() {
        return m_hitDelayTimer;
    }
    void setScale(const sf::Vector2f& scale) { sprite.setScale(scale); }
};

#endif