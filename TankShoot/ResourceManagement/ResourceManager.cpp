#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "ResourceManager.h"

ResourceManager::ResourceManager() //Phương thức khởi tạo
{
	//Gắn đường dẫn cho các thuộc tính
	m_Path = "../Data/";
	m_TexturePath = m_Path + "Texture/";
	m_FontPath = m_Path + "Font/";

	//  Khởi tạo texture mặc định (ví dụ 1x1 màu trắng)
	// Tạo texture mặc định 1x1 màu trắng
	m_DefaultTexture = new sf::Texture();

	// Tạo image thông qua constructor mới
	sf::Image image({ 1, 1 }, sf::Color::White);  // Kích thước 1x1, màu trắng

	if (!m_DefaultTexture->loadFromImage(image)) {
		std::cerr << "Failed to create default texture!" << std::endl;
		delete m_DefaultTexture;
		m_DefaultTexture = nullptr;
	}

	if (m_DefaultTexture) {
		m_DefaultTexture->setSmooth(false); // Đảm bảo texture mặc định cũng không bị làm mịn
	}


	// THÊM: Khởi tạo font mặc định
	m_DefaultFont = new sf::Font();
	// Thử tải một font mặc định có sẵn của SFML nếu không có file hoặc dùng font rỗng (ít tác dụng)
	// Hoặc nếu bạn có một font file "default.TTF" nhỏ gọn, hãy tải nó.
	// Ví dụ, nếu bạn có file "arial.ttf" trong thư mục Fonts:
	if (!m_DefaultFont->openFromFile(m_FontPath + "arcade.TTF")) { // Thử tải một font cơ bản (ví dụ arial.ttf)
		std::cerr << "Failed to load default font from '" << m_FontPath << "arcade.TTF'. Text might not display correctly!" << std::endl;
		// Nếu không tải được font mặc định nào, sf::Text vẫn có thể được khởi tạo nhưng sẽ không hiển thị chữ.
		// Đối với các game đơn giản, một font lỗi sẽ tốt hơn là crash.
	}
}

ResourceManager::~ResourceManager()//Hàm huỷ
{
	for (auto it : m_MapTexture) {//Duyệt xoá map
		if (it.second != nullptr) {
			delete it.second;
		}
	}
	m_MapTexture.clear();

	for (auto it : m_MapFont) {//Duyệt xoá map
		if (it.second != nullptr) {
			delete it.second;
		}
	}
	m_MapFont.clear();

	//  Giải phóng texture mặc định
	if (m_DefaultTexture) {
		delete m_DefaultTexture;
		m_DefaultTexture = nullptr;
	}

	// Giải phóng font mặc định
	if (m_DefaultFont) {
		delete m_DefaultFont;
		m_DefaultFont = nullptr;
	}
}

void ResourceManager::addTexture(string name)
{
	auto it = m_MapTexture.find(name);
	if (it != m_MapTexture.end()) {
		return;
	}

	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(m_TexturePath + name + ".png")) {
		std::cerr << "Failed to load texture for addTexture: " << m_TexturePath + name + ".png" << std::endl;
		delete texture; // Xóa allocation thất bại
		// KHÔNG return m_DefaultTexture ở đây, addTexture chỉ để thêm.
		// GetTexture sẽ lo việc trả về default nếu file không tìm thấy.
		return;
	}

	texture->setSmooth(false); // <--- THÊM DÒNG NÀY

	m_MapTexture.insert(pair<string, sf::Texture*>(name, texture));
}


void ResourceManager::RemoveTexture(string name) //Xoá ảnh
{
	//Kiểm tra ảnh đã tồn tại chưa
	auto it = m_MapTexture.find(name);
	if (it == m_MapTexture.end()) { //Nếu chưa đã tồn tại thì không cần làm gì
		return;
	}
	if (it->second != nullptr)
		delete it->second;
	m_MapTexture.erase(it);
}

sf::Texture* ResourceManager::getTexture(string name)
{
	auto it = m_MapTexture.find(name);
	if (it != m_MapTexture.end()) {
		return it->second;
	}

	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(m_TexturePath + name + ".png")) {
		std::cerr << "Failed to load texture for getTexture: " << m_TexturePath + name + ".png" << ". Returning default texture." << std::endl;
		delete texture; // Xóa allocation thất bại
		return m_DefaultTexture; // THAY ĐỔI: Trả về texture mặc định thay vì nullptr
	}

	texture->setSmooth(false); // <--- THÊM DÒNG NÀY

	m_MapTexture.insert(pair<string, sf::Texture*>(name, texture));
	return texture;
}

// Triển khai hàm GetDefaultTexture
sf::Texture* ResourceManager::GetDefaultTexture() {
	return GetInstance()->m_DefaultTexture;
}

void ResourceManager::addFont(std::string name)
{
	sf::Font* font = new sf::Font();
	if (!font->openFromFile(m_FontPath + name + ".TTF")) {
		delete font;
		std::cerr << "Failed to load font for addFont: " << m_FontPath + name + ".TTF" << std::endl;
		return;
	}

	auto it = m_MapFont.find(name);
	if (it != m_MapFont.end()) {
		delete font;
		return;
	}
	m_MapFont.insert(std::pair<std::string, sf::Font*>(name, font));
}

void ResourceManager::removeFont(std::string name)//Xoá font chữ
{
	auto it = m_MapFont.find(name);
	if (it == m_MapFont.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_MapFont.erase(it);
}

sf::Font* ResourceManager::getFont(std::string name)//Lấy font
{
	auto it = m_MapFont.find(name);
	if (it != m_MapFont.end()) {
		return it->second;
	}
	sf::Font* font = new sf::Font();
	if (!font->openFromFile(m_FontPath + name + ".TTF")) {
		delete font;
		std::cerr << "Failed to load font for getFont: " << m_FontPath + name + ".TTF" << ". Returning default font." << std::endl;
		return m_DefaultFont; // THAY ĐỔI: Trả về font mặc định thay vì nullptr
	}
	m_MapFont.insert(std::pair<std::string, sf::Font*>(name, font));
	return font;
}
// Triển khai hàm GetDefaultFont
sf::Font* ResourceManager::GetDefaultFont() {
	return GetInstance()->m_DefaultFont;
}