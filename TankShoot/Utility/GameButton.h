#pragma once 

#include "WindowConnector.h"   // Kết nối với cửa sổ SFML (chứa thông tin input, window...)
#include "../ResourceManagement/ResourceManager.h"   // Quản lý tài nguyên (ảnh, font, âm thanh)

// Lớp GameButton kế thừa từ RectangleShape – dùng để tạo nút bấm có thể tương tác
class GameButton : public sf::RectangleShape {
public:
	GameButton();  // Constructor – khởi tạo nút
	~GameButton(); // Destructor – giải phóng tài nguyên nếu có

	// Khởi tạo nút: nạp texture theo tên từ ResourceManager
	void Init(std::string name);

	// Cập nhật trạng thái nút mỗi frame (ví dụ: hiệu ứng hover)
	void Update(float deltaTime);

	// Vẽ nút lên cửa sổ
	void Render(sf::RenderWindow* window);

	// Xử lý khi người chơi chạm vào nút
	void HandleTouchEvent();

	// Kiểm tra xem người dùng có đang chạm vào nút không
	bool isHandle();

	// Gán sự kiện khi nút được nhấn – truyền con trỏ hàm xử lý
	void setOnClick(void (*Func)());

private:
	// Con trỏ tới hàm được gọi khi nút được bấm
	void (*m_btnClickFunc)();

	// Biến đánh dấu nút đang được nhấn hay không
	bool m_isHandling;
};
