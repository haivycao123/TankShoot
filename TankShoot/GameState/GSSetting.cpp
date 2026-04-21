#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "GSSetting.h"

GSSetting::GSSetting() : m_Background(*DATA->GetDefaultTexture()), m_Title(*DATA->GetDefaultFont())
{
     
}

GSSetting::~GSSetting()
{
	// Giải phóng bộ nhớ cho các GameButton đã được cấp phát động
	for (auto btn : m_ListBtn) {
		delete btn;
	}
	m_ListBtn.clear();
}

void GSSetting::Exit()
{
}

void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}

void GSSetting::Init()
{
    // Xóa các nút cũ nếu Init() được gọi lại
    for (auto btn : m_ListBtn) {
        delete btn;
    }
    m_ListBtn.clear();

    GameButton* button;
    //close Button
    button = new GameButton();
    button->Init("return");
    button->setOrigin(button->getSize() / 2.f);
    button->setSize(sf::Vector2f(50.f, 50.f));
    button->setPosition({ screenWidth - screenWidth / 20.f, screenHeight / 8.f });
    button->setOnClick([]() {GSM->PopState(); });
    m_ListBtn.push_back(button);

    //turn on music
    button = new GameButton();
    button->Init("music"); // Đảm bảo bạn có texture "music"
    button->setOrigin(button->getSize() / 2.f);
    button->setSize(sf::Vector2f(100.f, 100.f));
    button->setPosition({ screenWidth / 2.f + screenWidth / 4.f, screenHeight - screenHeight / 8.f });
    button->setOnClick([]() {snd->setVolume(100.f); });
    m_ListBtn.push_back(button);

    //turn off music
    button = new GameButton();
    button->Init("music_off"); // Đảm bảo bạn có texture "music_off"
    button->setOrigin(button->getSize() / 2.f);
    button->setSize(sf::Vector2f(100.f, 100.f));
    button->setPosition({ screenWidth / 2.f - screenWidth / 4.f, screenHeight - screenHeight / 8.f });
    button->setOnClick([]() {snd->setVolume(0.f); });
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
		m_Title.setFont(*font);
	}
	else {
		m_Title.setFont(*DATA->GetDefaultFont());
	}

	m_Title.setString("SETTING");
	m_Title.setCharacterSize(128); // Kích thước chữ
	m_Title.setFillColor(sf::Color::White); // Màu chữ

	// Căn giữa chữ phía trên nút Play
	sf::FloatRect textBounds = m_Title.getLocalBounds();
	m_Title.setOrigin({ textBounds.size.x / 2, textBounds.size.y / 2 });
	m_Title.setPosition({ screenWidth / 2, (screenHeight / 2) - 300 });
}

void GSSetting::Update(float deltaTime)
{
	for (auto btn : m_ListBtn) {
		btn->Update(deltaTime);
	}
}

void GSSetting::Render(sf::RenderWindow* window)//Thiết kế lại
{
	window->draw(m_Background);
	window->draw(m_Title);
	for (auto btn : m_ListBtn) {
		btn->Render(window);
	}
}