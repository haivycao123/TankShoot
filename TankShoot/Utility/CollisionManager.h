#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../GameObject/Bullet.h"
#include "../GameObject/Enemy.h"
#include "../GameObject/AirCraft.h"
#include "../GameObject/Player.h"
#include "../Utility/ExplosionEffect.h"
#include "../Configuration/GameConfig.h"
#include "../ResourceManagement/SoundManager.h"

class CollisionManager {//Class không có thuộc tính nên không cần constructor và destructor
public:
    static void checkBulletEnemyCollision(std::vector<Bullet*>& bullets, std::vector<Enemy*>& enemies, std::vector<ExplosionEffect*>& explosions);
    static  void checkEnemyPlayerCollision(std::vector<Enemy*>& enemies, Player& player, std::vector<ExplosionEffect*>& explosions);
    static void checkBulletPlayerCollision(std::vector<Bullet*>& bullets, Player& player, std::vector<ExplosionEffect*>& explosions);
    static void checkBulletBulletCollision(std::vector<Bullet*>& bullets, std::vector<ExplosionEffect*>& explosions);

};
