#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "AirCraft.h"
#include "../Configuration/GameConfig.h"
#include "../ResourceManagement/ResourceManager.h"
#include <random> // Để tạo số ngẫu nhiên

// Sửa đổi constructor
AirCraft::AirCraft()
    : Enemy(std::shared_ptr<sf::Texture>(DATA->getTexture("aircraft"), [](sf::Texture*) {})), // Thay "aircraft_texture" bằng tên texture thực tế của bạn
    fireTypeTimer(0.0f),
    pendingFire(BossFireType::NONE),
    lazerWarningTimer(0.0f),
    lazerWarningLine(*DATA->GetDefaultTexture())
{
    sprite.setScale(AirCraftScale);
    speed = AirCraftSpeed;
    hp = AirCraftHP; // 150 HP
    initialShootCooldown = AirCraftShootCooldown; // Tần suất bắn ban đầu
    lowHPShootCooldown = AirCraftShootCooldown * 0.5f; // Tăng tần suất (ví dụ: giảm cooldown còn một nửa)
    shootCooldown = initialShootCooldown; // Bắt đầu với tần suất ban đầu
    shootTimer = 0.0f;
    type = "AirCraft"; // Gán loại Enemy

    // Thiết lập đường cảnh báo laser
    sf::Texture* lzTexture = DATA->getTexture("lazer_warning");

    if (lzTexture && lzTexture != DATA->GetDefaultTexture()) {
        lazerWarningLine.setTexture(*lzTexture, true); // ✅ Cờ `true` ép cập nhật lại bounds
        lazerWarningLine.setScale({
            1.f,
            1.f
            });
        lazerWarningLine.setPosition({ screenWidth / 2.f, 0.f });
        lazerWarningLine.setColor(sf::Color::White);
    }
    else {
        std::cerr << "Error: Load texture fail." << std::endl;
    }
    //lazerWarningLine.setSize(sf::Vector2f(5.f, screenHeight)); // Chiều rộng 5px, chiều cao toàn màn hình
    //lazerWarningLine.setFillColor(sf::Color::Red);
    //lazerWarningLine.setOrigin({ lazerWarningLine.getSize().x / 2.f, 0.f }); // Đặt gốc ở giữa phía trên
    //lazerWarningLine.setPosition({ screenWidth / 2.f, 0.f }); // Vị trí ban đầu
}

void AirCraft::move(float deltaTime) {
        if (!hasSpawned) {
            spawnTimer += deltaTime;

            // Nếu chưa đến 2 phút, vẫn ở ngoài màn hình
            if (spawnTimer < TimeAirCraftAppear) {
                position = sf::Vector2f(screenWidth / 2.f, -200.f); // Ngoài màn hình
            }
            else {
                // Sau 2 phút thì bắt đầu di chuyển xuống
                float targetY = getBounds().size.y / 2.f + 50.f;
                if (position.y < targetY) {
                    position.y += AirCraftSpeed * deltaTime; // Tốc độ di chuyển xuống
                }
                else {
                    position.y = targetY; // Giữ đúng vị trí
                    hasSpawned = true;
                }
            }
        }

        sprite.setPosition(position);
}

void AirCraft::update(float deltaTime) {
    Enemy::update(deltaTime); // Gọi update của lớp cha để cập nhật shootTimer
    if (!hasSpawned) return;

    // Kiểm tra HP để điều chỉnh tần suất bắn
    if (hp <= 45 && shootCooldown != lowHPShootCooldown) { // 30% của 150 HP là 45
        shootCooldown = lowHPShootCooldown;
        // Có thể thêm hiệu ứng âm thanh hoặc hình ảnh khi boss chuyển trạng thái
    }

    // Logic bắn laser
    if (pendingFire == BossFireType::LAZER_WARNING) { // Kiểm tra trạng thái cảnh báo laser
        lazerWarningTimer += deltaTime; // Tăng timer cảnh báo
        // Tạo hiệu ứng nhấp nháy: thay đổi alpha dựa vào sin sóng
        float blinkSpeed = 8.f; // tốc độ nhấp nháy
        float alpha = (std::sin(lazerWarningTimer * blinkSpeed) * 0.5f + 0.5f) * 255;
        lazerWarningLine.setColor(sf::Color(255, 255, 255, static_cast<uint8_t>(alpha)));

        if (lazerWarningTimer >= LazerWarningTime) {
            pendingFire = BossFireType::LAZER_FIRE;
            lazerWarningTimer = 0.0f;
            // Reset màu về trắng khi bắn
            lazerWarningLine.setColor(sf::Color::White);
        }
        if (lazerWarningTimer >= LazerWarningTime) { // Nếu thời gian cảnh báo đã hết
            pendingFire = BossFireType::LAZER_FIRE; // Chuyển sang trạng thái bắn laser
            lazerWarningTimer = 0.0f; // Reset timer cảnh báo
        }
    }
    // Chỉ chọn kiểu bắn mới khi không có kiểu bắn nào đang chờ xử lý và shootTimer đã hết cooldown
    else if (pendingFire == BossFireType::NONE && shootTimer >= shootCooldown) { // Điều kiện kiểm tra shootTimer và pendingFire
        std::random_device rd; // Khởi tạo bộ tạo số ngẫu nhiên
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 3); // 1: single, 2: triple, 3: laser

        int firechoice = distrib(gen); // Chọn ngẫu nhiên kiểu bắn

        if (firechoice == 1) {
            pendingFire = BossFireType::SINGLE; // Đặt kiểu bắn là single
        }
        else if (firechoice == 2) {
            pendingFire = BossFireType::TRIPLE; // Đặt kiểu bắn là triple
        }
        else { // firechoice == 3
            pendingFire = BossFireType::LAZER_WARNING; // Đặt kiểu bắn là cảnh báo laser
            // Đặt vị trí cảnh báo laser ngẫu nhiên (hoặc cố định)
            std::uniform_real_distribution<float> x_distrib(getBounds().size.x / 2.f, screenWidth - getBounds().size.x / 2.f); // Phân phối ngẫu nhiên cho vị trí X
            lazerWarningLine.setPosition({ x_distrib(gen), 0.f }); // Đặt vị trí đường cảnh báo
        }
        shootTimer = 0.0f; // reset shoottimer sau khi chọn kiểu bắn


    }
}

std::vector<Bullet*> AirCraft::shoot() {
    std::vector<Bullet*> newBullets; // Vector tạm thời để chứa đạn mới tạo ra trong lần bắn này
    if (this->getPosition().y < 0) { // Nếu enemy vẫn còn ngoài màn hình
        return newBullets; // Không bắn đạn
    }
    sf::Vector2f startPos = position;

    if (pendingFire == BossFireType::SINGLE) {
        Bullet* bullet = new Bullet("boss_bullet", BulletType::Normal, sf::Vector2f(0, 1), 200.0f, 2);
        bullet->setFiredByBoss();
        bullet->setPosition(startPos.x, startPos.y + sprite.getGlobalBounds().size.y / 2);
        newBullets.push_back(bullet);
        pendingFire = BossFireType::NONE;
    }
    else if (pendingFire == BossFireType::TRIPLE) {
        std::vector<sf::Vector2f> dirs = {
            sf::Vector2f(-0.5f, 1.f),
            sf::Vector2f(0.f, 1.f),
            sf::Vector2f(0.5f, 1.f)
        };
        for (auto& dir : dirs) {
            Bullet* bullet = new Bullet("boss_bullet", BulletType::Normal, dir, 200.0f, 2);
            bullet->setFiredByBoss();
            bullet->setPosition(startPos.x, startPos.y + sprite.getGlobalBounds().size.y / 2);
            newBullets.push_back(bullet);
        }
        pendingFire = BossFireType::NONE;
    }
    else if (pendingFire == BossFireType::LAZER_FIRE) {
        Bullet* lazer = new Bullet("lazer", BulletType::Laser, sf::Vector2f(0, 1), 0.0f, 5);
        lazer->setFiredByBoss();
       // lazer->setLifetime(0);
        /*lazer->setScale({ 0.5f, 0.5f });*/
        lazer->setPosition(lazerWarningLine.getPosition().x, lazerWarningLine.getPosition().y + 350.0f);
        newBullets.push_back(lazer);
        snd->playSound("lazer");
        pendingFire = BossFireType::NONE;
    }
    //pendingFire = BossFireType::NONE;
    return newBullets; // Trả về các viên đạn mới được tạo
   
}

void AirCraft::draw(sf::RenderWindow& window) {
    Enemy::draw(window); // Vẽ sprite của boss
    if (pendingFire == BossFireType::LAZER_WARNING) {
        window.draw(lazerWarningLine); // Vẽ đường cảnh báo laser
    }
}

std::string AirCraft::getType() {
    return type;
}
bool AirCraft::hasSpawnedFully() const {
    return hasSpawned;
}