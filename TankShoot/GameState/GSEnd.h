#pragma once
#include "../CoreEngine/GameStateBase.h"
#include "../Configuration/GameConfig.h"
#include "../Utility/GameButton.h"
class GSEnd : public GameStateBase {
public:
	GSEnd();
	virtual ~GSEnd();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
private:
	sf::Sprite m_Background;
	std::list<GameButton*> m_ListBtn;
	sf::Text m_Title;
	sf::Sprite m_Overlay;
};
