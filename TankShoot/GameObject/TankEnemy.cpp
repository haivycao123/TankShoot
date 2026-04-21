//Tuong tu voi ham shoot?
#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "Enemy.h"
#include "TankEnemy.h"
#include "../Configuration/GameConfig.h"

TankEnemy::TankEnemy()
// Gọi constructor của lớp Enemy cơ sở, truyền shared_ptr texture đã lấy được
    : Enemy(std::shared_ptr<sf::Texture>(DATA->getTexture("tank_enemy"), [](sf::Texture*) {})) // Thay "tank_enemy_texture" bằng tên texture thực tế của bạn
{
    // Các thiết lập riêng của TankEnemy
    sprite.setScale(TankEnemyScale); //Dat scale
    speed = TankEnemySpeed;
    hp = TankEnemyHP;
    shootCooldown = TankEnemyShootCooldown;
    shootTimer = 0.0f;
    type = "TankEnemy"; // Gán loại Enemy
}


void TankEnemy::move(float deltaTime) {
    position.y += speed * deltaTime;
    sprite.setPosition(position);
    if (position.y > screenHeight + getBounds().size.y / 2.0f) { //Ra khoi man hinh
        hp = 0;
    }
}

std::vector<Bullet*> TankEnemy::shoot() {
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
std::string TankEnemy::getType() {
    return type;
}