#pragma once
#include "State.h"

class ResultScreen : public State
{
public:
	ResultScreen();
	~ResultScreen();


	void Init()override;
	void Update()override;
	void Draw()override;

};
