#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "CoreEngine/Application.h"

int main()
{
    Application a;
    a.run();
}