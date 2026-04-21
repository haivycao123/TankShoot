#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "GameStateMachine.h"
#include "GameStateBase.h"

GameStateMachine::GameStateMachine()
{
    m_ActivesState = nullptr;// Trạng thái hiện tại (đang chạy)
    m_NextState = nullptr;// Trạng thái chuẩn bị được chuyển tới
}

GameStateMachine::~GameStateMachine()
{
    // Xoá toàn bộ các trạng thái trong stack khi kết thúc game
    while (!m_StateStack.empty()) {
        delete m_StateStack.back();
        m_StateStack.pop_back();
    }
}

void GameStateMachine::ChangeState(GameStateBase* state)
{
    m_NextState = state;// Ghi lại trạng thái sẽ được thay thế ở vòng lặp chính (run)
}


void GameStateMachine::ChangeState(StateTypes st)
{
    // Tạo đối tượng trạng thái mới từ enum và gọi ChangeState(state)
    GameStateBase* gs = GameStateBase::CreateState(st);
    ChangeState(gs);
}

void GameStateMachine::PushState(StateTypes st)
{
    GameStateBase* gs = GameStateBase::CreateState(st);
    // Nếu đang có state, tạm dừng state hiện tại trước khi push state mới
    if (!m_StateStack.empty()) {
        m_StateStack.back()->Pause();
    }
    m_NextState = gs;// Đợi được xử lý trong PerformStateChange
}

void GameStateMachine::PopState()
{
    // Xoá trạng thái hiện tại
    if (!m_StateStack.empty()) {
        m_StateStack.back()->Exit();
        m_StateStack.pop_back();
    }
    // Quay về trạng thái trước đó nếu có
    if (!m_StateStack.empty()) {
        m_StateStack.back()->Resume();
        m_ActivesState = m_StateStack.back();// Cập nhật trạng thái hiện tại
    }
    else {
        m_ActivesState = nullptr; // Nếu stack rỗng, không có state nào hoạt động
    }
}

void GameStateMachine::PerformStateChange()
{
    if (m_NextState != nullptr) {
        // Nếu đang có state → gọi Exit() trước khi thay đổi
        if (!m_StateStack.empty()) {
            m_StateStack.back()->Exit();
        }
        // Đẩy state mới vào stack, khởi tạo nó
        m_StateStack.push_back(m_NextState);
        m_StateStack.back()->Init();
        // Cập nhật trạng thái hiện tại
        m_ActivesState = m_NextState;
    }
    m_NextState = nullptr;// Reset lại sau khi chuyển xong
}

GameStateBase* GameStateMachine::currentState() const
{
    return m_ActivesState;// Trả về trạng thái hiện tại đang chạy
}

GameStateBase* GameStateMachine::nextState() const
{
    return m_NextState;// Trạng thái sẽ chuyển tới (nếu có)
}

bool GameStateMachine::NeedToChangeState()
{
    return m_NextState != nullptr;// Kiểm tra có yêu cầu chuyển state không
}

bool GameStateMachine::HasState()
{
    return m_StateStack.size() > 0;// Có đang có bất kỳ state nào không?
}