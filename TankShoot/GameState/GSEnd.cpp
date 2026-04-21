#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "GSEnd.h"

GSEnd::GSEnd() : m_Background(*DATA->GetDefaultTexture()), m_Title(*DATA->GetDefaultFont()), m_Overlay(*DATA->GetDefaultTexture())
{
}

GSEnd::~GSEnd()
{
	// Giải phóng bộ nhớ cho các GameButton đã được cấp phát động
	for (auto btn : m_ListBtn) {
		delete btn;
	}
	m_ListBtn.clear();
}

void GSEnd::Exit()
{
}

void GSEnd::Pause()
{
}

void GSEnd::Resume()
{
}

void GSEnd::Init()
{
    // Xóa các nút cũ nếu Init() được gọi lại
    for (auto btn : m_ListBtn) {
        delete btn;
    }
    m_ListBtn.clear();

    GameButton* button;
    //menu Button
    button = new GameButton();
    button->Init("menu");
    button->setOrigin(button->getSize() / 2.f);
    button->setSize(sf::Vector2f(100.f, 100.f));
    button->setPosition({ (screenWidth / 2.f) + 200 , (screenHeight/2) - 100 });
    button->setOnClick([]() {
        // GSM->PopState(); // Pop GSEnd
        // GSM->PopState(); // Pop GSPlay
        // Logic này giả định stack là [Menu, Play, End].
       
        GSM->ChangeState(StateTypes::MENU);
        });
    m_ListBtn.push_back(button);

    //replay Button
    button = new GameButton();
    button->Init("restart");
    button->setOrigin(button->getSize() / 2.f);
    button->setSize(sf::Vector2f(100.f, 100.f));
    button->setPosition({ (screenWidth / 2.f) - 200 , (screenHeight / 2) - 100 });
    button->setOnClick([]() {
        GSM->PopState(); // Pop GSEnd (trạng thái hiện tại)
        GSM->ChangeState(StateTypes::PLAY); // Chuyển sang trạng thái Play mới
        });
    m_ListBtn.push_back(button);


    if (g_isWin) {
        sf::Texture* ovTexture = DATA->getTexture("player");
        if (ovTexture && ovTexture != DATA->GetDefaultTexture()) {
            m_Overlay.setTexture(*ovTexture, true); // ✅ Cờ `true` ép cập nhật lại bounds
            m_Background.setScale({
                (float)screenWidth / ovTexture->getSize().x,
                (float)screenHeight / ovTexture->getSize().y
                });
            m_Overlay.setPosition({ (screenWidth / 2) - 50, (screenHeight / 2) + 100 });
            m_Overlay.setColor(sf::Color::White);
        }
        else {
            std::cerr << "Error: Load texture fail." << std::endl;
        }
    }
    else {
        sf::Texture* ovTexture = DATA->getTexture("player_lose");
        if (ovTexture && ovTexture != DATA->GetDefaultTexture()) {
            m_Overlay.setTexture(*ovTexture, true); // ✅ Cờ `true` ép cập nhật lại bounds
            m_Background.setScale({
                (float)screenWidth / ovTexture->getSize().x,
                (float)screenHeight / ovTexture->getSize().y
                });
            m_Overlay.setPosition({ (screenWidth / 2) - 50, (screenHeight / 2) + 100 });
            m_Overlay.setColor(sf::Color::White);
        }
        else {
            std::cerr << "Error: Load texture fail." << std::endl;
        }
    }
    //Background
    sf::Texture* bgTexture = DATA->getTexture("background");

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


    // Tile
    sf::Font* font = DATA->getFont("arcade"); 
    if (font) {
        m_Title.setFont(*font);
    }
    else {
        m_Title.setFont(*DATA->GetDefaultFont());
    }

    if (g_isWin) {
        m_Title.setString("WIN");

    }
    else {
        m_Title.setString("LOSE");
    }
    m_Title.setCharacterSize(128); // Kích thước chữ
    m_Title.setFillColor(sf::Color::White); // Màu chữ

    // Căn giữa chữ 
    sf::FloatRect textBounds = m_Title.getLocalBounds();
    m_Title.setOrigin({ textBounds.size.x / 2, textBounds.size.y / 2 });
    m_Title.setPosition({ screenWidth / 2, (screenHeight / 2) - 350 });
}

void GSEnd::Update(float deltaTime)
{
	for (auto btn : m_ListBtn) {
		btn->Update(deltaTime);
	}
}

void GSEnd::Render(sf::RenderWindow* window)//Thiết kế lại
{
    
	window->draw(m_Background);
    window->draw(m_Overlay);
    window->draw(m_Title);
	for (auto btn : m_ListBtn) {
		btn->Render(window);
	}
}