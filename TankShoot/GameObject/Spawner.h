#pragma once
#include <vector>
#include <string>
#include <memory> // For std::shared_ptr (though not directly used in Spawner's raw pointers, good practice for related concepts)
#include "Enemy.h"
#include "MineTrap.h"    // Bao gồm các loại kẻ thù cụ thể
#include "TankEnemy.h"
#include "Plane.h"
#include "ArmoredTank.h"
#include "AirCraft.h"    // Cho trùm
#include "../Configuration/GameConfig.h"  // Cho kích thước màn hình và các hằng số khác
#include "ResourceIndexer.h"
#include <random>
#include <iostream>

class Spawner {
public:
    Spawner();
    ~Spawner() = default; // Hàm hủy mặc định là đủ vì không sở hữu thành viên được cấp phát động trực tiếp

    void init();
    void update(float deltaTime); // Dùng cho việc tạo lính theo thời gian (nếu có)

    // Phương thức factory để tạo một kẻ thù dựa trên tên loại của nó
    Enemy* createEnemy(const std::string& enemyType);

    // Tạo tập hợp kẻ thù ban đầu cho game
    std::vector<Enemy*> spawnInitialEnemies();

    bool canSpawnRegularEnemy(); // Thêm hàm này
    Enemy* spawnRandomRegularEnemy(); // Thêm hàm này
    void resetSpawnTimer();

private:
    // Các tham số cho việc tạo lính ngẫu nhiên theo thời gian của kẻ thù thông thường
    float currentSpawnTimer; // Bộ đếm thời gian cho lần tạo lính tiếp theo
    float spawnInterval;     // Khoảng thời gian giữa các lần tạo lính ngẫu nhiên
    int enemiesSpawnedCount; // Để theo dõi số lượng kẻ thù đã được tạo ra
    int maxEnemiesToSpawn;   // Số lượng kẻ thù tối đa được tạo ra bởi spawner (không bao gồm lính của trùm)
};