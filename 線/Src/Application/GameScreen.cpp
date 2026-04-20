#include "GameScreen.h"

GameScreen::GameScreen()
{
	player.Init();
}

GameScreen::~GameScreen()
{
}

void GameScreen::Init()
{
	player.Init();
}

void GameScreen::Update()
{
	player.Update();
}

void GameScreen::Draw()
{
	player.Draw();

	// •¶š—ñ•\¦
	SHADER.m_spriteShader.DrawString(0, 0, "ƒQ[ƒ€‰æ–Ê", Math::Vector4(1, 1, 1, 1));

}