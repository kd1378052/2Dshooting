#pragma once
#include "Scene/ResultScreen.h"
#include "Scene/GameScene.h"
#include "Scene/RankingScreen.h"
#include "Scene/TutorialScreen.h"

class SceneManager
{
public:
	
	static SceneManager& GetInstance()
	{
		static SceneManager instance;
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

	SceneManager(){}

	State* currentState = nullptr;
};

#define SCENEMANAGER SceneManager::GetInstance()
