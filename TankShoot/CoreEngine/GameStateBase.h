#pragma once // Ngăn chặn include nhiều lần cùng một file

#include "../ResourceManagement/ResourceManager.h"     // Quản lý texture, font,...
#include "GameStateMachine.h"    // Quản lý chuyển đổi trạng thái game
#include "../Configuration/GameConfig.h"          // Cấu hình chung của game (kích thước, path,...)
#include "../Utility/GameButton.h"          // Định nghĩa nút bấm UI
#include "../ResourceManagement/SoundManager.h"        // Quản lý âm thanh

// Lớp cơ sở trừu tượng cho các trạng thái trong game (ví dụ: menu, gameplay, end screen)
class GameStateBase {
public:
	GameStateBase() {}
	virtual ~GameStateBase() {}

	// Gọi khi thoát khỏi state (giải phóng tài nguyên)
	virtual void Exit() = 0;

	// Gọi khi tạm dừng (pause)
	virtual void Pause() = 0;

	// Gọi khi quay lại state này sau khi pause
	virtual void Resume() = 0;

	// Gọi khi bắt đầu state (khởi tạo tài nguyên)
	virtual void Init() = 0;

	// Gọi mỗi khung hình để cập nhật logic
	virtual void Update(float deltaTime) = 0;

	// Gọi mỗi khung hình để vẽ nội dung
	virtual void Render(sf::RenderWindow* window) = 0;

	// Tạo state cụ thể theo loại (enum StateTypes) – dùng trong GameStateMachine
	static GameStateBase* CreateState(StateTypes st);
};
