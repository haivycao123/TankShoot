#pragma once
#include "../CoreEngine/GameStateBase.h"
#include "../Configuration/GameConfig.h"
#include "../Utility/GameButton.h"
class GSIntro : public GameStateBase {
public:
	GSIntro();
	virtual ~GSIntro();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
private:
	sf::Sprite m_Logo;
	float m_currentTime;
};