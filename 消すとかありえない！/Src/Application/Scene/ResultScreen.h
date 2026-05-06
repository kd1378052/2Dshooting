#pragma once
#include "../State.h"

class Score;

class ResultScreen : public State
{
public:
	ResultScreen();
	~ResultScreen();


	void Init()override;
	void Update()override;
	void Draw()override;

private:

	Score* m_score;

	//背景
	Math::Matrix ResultbackMat;
	KdTexture ResultbackTex;
};
