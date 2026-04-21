#pragma once
#include <SFML/Graphics.hpp>
#include "../Configuration/GameConfig.h"
class Application {
public:
	void run();//Vòng lặp chính của game
	~Application();
private:
	void init();//Dùng để khởi tạo các thành phần: ví dụ như tạo cửa sổ sf::RenderWindow, khởi tạo GameStateMachine
	void update(float deltaTime);
	void draw();

	sf::RenderWindow* m_window;//là con trỏ đến cửa sổ hiển thị game (SFML).
};
