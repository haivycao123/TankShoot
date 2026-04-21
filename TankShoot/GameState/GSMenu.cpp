#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "GSMenu.h"

GSMenu::GSMenu() : m_Background(*DATA->GetDefaultTexture()), m_TitleText(*DATA->GetDefaultFont())
{
}

GSMenu::~GSMenu()
{
	for (auto btn : m_ListBtn) {
		delete btn;
	}
	m_ListBtn.clear();
}

void GSMenu::Exit()
{
}

void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}

void GSMenu::Init()
{
	GameButton* button;
	//PlayButton
	button = new GameButton();
	button->Init("play");
	button->setOnClick([]() {GSM->ChangeState(StateTypes::PLAY); });
	button->setPosition({ screenWidth / 2, screenHeight / 2 });
	/*button->setSize(sf::Vector2f(150, 150));*/ //Dùng setScale sẵn 
	button->setScale(PlayButtonScale);
	button->setOrigin(button->getSize() / 2.f);
	m_ListBtn.push_back(button);

	//Exit Button
	button = new GameButton();
	button->Init("close");
	button->setOrigin(button->getSize() / 2.f);
	button->setPosition({ screenWidth * 3 / 4, screenHeight - screenHeight / 5 });
	button->setScale(OtherButtonScale);
	button->setOnClick([]() {WConnect->getWindow()->close(); });
	m_ListBtn.push_back(button);

	//Setting Button
	button = new GameButton();
	button->Init("setting");
	button->setOrigin(button->getSize() / 2.f);
	button->setPosition({ screenWidth / 4, screenHeight - screenHeight / 5 });
	button->setScale(OtherButtonScale);
	button->setOnClick([]() {GSM->ChangeState(StateTypes::SETTING); });
	m_ListBtn.push_back(button);

	//about Button
	button = new GameButton();
	button->Init("about");
	button->setOrigin(button->getSize() / 2.f);
	button->setPosition({ screenWidth / 2, screenHeight - screenHeight / 5 });
	button->setScale(OtherButtonScale);
	button->setOnClick([]() {GSM->ChangeState(StateTypes::ABOUT); });
	m_ListBtn.push_back(button);



	//Background 
	sf::Texture* bgTexture = DATA->getTexture("background3");

	if (bgTexture && bgTexture != DATA->GetDefaultTexture()) {
		m_Background.setTexture(*bgTexture, true); // ✅ Cờ `true` ép cập nhật lại bounds
		m_Background.setScale({
			(float)screenWidth / bgTexture->getSize().x,
			(float)screenHeight / bgTexture->getSize().y
			});
		m_Background.setPosition({ 0.f, 0.f });
		m_Background.setColor(sf::Color::White);
	}
	else {
		std::cerr << "Error: Load texture fail." << std::endl;
	}

	// Lấy font
	sf::Font* font = DATA->getFont("arcade"); // hoặc font bạn đang dùng
	if (font) {
		m_TitleText.setFont(*font);
	}
	else {
		m_TitleText.setFont(*DATA->GetDefaultFont());
	}

	m_TitleText.setString("TANK SHOOT");
	m_TitleText.setCharacterSize(128); // Kích thước chữ
	m_TitleText.setFillColor(sf::Color(119, 168, 50)); // Màu chữ

	// Căn giữa chữ phía trên nút Play
	sf::FloatRect textBounds = m_TitleText.getLocalBounds();
	m_TitleText.setOrigin({ textBounds.size.x / 2, textBounds.size.y / 2 });
	m_TitleText.setPosition({ screenWidth / 2, (screenHeight / 2) - 300 }); 


	snd->loadMusic("background1");
	snd->playMusic("background1");

	m_isDebouncing = true; // Bật cờ chống dội khi khởi tạo
}

void GSMenu::Update(float deltaTime)
{
	if (m_isDebouncing) {
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			m_isDebouncing = false; // Tắt cờ khi không còn nhấn chuột
		}
		return; // Bỏ qua cập nhật nút trong trạng thái chống dội
	}
	for (auto btn : m_ListBtn) {
		btn->Update(deltaTime);
	}
}

void GSMenu::Render(sf::RenderWindow* window)
{
	window->draw(m_Background);
	window->draw(m_TitleText);
	for (auto btn : m_ListBtn) {
		btn->Render(window);
	}
}