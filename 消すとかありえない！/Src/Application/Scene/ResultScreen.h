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
	//スコア文字表示
	Math::Matrix ResultscoreMat;
	KdTexture ResultscoreTex;
	//スコア数字表示
	static const int maxDigits = 5;
	Math::Matrix scorenumbersMat;
	KdTexture scorenumbersTex;
	int m_scorenumbers[maxDigits] = {};//{}初期化
};
