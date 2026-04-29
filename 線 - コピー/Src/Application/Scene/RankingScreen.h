#pragma once
#include "../State.h"

class RankingScreen : public State
{
public:
	RankingScreen();
	~RankingScreen();


	void Init()override;
	void Update()override;
	void Draw()override;

};
