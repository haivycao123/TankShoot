#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "WindowConnector.h"

WindowConnector::WindowConnector()
{
    m_Window = nullptr;
}

void WindowConnector::setWindow(sf::RenderWindow* window)
{
    m_Window = window;
}

sf::RenderWindow* WindowConnector::getWindow()
{
    return m_Window;
}