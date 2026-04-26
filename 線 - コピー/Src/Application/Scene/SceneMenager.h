#pragma once
#include "ResultScreen.h"
#include"SelectionScreen.h"
#include "RankingScreen.h"
#include "TutorialScreen.h"
#include "GameScreen.h"

class SceneMenager
{
public:
	
	static SceneMenager& GetInstance()
	{
		static SceneMenager instance;
		return instance;
	}

	void ChangState(State* newState)
	{
		delete currentState;//©‚±‚ê‚É‚µ‚Ä‚é‚ÆˆÀ‘S
		currentState = newState;
	}

	void Init()
	{
		currentState->Init();
	}

	void Update()
	{
		currentState->Update();
	}

	void Draw()
	{
		currentState->Draw();
	}
	
private:

	SceneMenager(){}

	State* currentState = nullptr;
};

#define SCENEMENAGER SceneMenager::GetInstance()
