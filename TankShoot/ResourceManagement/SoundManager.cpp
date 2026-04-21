#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "SoundManager.h"

SoundManager::SoundManager() : volume(100.f) {
    // KHỞI TẠO ĐƯỜNG DẪN: Đặt đường dẫn cơ sở cho các file âm thanh và nhạc
    // Giả định thư mục cấu trúc giống ResourceManager: ../Data/Sounds/ và ../Data/Music/
    std::string dataPath = "../Data/";
    m_SoundFXPath = dataPath + "Sound/"; 
    m_MusicPath = dataPath + "Music/";   
}

SoundManager::~SoundManager() = default;

void SoundManager::loadSound(const std::string& name) {
    std::string fullPath = m_SoundFXPath + name + ".wav"; // Tự động thêm đuôi .wav (bạn có thể thay đổi)

    // Kiểm tra xem sound này đã được tải chưa để tránh tải lại
    if (bufferMap.count(name)) {
        std::cerr << "Warning: Sound '" << name << "' already loaded. Not reloading." << std::endl;
        return;
    }

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(fullPath)) {
        std::cerr << "Failed to load sound: " << fullPath << std::endl;
        return;
    }

    bufferMap[name] = std::move(buffer); // Chuyển buffer vào map

    // Tạo sound mới bằng cách truyền buffer đã lưu trong map
    // Sử dụng .at() để truy cập buffer an toàn, đảm bảo nó tồn tại
    auto sound = std::make_unique<sf::Sound>(bufferMap.at(name));
    sound->setVolume(volume);
    soundMap[name] = std::move(sound);
}


void SoundManager::playSound(const std::string& name) {
    if (!allowSound) return;

    auto it = soundMap.find(name);
    if (it != soundMap.end()) {
        it->second->play();
    }
}


// SỬA ĐỔI: Hàm loadMusic chỉ nhận tên, tự thêm đuôi .ogg và đường dẫn
void SoundManager::loadMusic(const std::string& name) {
    std::string fullPath = m_MusicPath + name + ".ogg"; // Tự động thêm đuôi .ogg (bạn có thể thay đổi)

    music.stop(); // Dừng nhạc đang phát trước khi tải nhạc mới
    if (!music.openFromFile(fullPath)) {
        std::cerr << "Failed to load music: " << fullPath << std::endl;
        return;
    }
    music.setVolume(volume);
}
void SoundManager::playMusic(bool loop) {
    if (!allowSound) return;

    music.setLooping(loop);
    music.play();
}


void SoundManager::stopMusic() {
    music.stop();
}

void SoundManager::setVolume(float v) {
    volume = v;
    // Sử dụng range-based for loop để duyệt map
    for (auto& pair : soundMap)
        pair.second->setVolume(volume);
    music.setVolume(volume);
}

bool SoundManager::isSoundPlaying(const std::string& name) {
    auto it = soundMap.find(name);
    if (it != soundMap.end())
        return it->second->getStatus() == sf::Sound::Status::Playing;
    return false;
}

float SoundManager::getSoundTime(const std::string& name) {
    auto it = soundMap.find(name);
    if (it != soundMap.end())
        return it->second->getPlayingOffset().asSeconds();
    return 0.f;
}

void SoundManager::setAllowSound(bool allow) {
    allowSound = allow;
    if (!allow) {
        for (auto& [name, sound] : soundMap) {
            sound->stop(); // Tắt tất cả sound đang phát
        }
        music.stop(); // Tắt nhạc nền luôn
    }
}

bool SoundManager::isAllowSound() const {
    return allowSound;
}


/*int main() {
    SoundManager sm;

    sm.loadSound("click", "click.wav");
    sm.playSound("click");

    sm.loadMusic("background.ogg");
    sm.playMusic(true);

    sf::sleep(sf::seconds(5));
    sm.stopMusic();

    return 0;
}*/
