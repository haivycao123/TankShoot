#pragma once
#include "../Utility/Singleton.h"
#include <list>


// Macro gọi nhanh singleton GameStateMachine ở bất kỳ đâu trong code
#define GSM GameStateMachine::GetInstance()

// Forward declaration – tránh circular include với GameStateBase
class GameStateBase;

// Các loại trạng thái game – dùng trong hàm chuyển state
enum StateTypes
{
	INVALID = 0, // Không hợp lệ
	INTRO,       // Màn hình mở đầu
	MENU,        // Menu chính
	PLAY,        // Trạng thái đang chơi
	SETTING,     // Cài đặt
	ABOUT,       // Giới thiệu 
	PAUSE,       // Tạm dừng game
	END          // Kết thúc game
};

// Lớp quản lý các trạng thái game (menu, chơi, thua, v.v.)
class GameStateMachine : public CSingleton<GameStateMachine> {
public:
	GameStateMachine();  // Constructor
	~GameStateMachine(); // Destructor

	// Đổi sang state mới, xoá state hiện tại
	void ChangeState(GameStateBase* state);

	// Đổi sang state mới dựa vào enum
	void ChangeState(StateTypes st);

	// Đẩy thêm một state lên trên (giữ state hiện tại)
	void PushState(StateTypes st);

	// Gỡ bỏ state hiện tại (quay về state trước đó)
	void PopState();

	// Gọi để thực hiện chuyển state nếu có yêu cầu trước đó
	void PerformStateChange();

	// Lấy state đang hoạt động hiện tại
	GameStateBase* currentState() const;

	// Lấy state sắp được chuyển tới
	GameStateBase* nextState() const;

	// Có đang chờ chuyển state không?
	bool NeedToChangeState();

	// Có bất kỳ state nào trong stack không?
	bool HasState();

private:
	std::list<GameStateBase*> m_StateStack; // Stack các trạng thái
	GameStateBase* m_ActivesState;          // State hiện tại
	GameStateBase* m_NextState;             // State kế tiếp cần chuyển đến
};