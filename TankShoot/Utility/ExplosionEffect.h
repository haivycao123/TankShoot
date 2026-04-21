#ifndef ExplosionEffect_h
#define ExplosionEffect_h

#include <SFML/Graphics.hpp>
#include <memory> // Cho std::shared_ptr
#include "../ResourceManagement/ResourceManager.h" // Để lấy texture
#include "../Configuration/GameConfig.h" // Nếu cần hằng số (ví dụ thời gian nổ)
#include <iostream> // Để sử dụng std::cerr
 
class ExplosionEffect {
private:
    std::shared_ptr<sf::Texture> texture; //  Texture riêng 
    sf::Sprite sprite;                     //  Sprite riêng 
    sf::Vector2f position;                 // Vị trí riêng 
    float m_duration;    // Tổng thời gian hiệu ứng tồn tại
    float m_elapsedTime; // Thời gian đã trôi qua

public:
    ExplosionEffect(const sf::Vector2f& position);
    ~ExplosionEffect() = default;

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isAlive() const;

    void setPosition(float x, float y) { // setPosition 
        position.x = x;
        position.y = y;
        sprite.setPosition(position);
    }
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); } //  getBounds 
};

#endif