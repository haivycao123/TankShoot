#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "CollisionManager.h"
void CollisionManager::checkBulletEnemyCollision(std::vector<Bullet*>& bullets, std::vector<Enemy*>& enemies, std::vector<ExplosionEffect*>& explosions) {
    // Duyệt qua đạn và kẻ thù để kiểm tra va chạm
    // (Thay vì xóa trực tiếp trong vòng lặp, chúng ta chỉ đánh dấu)
    for (Bullet* bullet : bullets) { // Duyệt bằng range-based for hoặc iterator an toàn hơn
        if (!bullet->isAlive()) continue; // Bỏ qua đạn đã được đánh dấu không hoạt động
        if (bullet->getDirection().y > 0) {
            continue;
        }
        for (Enemy* enemy : enemies) {
            if (!enemy->isAlive()) continue; // Bỏ qua kẻ thù đã chết
            if (enemy->getType() == "AirCraft") {
                AirCraft* boss = dynamic_cast<AirCraft*>(enemy);
                if (boss && !boss->hasSpawnedFully()) continue; // Bỏ qua nếu chưa spawn
            }
            if (bullet->getHitDelayTimer() >= HIT_DELAY && bullet->getBounds().findIntersection(enemy->getBounds())) {
                enemy->takeDamage(bullet->getDamage());
                if(enemy->getHp()==0)
                    explosions.push_back(new ExplosionEffect(enemy->getPosition()));
                snd->playSound("explosion");

                // THAY ĐỔI: Chỉ đánh dấu đạn cần xóa, không xóa trực tiếp
                bullet->markForRemoval();
                break; // Đạn chỉ trúng 1 enemy là huỷ
            }
        }
    }
}

void CollisionManager::checkEnemyPlayerCollision(std::vector<Enemy*>& enemies, Player& player, std::vector<ExplosionEffect*>& explosions) {
    for (auto enemy : enemies) {
        if (!enemy->isAlive() || !player.isAlive()) continue;

        if (enemy->getType() == "MineTrap" && enemy->getBounds().findIntersection(player.getBounds())) {
            player.takeDamage();
            enemy->takeDamage(MineTrapHP );
            explosions.push_back(new ExplosionEffect(enemy->getPosition()));
            snd->playSound("explosion");
            continue; // xử lý xong MineTrap thì bỏ qua phần xử lý dưới
        }

        if (enemy->getBounds().findIntersection(player.getBounds())) {
            player.takeDamage();
            enemy->takeDamage(1);
            explosions.push_back(new ExplosionEffect(enemy->getPosition()));
            snd->playSound("explosion");
        }
    }
}
void CollisionManager::checkBulletPlayerCollision(std::vector<Bullet*>& bullets, Player& player, std::vector<ExplosionEffect*>& explosions) {
    for (Bullet* bullet : bullets) { // Duyệt bằng range-based for
        if (!bullet->isAlive()) continue; // Bỏ qua đạn đã được đánh dấu không hoạt động
        if (bullet->getDirection().y < 0) {
            continue;
        }
        if (bullet->getHitDelayTimer() >= HIT_DELAY && bullet->getBounds().findIntersection(player.getBounds())) {
            player.takeDamage();
            if(player.getHp() == 0)
                 explosions.push_back(new ExplosionEffect(player.getPosition()));
            snd->playSound("explosion");

            // THAY ĐỔI: Chỉ đánh dấu đạn cần xóa, không xóa trực tiếp
            bullet->markForRemoval();
        }
    }
}

void CollisionManager::checkBulletBulletCollision(std::vector<Bullet*>&bullets, std::vector<ExplosionEffect*>&explosions) {

    // Duyệt qua tất cả các cặp đạn (đảm bảo không kiểm tra với chính nó hoặc trùng lặp)

    for (size_t i = 0; i < bullets.size(); ++i) {

        Bullet* bullet1 = bullets[i];

        if (!bullet1->isAlive()) continue;

        for (size_t j = i + 1; j < bullets.size(); ++j) {

            Bullet* bullet2 = bullets[j];

            if (!bullet2->isAlive()) continue;

            // Kiểm tra xem viên đạn nào là của boss

            bool isBullet1FiredByBoss = bullet1->getIsFiredByBoss();

            bool isBullet2FiredByBoss = bullet2->getIsFiredByBoss();

            // Nếu MỘT TRONG HAI viên đạn được bắn bởi boss, thì bỏ qua va chạm (không hủy)

            if (isBullet1FiredByBoss || isBullet2FiredByBoss) {

                continue; // Đạn boss không bị hủy bởi đạn khác

            }

            // Kiểm tra xem một viên là của người chơi, viên còn lại là của kẻ địch

            bool isPlayerBullet1 = (bullet1->getDirection().y < 0);

            bool isEnemyBullet2 = (bullet2->getDirection().y > 0);

            bool isPlayerBullet2 = (bullet2->getDirection().y < 0);

            bool isEnemyBullet1 = (bullet1->getDirection().y > 0);

            // Chỉ va chạm nếu một viên là đạn player và viên kia là đạn enemy thường

            if ((isPlayerBullet1 && isEnemyBullet2) || (isPlayerBullet2 && isEnemyBullet1)) {

                if (bullet1->getHitDelayTimer() >= HIT_DELAY && bullet1->getBounds().findIntersection(bullet2->getBounds())) {

                    bullet1->markForRemoval();

                    bullet2->markForRemoval();

                    // Tạo hiệu ứng nổ nhỏ tại vị trí va chạm, ở giữa hai viên đạn

                    sf::Vector2f collisionPos = (bullet1->getPosition() + bullet2->getPosition()) / 2.0f;

                    explosions.push_back(new ExplosionEffect(collisionPos));

                    snd->playSound("explosion"); // Phát âm thanh nổ nhỏ

                    break;

                }

            }

        }

    }

}
