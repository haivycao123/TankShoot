#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "Enemy.h"

Enemy::Enemy(const std::shared_ptr<sf::Texture>& tex)
    : texture(tex),
    sprite(*texture),
    hp(1), // Giá trị HP mặc định, sẽ được ghi đè ở lớp con
    shootCooldown(0.0f),
    shootTimer(0.0f),
    isActive_(true),     
    isDestroyed_(false),  
    hitEffectTimer(0.0f)
{
    // Đảm bảo texture hợp lệ. Nếu không, sử dụng texture mặc định.
    if (!texture) {
        texture = std::shared_ptr<sf::Texture>(DATA->GetDefaultTexture(), [](sf::Texture*) {});
        sprite.setTexture(*texture); // Gán texture mặc định cho sprite
    }
    sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
}


void Enemy::update(float deltaTime) {
    if (!isAlive()) return; // Vẫn kiểm tra sống/chết
    move(deltaTime);
    shootTimer = std::min(shootTimer + deltaTime, shootCooldown);
    // Cập nhật hiệu ứng màu đỏ
    if (hitEffectTimer > 0) {
        hitEffectTimer -= deltaTime;
        // Nếu timer vẫn > 0, giữ màu đỏ. Ngược lại, đặt lại màu trắng (hoặc màu gốc của texture).
        // (Nếu sprite ban đầu của bạn không phải màu trắng, hãy đảm bảo texture của nó hiển thị màu gốc bạn muốn)
        sprite.setColor(sf::Color::Red);
    }
    else {
        sprite.setColor(sf::Color::White); // Trở lại màu gốc của texture (mặc định là trắng)
    }
}

std::string Enemy::getType() {
    return this->type;
}
void Enemy::draw(sf::RenderWindow& window) {
    if (isActive_ && !isDestroyed_) { //Kiểm tra isActive_ và isDestroyed_ 
        window.draw(sprite);
    }
}

void Enemy::takeDamage(int damage) {
    hp -= damage;
    hitEffectTimer = ENEMY_HIT_EFFECT_DURATION; // Kích hoạt hiệu ứng đỏ
    if (hp <= 0) {
        hp = 0; // Đảm bảo HP không âm
        isActive_ = false;     //  Đánh dấu không hoạt động 
        isDestroyed_ = true;   //  Đánh dấu đã bị hủy [cite: 1, 1]
    }
}


void Enemy::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
    sprite.setPosition(position);
}

void Enemy::setSpeed(float newSpeed) {
    speed = newSpeed;
}
bool Enemy::isAlive() const {
    // Hàm isAlive() kiểm tra đầy đủ điều kiện sống 
    return hp > 0 && isActive_ && !isDestroyed_;
}