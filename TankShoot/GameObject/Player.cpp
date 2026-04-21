//Co hieu ung, am thanh khi su dung skill khong?
//Hàm shoot() tạo đạn
//Hàm useSkill() tạo đạn, hiệu ứng, playSound?... không xử lí trực tiếp Enemy, cần hàm xử lí
//Hàm takeDamage hiệu ứng playSound?
#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "Player.h"
#include "../Configuration/GameConfig.h"
#include "../ResourceManagement/ResourceManager.h" // Đảm bảo đã include để sử dụng DATA

Player::Player(std::string textureName)
    : hp(maxHp), // Khởi tạo hp
    // Đảm bảo 'texture' được khởi tạo trước 'sprite' trong danh sách này.
    texture(std::shared_ptr<sf::Texture>(DATA->getTexture(textureName), [](sf::Texture*) {})),
    sprite(*texture) // Khởi tạo sprite bằng cách truyền tham chiếu tới sf::Texture từ shared_ptr
{
 
    if (!texture) {
        std::cerr << "Error: Player texture '" << textureName << "' not loaded or is nullptr. Game may crash." << std::endl;
       
    }

    // Các thiết lập khác của sprite và player
    sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
    sprite.setScale(PlayerScale);
    position = PlayerStartPosition;
    sprite.setPosition(position);

    // Khởi tạo các biến khác
    shootTimer = 0.0f;
    skillTimer = 0.0f;
    isInvincible = false;
    invincibleTimer = 0.0f;
    
}

void Player::update(float deltaTime) {
    shootTimer = std::min(shootTimer + deltaTime, shootCooldown);
    skillTimer = std::min(skillTimer + deltaTime, skillCooldown);
    if (isInvincible) {
        invincibleTimer += deltaTime;
        if (invincibleTimer >= invincibleDuration) {
            isInvincible = false;
            invincibleTimer = 0.0f;
            sprite.setColor(sf::Color::White); //Tro lai binh thuong
        }
        else {
            static float blinkTimer = 0.0f; //Dung static de giu gia tri
            blinkTimer += deltaTime;
            if (blinkTimer > 0.1f) { //Nhap nhay chu ki 0.1s
                blinkTimer = 0.0f;
                sprite.setColor(sprite.getColor().a == 255 ? sf::Color(255, 255, 255, 150) : sf::Color::White); //255 la ro net, 150 la dang mo
            }
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::move(float deltaTime, int direction) {
    float newX = getPosition().x + direction * speed * deltaTime; //Vi tri moi, truc Ox
    float playerWidth = getBounds().size.x; //Lay chieu rong
    newX = std::clamp(newX, playerWidth / 2.0f, screenWidth - playerWidth / 2.0f); //Gioi han toa do x de khong ra khoi man hinh std::clamp(value, min, max)
    setPosition(newX, getPosition().y);
}

void Player::shoot(std::vector<Bullet*>& bullets) {
    if (shootTimer >= shootCooldown) {
        shootTimer = 0.0f;
        Bullet* bullet = new Bullet(
            "player_bullet", // Tên texture đạn của player (ví dụ "bullet")
            BulletType::Normal,
            sf::Vector2f(0, -1),
            BulletSpeed,
            NormalDamage
        );

        // Đặt vị trí đạn xuất phát từ đầu nòng player
        sf::Vector2f bulletPos = getPosition();
        bullet->setPosition(bulletPos.x, (bulletPos.y - sprite.getGlobalBounds().size.y / 2));

        bullets.push_back(bullet);
        //  Phát âm thanh bắn đạn
        snd->playSound("player_shoot"); // Giả sử bạn có sound "player_shoot.wav"
    }
     
    
}


void Player::useSkill(std::vector<Enemy*>& enemies, std::vector<ExplosionEffect*>& explosions) {
    if (isSkillReady()) {
        skillTimer = 0.0f;
        // THÊM: Phát âm thanh kích hoạt kỹ năng
        snd->playSound("skill_active"); // Giả sử bạn có sound "skill_activate.wav"

        // Xử lý damage cho tất cả kẻ thù
        for (Enemy* e : enemies) {
            explosions.push_back(new ExplosionEffect(e->getPosition()));
            if (e->isAlive()) {
                if (e->isBoss()) {
                    
                       AirCraft* boss = dynamic_cast<AirCraft*>(e);
                        if (boss && !boss->hasSpawnedFully()) continue; // Bỏ qua nếu chưa spawn
                    
                    e->takeDamage(30); // Kĩ năng gây 30hp cho Trùm
                }
                else {
                    e->takeDamage(1000); // Tiêu diệt mọi kẻ địch khác
                }
            }
        }
    }
}

void Player::takeDamage() {
    if (!isInvincible) {
        --hp;
        sprite.setColor(sf::Color::Red);
        if (isAlive()) {
            isInvincible = true;
            invincibleTimer = 0.0f;
        }
        // Phát âm thanh khi player bị hit
       snd->playSound("player_hit"); // Giả sử bạn có sound "player_hit.wav"
    }
}

bool Player::isAlive() const {
    return hp > 0;
}

bool Player::isSkillReady() const {
    return skillTimer >= skillCooldown;
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

void Player::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
    sprite.setPosition(position);
}

sf::Vector2f Player::getPosition() const {
    return position;
}

int Player::getHp() const {
    return hp;
}

float Player::getSkillCooldownTimer() const {
    return skillTimer;
}
void Player::setHp(int newHp) { // THÊM: Triển khai hàm setHp
    hp = newHp;
    if (hp > maxHp) hp = maxHp;
    if (hp < 0) hp = 0; // Đảm bảo HP không âm
    sprite.setColor(sf::Color::White); // Đặt lại màu bình thường nếu bị đỏ trước đó
    isInvincible = false; // Đảm bảo không bất tử khi reset HP
    invincibleTimer = 0.0f;
}