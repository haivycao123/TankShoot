
#pragma once
#include "../CoreEngine/GameStateBase.h"
#include "../Configuration/GameConfig.h"
#include "../Utility/GameButton.h"
class GSMenu : public GameStateBase {
public:
	GSMenu();
	virtual ~GSMenu();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
private:
	std::list<GameButton*> m_ListBtn;
	sf::Sprite m_Background;
	sf::Text m_TitleText;
	bool m_isDebouncing; // Biến cờ chống dội
};
