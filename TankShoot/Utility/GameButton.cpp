#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "GameButton.h"

GameButton::GameButton()
{
	m_isHandling = false; // Khởi đầu: nút chưa được nhấn

}

GameButton::~GameButton()
{
}

void GameButton::Init(std::string name)
{
	// Dòng dưới để nạp texture từ file (hiện đang bị tắt comment)
	this->setTexture(DATA->getTexture( name));
	this->setSize(sf::Vector2f(100, 100));//Vẽ nút
}

void GameButton::Update(float deltaTime)
{
	// Nếu người chơi nhấn chuột trái
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {//Kiểm tra xem có ấn chuột trái không
		HandleTouchEvent();// Kiểm tra xem chuột có nằm trên nút hay không
	}
}

void GameButton::Render(sf::RenderWindow* window)
{
	// Vẽ hình chữ nhật đại diện cho nút lên cửa sổ
	window->draw(*this);
}

void GameButton::HandleTouchEvent()
{
	m_isHandling = false;// Mặc định: không xử lý
	// Nếu vị trí chuột nằm trong vùng của nút
	if (this->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*WConnect->getWindow())))//Kiểm tra vị trí con trỏ chuột
	{
		m_btnClickFunc();// Gọi hàm xử lý đã được gán bằng setOnClick
		m_isHandling = true;// Đánh dấu là đã xử lý
	}
}

bool GameButton::isHandle()
{
	return m_isHandling;// Trả về trạng thái: nút có đang được nhấn hay không

}

void GameButton::setOnClick(void(*Func)())
{
	m_btnClickFunc = Func; // Gán con trỏ hàm xử lý khi click
}