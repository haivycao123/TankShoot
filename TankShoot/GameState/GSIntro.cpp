#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "GSIntro.h"


GSIntro::GSIntro() : m_Logo(*DATA->GetDefaultTexture())
{
	m_currentTime = 0.f;
}

GSIntro::~GSIntro()
{
}

void GSIntro::Exit()
{
}

void GSIntro::Pause()
{
}

void GSIntro::Resume()
{
}

void GSIntro::Init()
{   
    sf::Texture* lgTexture = DATA->getTexture("logo");

    if (lgTexture && lgTexture != DATA->GetDefaultTexture()) {
        m_Logo.setTexture(*lgTexture, true); // ✅ Cờ `true` ép cập nhật lại bounds
        m_Logo.setOrigin(sf::Vector2f(lgTexture->getSize()) / 2.f);
        m_Logo.setPosition({ screenWidth / 2.f, screenHeight / 2.f });
        m_Logo.setColor(sf::Color::White);
    }
    else {
        std::cerr << "Error: Logo texture not loaded for GSIntro." << std::endl;
    }
}


void GSIntro::Update(float deltaTime)
{
    m_currentTime += deltaTime;
    if (m_currentTime >= 3.f) { // Thời gian hiển thị intro
        GameStateMachine::GetInstance()->ChangeState(StateTypes::MENU);
    }
}

void GSIntro::Render(sf::RenderWindow* window)
{
	window->draw(m_Logo);
}