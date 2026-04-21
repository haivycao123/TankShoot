//Chinh dan lazer?
#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "Bullet.h"

Bullet::Bullet(std::string textureName, BulletType bulletType, sf::Vector2f dir, float spd, int dmg)
// Khởi tạo các biến thành viên trong danh sách khởi tạo
    : type(bulletType),
    direction(dir),
    speed(spd),
    damage(dmg),
    lazerWarningTime(LazerWarningTime),
    lazerTimer(0.0f),
    // 1. Khởi tạo 'texture' shared_ptr trước
    texture(std::shared_ptr<sf::Texture>(DATA->getTexture(textureName), [](sf::Texture*) {})),
    // 2. Sau đó, khởi tạo 'sprite' sử dụng 'texture' đã được khởi tạo
    // Lưu ý: Nếu DATA->getTexture(textureName) trả về nullptr,
    // thì dòng `sprite(*texture)` này sẽ gây crash.
    // Bạn cần đảm bảo ResourceManager luôn trả về một texture hợp lệ
    // (hoặc một texture mặc định/lỗi) để tránh lỗi này.
    sprite(*texture), // Sử dụng constructor sf::Sprite(const sf::Texture& texture)
    m_active(true),// KHỞI TẠO: Viên đạn bắt đầu ở trạng thái hoạt động
    // THÊM: Khởi tạo các biến thời gian sống của laser
    m_laserDuration(bulletType == BulletType::Laser ? 2.0f : 0.0f), // Nếu là laser, dùng LaserDuration từ GameConfig.h
    m_hitDelayTimer(0.0f), // Khởi tạo timer
    m_laserElapsedTime(0.0f) // Thời gian ban đầu là 0
{
    // Sau khi sprite đã được khởi tạo, bạn có thể thiết lập các thuộc tính khác
    if (texture) { // Kiểm tra texture hợp lệ (mặc dù đã dùng nó ở trên)
        sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
        // Không cần gọi sprite.setTexture(*texture) nữa vì đã được khởi tạo rồi
       
    }
    else {
        std::cerr << "Error: Bullet texture '" << textureName << "' not loaded (might have crashed earlier)." << std::endl;
        // Xử lý lỗi nếu texture không tải được (ví dụ: gán texture mặc định)
    }
}

void Bullet::update(float deltaTime) {
    if (!m_active) return;
    m_hitDelayTimer += deltaTime; // Luôn tăng timer này

    if (type == BulletType::Laser) {
        m_laserElapsedTime += deltaTime ;
    }
    else {
        position += direction * speed * deltaTime;
    }

    sprite.setPosition(position);

    // THÊM DÒNG DEBUG NÀY ĐỂ XEM GIÁ TRỊ CỦA TIMER
    std::cerr << "DEBUG: Laser Bullet Timer - Elapsed: " << m_laserElapsedTime
        << ", Duration: " << m_laserDuration
        << ", Alive: " << isAlive() << std::endl;

}


void Bullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Bullet::isOutOfBounds() const {
    return position.y > screenHeight + getBounds().size.y / 2.0f || position.x > screenWidth + getBounds().size.x / 2.0f || position.x < -sprite.getGlobalBounds().size.x / 2.0f;
}

// THÊM: Triển khai hàm markForRemoval()
void Bullet::markForRemoval() {
    m_active = false; // Đặt trạng thái không hoạt động
}

// Triển khai hàm isAlive()
bool Bullet::isAlive() const {
    if (type == BulletType::Laser) {
        // Laser còn sống nếu:
        // 1. Nó đang hoạt động (m_active)
        // 2. Thời gian đã trôi qua chưa vượt quá thời gian tồn tại tối đa (m_laserElapsedTime < m_laserDuration)
        // 3. Nó chưa ra khỏi màn hình (!isOutOfBounds())
        return m_active && (m_laserElapsedTime < m_laserDuration) && !isOutOfBounds();
    }
    // Các loại đạn khác chỉ sống nếu đang hoạt động và chưa ra khỏi màn hình
    return m_active && !isOutOfBounds();
}

void Bullet::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
    sprite.setPosition(position);
}

void Bullet::setSpeed(float newSpeed) {
    speed = newSpeed;
}
