#pragma once
#define screenWidth 1280
#define screenHeight 720
#define title "TankShoot"
constexpr sf::Vector2f PlayButtonScale(1.75f, 1.75f);
constexpr sf::Vector2f OtherButtonScale(1.25f, 1.25f);

//-------------------- Player --------------------//
#define PlayerSpeed 60.0f
#define PlayerShootCooldown 0.3f
#define PlayerSkillCooldown 60.0f
#define PlayerInvincibleTime 3.0f
constexpr sf::Vector2f PlayerScale(1.0f, 1.0f);
constexpr sf::Vector2f PlayerStartPosition(500.f, 600.f);
#define NormalDamage 1

//-------------------- MineTrap --------------------//
constexpr sf::Vector2f MineTrapScale(0.5f, 0.5f);
#define MineTrapSpeed 100.0f
#define MineTrapHP 1

//-------------------- TankEnemy --------------------//
constexpr sf::Vector2f TankEnemyScale(0.5f, 0.5f);
#define TankEnemySpeed 60.0f
#define TankEnemyHP 5
#define TankEnemyShootCooldown 5.0f

//-------------------- Plane --------------------//
constexpr sf::Vector2f PlaneScale(0.5f, 0.5f);
#define PlaneSpeed 60.0f
#define PlaneHP 3
#define PlaneShootCooldown 3.0f

//-------------------- ArmoredTank --------------------//
constexpr sf::Vector2f ArmoredTankScale(0.5f, 0.5f);
#define ArmoredTankSpeed 60.0f
#define ArmoredTankHP 12 
#define ArmoredTankShootCooldown 3.0f

//-------------------- AirCraft --------------------//
constexpr sf::Vector2f AirCraftScale(0.7f, 0.7f);
#define AirCraftSpeed 10.0f
#define AirCraftHP 150
#define AirCraftShootCooldown 10.0f
#define TimeAirCraftAppear 90.0f
constexpr sf::Vector2f AirCraftStartPosition(screenWidth / 2.0f, (screenHeight / 5.0f) - 100);
constexpr sf::Vector2f SizeLazerWarningLine(10.0f, 10.0f);
constexpr sf::Color ColorLazerWarningLine(255, 0, 0, 120);

//-------------------- Bullet --------------------//
#define BulletSpeed 150.0f
#define LazerWarningTime 5.0f
#define LazerDuration 2.0f 
const float ENEMY_HIT_EFFECT_DURATION = 0.15f;
const float HIT_DELAY = 0.4f; // Ví dụ: Miễn nhiễm va chạm 0.4 giây đầu
inline bool g_isWin = false;

