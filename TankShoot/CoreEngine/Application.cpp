#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "Application.h"
#include "GameStateBase.h"

void Application::run()
{
    //Khởi tạo bộ tạo số ngẫu nhiên
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    init(); 
    sf::Clock clock; //Tạo đồng hồ đo thời gian giữa các khung hình
    float deltaTime = 0.f; 

    while (m_window->isOpen()) 
    {
        deltaTime = clock.restart().asSeconds(); //Tính khoảng thời gian từ lần lặp trước

        while (const std::optional event = m_window->pollEvent())//Bắt sự kiện bàn phím, chuột, đóng cửa sổ
        {
            if (event->is<sf::Event::Closed>())
                m_window->close();
        }
        update(deltaTime);//Cập nhật logic game theo thời gian thực
        draw();
    }
}

Application::~Application() {
	if (m_window != nullptr)
		delete m_window;
}
void Application::init()
{
    //Tạo cửa sổ hiển thị game, kích thước cố định, chỉ có nút đóng
    m_window = new sf::RenderWindow(sf::VideoMode({screenWidth, screenHeight}), "TankShoot", sf::Style::Close);
    m_window->setFramerateLimit(60);//Giới hạn 60 FPS
    m_window->setVerticalSyncEnabled(false);//Không bật đồng bộ dọc

    //Cung cấp cửa sổ cho WindowConnector
    WConnect->setWindow(m_window);

    DATA->addTexture("background");
    //
    snd->setAllowSound(true);
    snd->setVolume(100.f);
    snd->loadSound("explosion");
    snd->loadSound("lazer");
    snd->loadSound("player_shoot");
    snd->loadSound("skill_active");
    snd->loadSound("player_hit");
    snd->loadSound("win");
    snd->loadSound("lose");
    // Khởi tạo trạng thái game ban đầu (INTRO)
    GSM->ChangeState(StateTypes::INTRO);
}

void Application::update(float deltaTime)
{
    //Kiểm tra xem có cần chuyển trạng thái không 
    if (GameStateMachine::GetInstance()->NeedToChangeState()) {
        GameStateMachine::GetInstance()->PerformStateChange();
    }
    // Kiểm tra con trỏ currentState có hợp lệ không trước khi gọi Update
    if (GameStateMachine::GetInstance()->currentState() != nullptr) {
        GameStateMachine::GetInstance()->currentState()->Update(deltaTime);
    }

}

void Application::draw()
{
    m_window->clear(sf::Color::White);//Xoá màn hình (làm mới)
    // Kiểm tra con trỏ currentState có hợp lệ không trước khi gọi Render
    if (GameStateMachine::GetInstance()->currentState() != nullptr) {
        GameStateMachine::GetInstance()->currentState()->Render(m_window);
    }
    m_window->display();//Hiển thị khung hình mới
}
