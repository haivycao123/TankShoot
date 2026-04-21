#pragma once
#include "../CoreEngine/GameStateBase.h"
#include "../Configuration/GameConfig.h"
#include "../Utility/GameButton.h"

class GSPause : public GameStateBase {
public:
	GSPause();
	virtual ~GSPause();

	void Exit() override;
	void Pause() override;
	void Resume() override;

	void Init() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
private:
	sf::Text m_Title;
	sf::Sprite m_Background; 
	std::list<GameButton*> m_ListBtn;
};