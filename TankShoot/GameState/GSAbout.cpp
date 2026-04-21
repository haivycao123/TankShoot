#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "GSAbout.h"

GSAbout::GSAbout() : m_Background(*DATA->GetDefaultTexture()), m_Title(*DATA->GetDefaultFont())
{
}

GSAbout::~GSAbout()
{
	// Giải phóng bộ nhớ cho các GameButton đã được cấp phát động
	for (auto btn : m_ListBtn) {
		delete btn;
	}
	m_ListBtn.clear();
}

void GSAbout::Exit()
{
}

void GSAbout::Pause()
{
}

void GSAbout::Resume()
{
}

void GSAbout::Init()//Thiết kế lại nếu cần
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

	m_Title.setString("ABOUT");
	m_Title.setCharacterSize(128); // Kích thước chữ
	m_Title.setFillColor(sf::Color::White); // Màu chữ

	// Căn giữa chữ 
	sf::FloatRect textBounds = m_Title.getLocalBounds();
	m_Title.setOrigin({ textBounds.size.x / 2, textBounds.size.y / 2 });
	m_Title.setPosition({ screenWidth / 2, (screenHeight / 2) - 300 });
	//Thông tin
	std::vector<std::string> lines = {
	"GROUP  NINE",
	"Cao  Hai  Vy",
	"Nguyen  Lam  Thao  Trang",
	"Nguyen  Cao  Tri",
	"Nguyen  Son  Truong",
	"THANKS   FOR   PLAYING!"
	};

	float startY = screenHeight / 5.f + 100.f;
	for (size_t i = 0; i < lines.size(); ++i) {
		sf::Text text(*font);
		text.setFont(*font);
		text.setString(lines[i]);
		text.setCharacterSize(50);
		text.setFillColor(sf::Color::White); // Màu chữ
		text.setPosition({ screenWidth / 2.f, startY + i * 50.f });
		text.setOrigin(text.getGlobalBounds().size / 2.f);
		m_InfoTexts.push_back(text);
	}
}


void GSAbout::Update(float deltaTime)
{
	for (auto btn : m_ListBtn) {
		btn->Update(deltaTime);
	}
}

void GSAbout::Render(sf::RenderWindow* window)//Thiết kế lại
{
	window->draw(m_Background);
	for (auto btn : m_ListBtn) {
		btn->Render(window);
	}
	window->draw(m_Title);
	for (auto& t : m_InfoTexts) {
		window->draw(t);
	}
}