#pragma once
#include "../Utility/Singleton.h"
#include <map>
#include<string>
#include<iostream>
#include <SFML/Graphics.hpp>
#define DATA ResourceManager::GetInstance()// Macro giúp gọi nhanh singleton của ResourceManager
using namespace std;
// Lớp quản lý tài nguyên toàn cục của game (texture, font)
class ResourceManager :public CSingleton<ResourceManager> 
{
public:
	ResourceManager();
	~ResourceManager();

	void addTexture(string name);// Thêm texture vào bộ nhớ, truyền vào tên file (không cần đuôi hoặc đường dẫn đầy đủ)
	void RemoveTexture(string name);// Xoá texture khỏi bộ nhớ (nếu không còn dùng)
	sf::Texture* getTexture(string name);// Trả về con trỏ đến texture theo tên đã đăng ký

	void addFont(std::string name);// Thêm font vào bộ nhớ, truyền vào tên file
	void removeFont(std::string name);// Xoá font khỏi bộ nhớ
	sf::Font* getFont(std::string name);//// Trả về con trỏ đến font theo tên

	// Hàm này để lấy texture mặc định (sẽ sử dụng khi khởi tạo sprite)
	static sf::Texture* GetDefaultTexture();

	// Hàm này để lấy font mặc định (sẽ sử dụng khi khởi tạo sf::Text)
	static sf::Font* GetDefaultFont();
private:
	// Bản đồ lưu trữ texture theo tên → giúp quản lý và tái sử dụng
	map<string, sf::Texture*> m_MapTexture;

	// Bản đồ lưu trữ font chữ theo tên
	map<string, sf::Font*> m_MapFont;

	// Đường dẫn cơ bản (gốc) – dùng để ghép với texture/font path
	string m_Path;

	// Đường dẫn con dẫn tới thư mục chứa texture
	string m_TexturePath;

	// Đường dẫn con dẫn tới thư mục chứa font
	string m_FontPath;

	// Texture mặc định sẽ được trả về nếu texture yêu cầu không tìm thấy
	sf::Texture* m_DefaultTexture;

	//  Font mặc định
	sf::Font* m_DefaultFont;
};
