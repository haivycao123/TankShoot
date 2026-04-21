#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "UIManager.h"

UIManager::UIManager()
    : m_player(nullptr),
    m_hpText(*DATA->GetDefaultFont()),
    m_skillText(*DATA->GetDefaultFont()),
    m_hpShadow(*DATA->GetDefaultFont()),
    m_skillShadow(*DATA->GetDefaultFont())
{
    int fontSize = 28;
    sf::Color mainColor = sf::Color::White;
    sf::Color shadowColor = sf::Color(0, 0, 0, 150); // Bóng đen mờ

    // HP
    m_hpText.setCharacterSize(fontSize);
    m_hpText.setFillColor(mainColor);
    m_hpText.setPosition({ 10.f, 10.f });

    m_hpShadow.setCharacterSize(fontSize);
    m_hpShadow.setFillColor(shadowColor);
    m_hpShadow.setPosition(m_hpText.getPosition() + sf::Vector2f(2, 2));

    // SKILL
    m_skillText.setCharacterSize(fontSize);
    m_skillText.setFillColor(mainColor);
    m_skillText.setPosition({ 10.f, 50.f });

    m_skillShadow.setCharacterSize(fontSize);
    m_skillShadow.setFillColor(shadowColor);
    m_skillShadow.setPosition(m_skillText.getPosition() + sf::Vector2f(2, 2));
}

void UIManager::init(Player* player) {
    m_player = player;

    sf::Font* mainFont = DATA->getFont("arcade");
    if (mainFont) {
        m_hpText.setFont(*mainFont);
        m_skillText.setFont(*mainFont);
        m_hpShadow.setFont(*mainFont);
        m_skillShadow.setFont(*mainFont);
    }
    else {
        std::cerr << "⚠️ Error: Cannot load font 'arcade'. Using default.\n";
    }

    update(0.f);
}

void UIManager::update(float deltaTime) {
    if (!m_player) return;

    std::string hpStr = "HP: " + std::to_string(m_player->getHp());
    m_hpText.setString(hpStr);
    m_hpShadow.setString(hpStr);

    std::string skillStr;
    if (m_player->isSkillReady()) {
        skillStr = "SKILL: READY";
    }
    else {
        float elapsed = m_player->getSkillCooldownTimer();
        float cooldown = PlayerSkillCooldown;
        float timeLeft = cooldown - elapsed;
        if (timeLeft < 0) timeLeft = 0;

        std::stringstream ss;
        ss << "SKILL: " << std::fixed << std::setprecision(0) << timeLeft << "S";
        skillStr = ss.str();
    }

    m_skillText.setString(skillStr);
    m_skillShadow.setString(skillStr);
}

void UIManager::draw(sf::RenderWindow* window) {
    if (!window) return;

    window->draw(m_hpShadow);
    window->draw(m_skillShadow);

    window->draw(m_hpText);
    window->draw(m_skillText);
}
