#pragma once
#include "../State.h"

class SelectionScreen : public State
{
public:
	SelectionScreen();
	~SelectionScreen();


	void Init()override;
	void Update()override;
	void Draw()override;

};
