#include "GameScene.h"
#include "../SceneManager.h"


GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
}

void GameScene::Update()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		SCENEMANAGER.ChangState(new ResultScreen());

	}
}

void GameScene::Draw()
{
	SHADER.m_spriteShader.DrawString(0, 0, "ÉQÅ[ÉÄâÊñ ", Math::Vector4(1, 1, 1, 1));
}
