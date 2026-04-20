#pragma once
#include "State.h"
#include "Player.h"

class GameScreen : public State
{
public:
	GameScreen();
	~GameScreen();


	void Init()override;
	void Update()override;
	void Draw()override;
private:

	Player player;
};
