#ifndef AirCraft_h
#define AirCraft_h

#include <SFML/Graphics.hpp> // Cần cho sf::RectangleShape và các thuộc tính đồ họa
#include "Enemy.h"           // Kế thừa Enemy
#include "Bullet.h"          // Cho std::vector<Bullet*> shoot()
#include <memory>  
#include "../ResourceManagement/SoundManager.h"
#include <cstdint> 
enum class BossFireType {
    NONE,
    SINGLE,
    TRIPLE,
    LAZER_WARNING, // Trạng thái cảnh báo laser
    LAZER_FIRE     // Trạng thái bắn laser
};

class AirCraft : public Enemy {
private:
    float fireTypeTimer; // Timer để chọn kiểu bắn ngẫu nhiên
    BossFireType pendingFire; // Kiểu bắn đang chờ thực hiện
    float lazerWarningTimer; // Timer cho cảnh báo laser
    sf::Sprite lazerWarningLine; // Đường cảnh báo laser

    float initialShootCooldown; // Tần suất bắn ban đầu
    float lowHPShootCooldown;   // Tần suất bắn khi HP thấp

    float spawnTimer = 0.f;
    bool hasSpawned = false;


public:
    AirCraft();
    ~AirCraft() = default;
    void move(float deltaTime) override;
    std::vector<Bullet*> shoot() override;
    std::string getType();
    void update(float deltaTime) override; // Cần override update để xử lý timer và trạng thái laser
    void draw(sf::RenderWindow& window) override; // Cần override draw để vẽ đường cảnh báo laser
    bool isBoss()  override { return true; }
    bool hasSpawnedFully() const;
};

#endif