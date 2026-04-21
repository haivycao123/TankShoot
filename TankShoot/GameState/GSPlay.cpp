#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "GSPlay.h"

// Trong GSPlay.cpp
GSPlay::GSPlay() : m_isWin(false), m_isLose(false), m_PlayBackground(*DATA->GetDefaultTexture()),
m_Player("player") // Dòng này khởi tạo m_Player bằng constructor mới của nó
{
}
GSPlay::~GSPlay() {
    for (auto enemy : m_Enemies) delete enemy;
    for (auto bullet : m_Bullets) delete bullet;
    for (auto exp : m_Explosions) delete exp;
}

void GSPlay::Exit() {
    if (m_pauseButton != nullptr) {
        delete m_pauseButton;
        m_pauseButton = nullptr;
    }
}

void GSPlay::Pause() {}

void GSPlay::Resume() {
    if (m_pauseButton == nullptr) {
        m_pauseButton = new GameButton();
        m_pauseButton->Init("pause");
        m_pauseButton->setSize(sf::Vector2f(50.f, 50.f));
        m_pauseButton->setOrigin(m_pauseButton->getSize() / 2.f);
        m_pauseButton->setPosition({ screenWidth - 40.f, 40.f });
        m_pauseButton->setOnClick([]() {
            GSM->PushState(StateTypes::PAUSE);
            });
    }
}

void GSPlay::Init() {

    
    // Reset trạng thái
    m_Enemies.clear();
    m_Bullets.clear();
    m_Explosions.clear();
    m_isWin = false;
    m_isLose = false;

    // Khởi tạo Player
    m_Player.setPosition(PlayerStartPosition.x, PlayerStartPosition.y);
    m_Player.setHp(m_Player.getMaxHp()); // THÊM DÒNG NÀY ĐỂ ĐẢM BẢO PLAYER CÓ ĐỦ HP KHI BẮT ĐẦU VÁN MỚI

    // Gọi Spawner sinh enemy ban đầu
    m_Spawner.init();
    m_Enemies = m_Spawner.spawnInitialEnemies();

    // UI
    m_UI.init(&m_Player);

    // THIẾT LẬP BACKGROUND THẬT CHO MÀN CHƠI
    sf::Texture* bgTexture = DATA->getTexture("background");

    if (bgTexture && bgTexture != DATA->GetDefaultTexture()) {
        m_PlayBackground.setTexture(*bgTexture, true); // ✅ Cờ `true` ép cập nhật lại bounds
        m_PlayBackground.setScale({
            (float)screenWidth / bgTexture->getSize().x,
            (float)screenHeight / bgTexture->getSize().y
            });
        m_PlayBackground.setPosition({ 0.f, 0.f });
        m_PlayBackground.setColor(sf::Color::White);
    }
    else {
        std::cerr << "Error: Load texture fail." << std::endl;
    }

    // Nhạc nền

    snd->loadMusic("background");
    snd->playMusic("background");

    // Khởi tạo nút tạm dừng
    m_pauseButton = new GameButton();
    m_pauseButton->Init("pause"); 
    m_pauseButton->setSize(sf::Vector2f(50.f, 50.f));
    m_pauseButton->setOrigin(m_pauseButton->getSize() / 2.f);
    m_pauseButton->setPosition({ screenWidth - 40.f, 40.f });
    m_pauseButton->setOnClick([]() {
        // Khi nhấn nút, đẩy trạng thái PAUSE lên trên
        GSM->PushState(StateTypes::PAUSE);
        });
}

void GSPlay::Update(float dt) {
    if (m_isWin || m_isLose) return;
    // Cập nhật nút tạm dừng
    m_pauseButton->Update(dt);

    // Kiểm tra nhấn phím ESC
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        GSM->PushState(StateTypes::PAUSE);
    }
    // --- Xử lý Input của Player ---

   // Di chuyển sang trái/phải
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        m_Player.move(dt, -3); // -1 cho di chuyển sang trái
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        m_Player.move(dt, 3); // 1 cho di chuyển sang phải
    }

    // Bắn đạn thường (Phím cách hoặc Chuột trái)
    // Cần một cờ để tránh bắn liên tục khi giữ phím
    static bool spacePressed = false;
    static bool mouseLeftPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        if (!spacePressed) {
            // Kiểm tra cooldown của Player trước khi bắn
            // Player::shoot đã tự kiểm tra cooldown bên trong
            m_Player.shoot(m_Bullets);
            spacePressed = true;
        }
    }
    else {
        spacePressed = false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (!mouseLeftPressed) {
            m_Player.shoot(m_Bullets);
            mouseLeftPressed = true;
        }
    }
    else {
        mouseLeftPressed = false;
    }

    // Sử dụng kĩ năng (Phím Enter hoặc Chuột phải)
    static bool enterPressed = false;
    static bool mouseRightPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
        if (!enterPressed) {
            m_Player.useSkill(m_Enemies, m_Explosions); // useSkill đã tự kiểm tra cooldown bên trong
            enterPressed = true;
        }
    }
    else {
        enterPressed = false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        if (!mouseRightPressed) {
            m_Player.useSkill(m_Enemies, m_Explosions);
            mouseRightPressed = true;
        }
    }
    else {
        mouseRightPressed = false;
    }


    m_Player.update(dt);
    m_Spawner.update(dt);

    // LOGIC TẠO KẺ THÙ THÔNG THƯỜNG LIÊN TỤC
    if (m_Spawner.canSpawnRegularEnemy()) {
        Enemy* newEnemy = m_Spawner.spawnRandomRegularEnemy();
        if (newEnemy) {
            m_Enemies.push_back(newEnemy);
            m_Spawner.resetSpawnTimer();
        }
    }

    // Cập nhật và thu thập đạn từ Player
    // Hàm shoot của Player cần truyền m_Bullets vào
   // m_Player.shoot(m_Bullets); // Đảm bảo Player::shoot() nhận std::vector<Bullet*>&

    // Cập nhật enemy và thu thập đạn từ enemy
    for (auto enemy : m_Enemies) {
        enemy->update(dt);
        // Thu thập đạn từ kẻ thù
        std::vector<Bullet*> enemyNewBullets = enemy->shoot();
        m_Bullets.insert(m_Bullets.end(), enemyNewBullets.begin(), enemyNewBullets.end());
    }

    for (auto bullet : m_Bullets) {
        bullet->update(dt);
    }

    // Kiểm tra va chạm
    CollisionManager::checkBulletEnemyCollision(m_Bullets, m_Enemies, m_Explosions);
    CollisionManager::checkEnemyPlayerCollision(m_Enemies, m_Player, m_Explosions);
    CollisionManager::checkBulletPlayerCollision(m_Bullets, m_Player, m_Explosions);
    CollisionManager::checkBulletBulletCollision(m_Bullets, m_Explosions);
    // Xoá đạn/enemy chết
    m_Enemies.erase(std::remove_if(m_Enemies.begin(), m_Enemies.end(), [](Enemy* e) {
        bool dead = !e->isAlive();
        if (dead) delete e; // Giải phóng bộ nhớ của enemy đã chết
        return dead;
        }), m_Enemies.end());

    m_Bullets.erase(std::remove_if(m_Bullets.begin(), m_Bullets.end(), [](Bullet* b) {
        bool dead = !b->isAlive();
        if (dead) delete b; // Giải phóng bộ nhớ của bullet đã chết
        return dead;
        }), m_Bullets.end());

    // Update Explosion
    for (auto exp : m_Explosions) exp->update(dt);
    m_Explosions.erase(std::remove_if(m_Explosions.begin(), m_Explosions.end(), [](ExplosionEffect* e) {
        bool dead = !e->isAlive();
        if (dead) delete e; // Giải phóng bộ nhớ của hiệu ứng nổ đã kết thúc
        return dead;
        }), m_Explosions.end());

    // Logic sinh quái phụ từ Trùm khi HP thấp (trong GSPlay)
    // Tìm AirCraft trong danh sách m_Enemies
    AirCraft* boss = nullptr;
    for (auto enemy : m_Enemies) {
        if (enemy->getType() == "AirCraft") {
            boss = static_cast<AirCraft*>(enemy);
            break;
        }
    }

    if (boss && boss->getHp() <= 45) { // 30% HP của 150 là 45
        // Logic sinh quái phụ ngẫu nhiên
        // Bạn cần thêm hàm vào Spawner để sinh quái theo yêu cầu
        // Ví dụ: m_Spawner.spawnRandomSubEnemy(boss->getPosition().x, boss->getPosition().y);
        // Hoặc trực tiếp tạo ở đây nếu Spawner chưa có hàm đó
        static float spawnSubEnemyTimer = 0.0f;
        const float spawnSubEnemyCooldown = 5.0f; // Tần suất sinh quái phụ (ví dụ 5 giây)
        spawnSubEnemyTimer += dt;

        if (spawnSubEnemyTimer >= spawnSubEnemyCooldown) {
            spawnSubEnemyTimer = 0.0f;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(1, 3); // 1: TankEnemy, 2: ArmoredTank, 3: Plane

            Enemy* newSubEnemy = nullptr;
            int enemyChoice = distrib(gen);

            if (enemyChoice == 1) {
                newSubEnemy = new TankEnemy();
            }
            else if (enemyChoice == 2) {
                newSubEnemy = new ArmoredTank();
            }
            else { // enemyChoice == 3
                newSubEnemy = new Plane();
            }

            if (newSubEnemy) {
                // Máy bay sẽ ở vị trí thấp hơn tàu sân bay.
                // Đặt vị trí xuất hiện của quái phụ gần boss nhưng thấp hơn
                newSubEnemy->setPosition(boss->getPosition().x + (distrib(gen) % 100 - 50), boss->getPosition().y + boss->getBounds().size.y / 2 + 50);
                m_Enemies.push_back(newSubEnemy);
            }
        }
    }

    // Kiểm tra win/lose
    m_isWin = true; // Giả sử thắng cho đến khi tìm thấy boss còn sống
    for (auto enemy : m_Enemies) {
        if (enemy->getType() == "AirCraft" && enemy->isAlive()) {
            m_isWin = false; // Boss vẫn còn sống, chưa thắng
            break;
        }
    }
    if (m_isWin && !m_isLose) { // Chỉ kích hoạt khi thực sự thắng và chưa thua
        g_isWin = true;
        snd->playSound("win");
        // Chuyển trạng thái sang End Game
        GSM->ChangeState(StateTypes::END); // Ví dụ: Chuyển sang màn hình kết thúc
    }


    if (!m_Player.isAlive()) {
        if (!m_isLose) { // Chỉ kích hoạt khi thực sự thua và chưa thắng
            m_isLose = true;
            g_isWin = false;
            snd->playSound("lose");
            // Chuyển trạng thái sang End Game
            GSM->ChangeState(StateTypes::END); // Ví dụ: Chuyển sang màn hình kết thúc
        }
    }

    // UI update
    m_UI.update(dt);
}

void GSPlay::Render(sf::RenderWindow* window) {

    // THÊM: Vẽ background màn chơi đầu tiên
   window->draw(m_PlayBackground);


    m_Player.draw(*window);

    for (auto enemy : m_Enemies) enemy->draw(*window);
    for (auto bullet : m_Bullets) bullet->draw(*window);
    for (auto exp : m_Explosions) exp->draw(*window);
   
    m_UI.draw(window);

    m_pauseButton->Render(window);

    


    // Có thể vẽ thông báo win/lose ở đây nếu cần
}
