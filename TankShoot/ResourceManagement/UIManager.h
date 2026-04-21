#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "../GameObject/Player.h"
#include "ResourceManager.h"
#include "../Configuration/GameConfig.h"
#include <iostream>
#include <iomanip>
#include <sstream>

class UIManager {
public:
    UIManager();
    ~UIManager() = default;

    void init(Player* player);
    void update(float deltaTime);
    void draw(sf::RenderWindow* window);

private:
    Player* m_player;         // Con trỏ tới đối tượng người chơi

    sf::Text m_hpText;        // Text chính hiển thị HP
    sf::Text m_skillText;     // Text chính hiển thị thời gian hồi chiêu

    sf::Text m_hpShadow;      // Bóng mờ của HP
    sf::Text m_skillShadow;   // Bóng mờ của thời gian hồi chiêu
};
#endif