#include "GSPause.h"
#include "../Configuration/GameConfig.h"

GSPause::GSPause() : m_Title(*DATA->GetDefaultFont()), m_Background(*DATA->GetDefaultTexture()) {
	
}

GSPause::~GSPause()
{
	for (auto btn : m_ListBtn) {
		delete btn;
	}
	m_ListBtn.clear();
}

void GSPause::Exit() {}
void GSPause::Pause() {}
void GSPause::Resume() {}

void GSPause::Init()
{
	for (auto btn : m_ListBtn) {
		delete btn;
	}
	m_ListBtn.clear();

	// Tiêu đề
	sf::Font* arcadeFont = DATA->getFont("arcade");
	if (arcadeFont) {
		m_Title.setString("PAUSED");
		m_Title.setFont(*arcadeFont);
		m_Title.setCharacterSize(100);
		m_Title.setOrigin({ m_Title.getGlobalBounds().size.x / 2.f, m_Title.getGlobalBounds().size.y / 2.f });
		m_Title.setPosition({ screenWidth / 2.f, screenHeight / 9.f });
	}

	sf::Texture* bgTexture = DATA->getTexture("background");
	if (bgTexture) {
		m_Background.setTexture(*bgTexture, true);
		m_Background.setScale({
			(float)screenWidth / bgTexture->getSize().x,
			(float)screenHeight / bgTexture->getSize().y
			});
		m_Background.setPosition({ 0.f, 0.f });
		m_Background.setColor(sf::Color(255, 255, 255, 230)); // Đặt màu mờ
	}

	// Nút Resume
	GameButton* button;
	button = new GameButton();
	button->Init("resume"); 
	button->setScale({ 1.25f, 1.25f });
	button->setOrigin(button->getSize() / 2.f);
	button->setPosition({ screenWidth / 2.f, screenHeight / 2.f - 80.f });
	button->setOnClick([]() {
		// Quay về trạng thái trước đó (GSPlay)
		GSM->PopState();
		});
	m_ListBtn.push_back(button);

	// Nút Menu
	button = new GameButton();
	button->Init("menu");
	button->setScale({ 1.25f, 1.25f });
	button->setOrigin(button->getSize() / 2.f);
	button->setPosition({ screenWidth / 2.f, screenHeight / 2.f + 80.f });
	button->setOnClick([]() {
		GSM->ChangeState(StateTypes::MENU);
		});
	m_ListBtn.push_back(button);
}

void GSPause::Update(float deltaTime)
{
	for (auto btn : m_ListBtn) {
		btn->Update(deltaTime);
	}
}

void GSPause::Render(sf::RenderWindow* window)
{
	window->draw(m_Background);
	window->draw(m_Title);
	for (auto btn : m_ListBtn) {
		btn->Render(window);
	}
}