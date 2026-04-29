#pragma once
#include "../State.h"

class GameScene : public State
{
public:
	GameScene();
	~GameScene();


	void Init()override;
	void Update()override;
	void Draw()override;

};
