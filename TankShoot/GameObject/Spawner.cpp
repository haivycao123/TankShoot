#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "Spawner.h"
 

Spawner::Spawner()
    : currentSpawnTimer(0.0f),
    spawnInterval(5.0f), // Khoảng thời gian mặc định cho kẻ thù mới (ví dụ: mỗi 5 giây)
    enemiesSpawnedCount(0),
    maxEnemiesToSpawn(1000) // Ví dụ: tạo tối đa 50 kẻ thù thông thường theo thời gian
{
    // Constructor
}

void Spawner::init() {
    currentSpawnTimer = 0.0f;
    enemiesSpawnedCount = 0;
    // Đặt lại các trạng thái khác của spawner nếu cần cho phiên game mới
}

// Hàm update này chủ yếu quản lý thời gian cho việc tạo kẻ thù thông thường
// Việc thêm kẻ thù vào danh sách của GSPlay sẽ do GSPlay quản lý hoặc một phương thức riêng
void Spawner::update(float deltaTime) {
    // Logic tạo kẻ thù ngẫu nhiên theo thời gian
    // Hiện tại, hàm này chỉ quản lý thời gian. GSPlay sẽ gọi createEnemy khi cần.
    // Nếu bạn muốn spawner tự động tạo và trả về kẻ thù, cần thay đổi cách nó hoạt động (ví dụ: trả về vector<Enemy*>)
    if (enemiesSpawnedCount < maxEnemiesToSpawn) {
        currentSpawnTimer += deltaTime;
        
    }
}

Enemy* Spawner::createEnemy(const std::string& enemyType) {
    if (enemyType == "MineTrap") {
        return new MineTrap();
    }
    else if (enemyType == "TankEnemy") {
        return new TankEnemy();
    }
    else if (enemyType == "ArmoredTank") {
        return new ArmoredTank();
    }
    else if (enemyType == "Plane") {
        return new Plane();
    }
    else if (enemyType == "AirCraft") { // Cho trùm
        return new AirCraft();
    }
    else {
        std::cerr << "Error: Unknown enemy " << enemyType << std::endl;
        return nullptr; // Trả về nullptr cho các loại không xác định
    }
}

std::vector<Enemy*> Spawner::spawnInitialEnemies() {
    std::vector<Enemy*> initialEnemies;
    std::random_device rd;
    std::mt19937 gen(rd());

    // Tạo trùm (AirCraft) đầu tiên
    Enemy* boss = createEnemy("AirCraft");
    if (boss) {
        boss->setPosition(AirCraftStartPosition.x, AirCraftStartPosition.y);
        initialEnemies.push_back(boss);
    }
    // Tạo một số kẻ thù thông thường ban đầu (ví dụ)
    for (int i = 0; i < 10; ++i) { // Tạo 3 kẻ thù ban đầu
        std::uniform_int_distribution<> type_distrib(0, 4); // 0:TankEnemy, 1:ArmoredTank, 2:Plane, 3,4:MineTrap
        std::string enemyType;
        int choice = type_distrib(gen);
        if (choice == 0) enemyType = "TankEnemy";
        else if (choice == 1) enemyType = "ArmoredTank";
        else  if (choice == 2) enemyType = "Plane";
        else enemyType = "MineTrap";

        Enemy* enemy = createEnemy(enemyType);
        if (enemy) {
            std::uniform_real_distribution<> x_pos_distrib(enemy->getBounds().size.x / 2.f, screenWidth - enemy->getBounds().size.x / 2.f);
            // Tạo kẻ thù ở phía trên màn hình, vị trí Y so le nhau
            if (enemyType == "Plane") {
                enemy->setPosition(x_pos_distrib(gen) * 1.0f, (screenHeight / 2)- 325.f );
            }
            else {
                enemy->setPosition(x_pos_distrib(gen) * 1.0f, -100.0f - (static_cast<float>(i) * 70.0f));
            }
            initialEnemies.push_back(enemy);
            enemiesSpawnedCount++; // Theo dõi số lượng kẻ thù đã được tạo
        }
    }

    return initialEnemies;
}
bool Spawner::canSpawnRegularEnemy() {
    if (enemiesSpawnedCount < maxEnemiesToSpawn && currentSpawnTimer >= spawnInterval) {
        return true;
    }
    return false;
}

Enemy* Spawner::spawnRandomRegularEnemy() {
    if (enemiesSpawnedCount >= maxEnemiesToSpawn) return nullptr; // Đảm bảo không vượt quá giới hạn

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> type_distrib(0, 3); // 0:TankEnemy, 1:ArmoredTank, 2:Plane, 3:MineTrap
    std::string enemyType;
    int choice = type_distrib(gen);
    if (choice == 0) enemyType = "TankEnemy";
    else if (choice == 1) enemyType = "ArmoredTank";
    else if (choice == 2) enemyType = "Plane";
    else enemyType = "MineTrap";

    Enemy* enemy = createEnemy(enemyType);
    if (enemy) {
        std::uniform_real_distribution<> x_pos_distrib(enemy->getBounds().size.x / 2.f, screenWidth - enemy->getBounds().size.x / 2.f);
        if (enemyType == "Plane") {
            enemy->setPosition(x_pos_distrib(gen), (screenHeight/2) - 325.f);
        }
        else {
            enemy->setPosition(x_pos_distrib(gen), -100.0f); // Sinh ở trên màn hình
        }
        enemiesSpawnedCount++;
    }
    currentSpawnTimer = 0.0f; // Reset timer sau khi tạo
    return enemy;
}
void Spawner::resetSpawnTimer() {
    currentSpawnTimer = 0.0f;
}
