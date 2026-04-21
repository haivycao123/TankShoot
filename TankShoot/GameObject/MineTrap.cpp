#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "MineTrap.h"
#include "../Configuration/GameConfig.h"

MineTrap::MineTrap()
// Gọi constructor của lớp Enemy cơ sở, truyền shared_ptr texture đã lấy được
    : Enemy(std::shared_ptr<sf::Texture>(DATA->getTexture("mine_trap"), [](sf::Texture*) {})) // Ví dụ tên texture
{
    // Các thiết lập riêng của MineTrap
    sprite.setScale(MineTrapScale);
    speed = MineTrapSpeed;
    hp = MineTrapHP;
    type = "MineTrap"; // Gán loại
}

void MineTrap::move(float deltaTime) {
    position.y += speed * deltaTime;
    sprite.setPosition(position);
    if (position.y > screenHeight + getBounds().size.y / 2.0f) { //Ra khoi man hinh
        hp = 0;
    }
}

std::vector<Bullet*> MineTrap::shoot() {
    return {}; // Trả về vector rỗng
}

std::string MineTrap::getType() {
    return type;
}