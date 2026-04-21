#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <string>
#include <SFML/System.hpp>
#include <iostream>
#include "../Utility/Singleton.h"
#define snd SoundManager::GetInstance()
class SoundManager :public CSingleton<SoundManager> {
private:
    std::map<std::string, std::unique_ptr<sf::Sound>> soundMap;
    std::map<std::string, sf::SoundBuffer> bufferMap;
    sf::Music music;
    float volume;
    bool allowSound = true;
    
    std::string m_SoundFXPath; // Đường dẫn cho các Sound Effect (ví dụ .wav)
    std::string m_MusicPath;
public:
    SoundManager();
    ~SoundManager();

    void loadSound(const std::string& name);
    void playSound(const std::string& name);
    void loadMusic(const std::string& file);
    void playMusic(bool loop);
    void stopMusic();
    void setVolume(float v);
    bool isSoundPlaying(const std::string& name);
    float getSoundTime(const std::string& name);

    void setAllowSound(bool allow);
    bool isAllowSound() const;

};

#endif // SOUNDMANAGER_HPP