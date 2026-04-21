#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "ExplosionEffect.h"


ExplosionEffect::ExplosionEffect(const sf::Vector2f& position)
// KHỞI TẠO: Texture, Sprite và vị trí riêng 
    : texture(std::shared_ptr<sf::Texture>(DATA->getTexture("explosion"), [](sf::Texture*) {})),
    sprite(*texture),
    position(position),
    m_duration(0.5f), // Thời gian tồn tại của hiệu ứng nổ
    m_elapsedTime(0.0f)
{
    if (texture) {
        sprite.setOrigin(sf::Vector2f(texture->getSize()) / 2.f); // Đặt gốc ở giữa sprite
        sprite.setScale({ 1.0f, 1.0f }); // Scale hiệu ứng nổ
    }
    else {
        std::cerr << "Error: Cannot upload" << std::endl;
    }
    sprite.setPosition(position); // Đặt vị trí sprite ban đầu
}

void ExplosionEffect::update(float deltaTime) {
    m_elapsedTime += deltaTime;
    // Nếu là animation, cập nhật frame ở đây
    // Nếu hết thời gian, hiệu ứng sẽ không còn sống
}

void ExplosionEffect::draw(sf::RenderWindow& window) {
    if (isAlive()) { // Chỉ vẽ nếu còn sống
        window.draw(sprite);
    }
}

bool ExplosionEffect::isAlive() const {
    return m_elapsedTime < m_duration; // Hiệu ứng còn sống nếu chưa hết thời gian
}