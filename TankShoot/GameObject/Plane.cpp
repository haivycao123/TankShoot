//Ham shoot?
#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "Plane.h"
#include "../Configuration/GameConfig.h"

Plane::Plane()
// Gọi constructor của lớp Enemy cơ sở, truyền shared_ptr texture đã lấy được
    : Enemy(std::shared_ptr<sf::Texture>(DATA->getTexture("plane"), [](sf::Texture*) {})) // Thay "plane_texture" bằng tên texture thực tế của bạn
{
    // Các thiết lập riêng của Plane
    sprite.setScale(PlaneScale); //Dat scale
    speed = PlaneSpeed;
    hp = PlaneHP;
    shootCooldown = PlaneShootCooldown;
    shootTimer = 0.0f;
    type = "Plane"; // Gán loại Enemy
}

void Plane::move(float deltaTime) {
    position.x += direction * speed * deltaTime; //Di chuyen qua phai
    if (position.x <= getBounds().size.x / 2.0f || position.x >= screenWidth - getBounds().size.x) {
        direction *= -1.0f;
    }
    sprite.setPosition(position);
}


std::vector<Bullet*> Plane::shoot() {
    std::vector<Bullet*> newBullets; // Vector tạm thời để chứa đạn mới tạo ra trong lần bắn này
    if (this->getPosition().y < 0) { // Nếu enemy vẫn còn ngoài màn hình
        return newBullets; // Không bắn đạn
    }
    if (shootTimer >= shootCooldown) {
        shootTimer = 0.0;
        Bullet* bullet = new Bullet("enemy_bullet", BulletType::Normal, { 0.f, 1.f }, BulletSpeed, 1);
        bullet->setPosition(position.x, position.y + sprite.getGlobalBounds().size.y / 2);
        newBullets.push_back(bullet);
    }
    // Trả về các viên đạn mới được tạo trong lần bắn này
    return newBullets;
}
std::string Plane::getType() {
    return type;
}