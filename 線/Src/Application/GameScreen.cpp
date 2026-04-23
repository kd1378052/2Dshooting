#include "GameScreen.h"
#include "Player.h"

GameScreen::GameScreen()
{
	m_player = new Player();
	m_player->Init();

}

GameScreen::~GameScreen()
{
	delete m_player;
}

void GameScreen::Init()
{
	m_player = new Player();
	m_player->Init();
}

void GameScreen::Update()
{
	m_player->Update();
}

void GameScreen::Draw()
{
	m_player->Draw();

	// •¶š—ñ•\¦
	SHADER.m_spriteShader.DrawString(0, 0, "ƒQ[ƒ€‰æ–Ê", Math::Vector4(1, 1, 1, 1));

}