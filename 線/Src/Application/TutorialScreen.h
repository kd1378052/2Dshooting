#pragma once
#include "State.h"

class TutorialScreen : public State
{
public:
	TutorialScreen();
	~TutorialScreen();


	void Init()override;
	void Update()override;
	void Draw()override;

};
