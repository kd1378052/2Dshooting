#pragma once
#include "State.h"

class Player;

class GameScreen : public State
{
public:
	GameScreen();
	~GameScreen();


	void Init()override;
	void Update()override;
	void Draw()override;
private:

	Player *m_player;
};
