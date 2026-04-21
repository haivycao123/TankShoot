#pragma once
#include "../CoreEngine/GameStateBase.h"
#include "../GameObject/Player.h"
#include "../GameObject/Enemy.h"
#include "../GameObject/Bullet.h"
#include "../Utility/ExplosionEffect.h"
#include "../ResourceManagement/UIManager.h"
#include "../ResourceManagement/SoundManager.h"
#include "../GameObject/Spawner.h"
#include "../Utility/CollisionManager.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../GameObject/AirCraft.h"
#include "../GameObject/TankEnemy.h"
#include "../GameObject/ArmoredTank.h"
#include "../GameObject/Plane.h"
#include <random>

class GSPlay : public GameStateBase {
public:
    GSPlay();
    ~GSPlay();

    void Exit();
    void Pause();
    void Resume();

    void Init();
    void Update(float dt);
    void Render(sf::RenderWindow* window) override;

private:
    Player m_Player;
    std::vector<Enemy*> m_Enemies;
    std::vector<Bullet*> m_Bullets;
    std::vector<ExplosionEffect*> m_Explosions;

    Spawner m_Spawner;
    UIManager m_UI;
    SoundManager* m_Sound; // singleton

    bool m_isWin;
    bool m_isLose;

    sf::Sprite m_PlayBackground; 

    GameButton* m_pauseButton;
};
