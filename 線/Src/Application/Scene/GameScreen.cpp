#include "GameScreen.h"
#include "../Game/Player.h"
#include "../Game/Enemy.h"

GameScreen::GameScreen()
{
	backTex.Load("Texture/back.png");

	m_player = new Player();
	m_player->Init();

	m_enemy = new Enemy();
	m_enemy->Init();
}

GameScreen::~GameScreen()
{
	backTex.Release();
	backX = 0;
	delete m_player;
	delete m_enemy;
}

void GameScreen::Init()
{
	m_player = new Player();
	m_enemy = new Enemy();
	m_player->Init();
	m_enemy->Init();
}

void GameScreen::Update()
{
	//”wŒiƒXƒNƒ[ƒ‹
	backX -= 5;

	if (backX < -1280)
	{
		backX = 0;
	}

	m_player->Update();
	m_enemy->Update();

	//”wŒi
	backMat1 = Math::Matrix::CreateTranslation(backX, 0, 0);
	backMat2 = Math::Matrix::CreateTranslation(backX + 1280, 0, 0);

}

void GameScreen::Draw()
{
	//”wŒi (ˆê–‡–Ú)
	SHADER.m_spriteShader.SetMatrix(backMat1);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//”wŒii“ñ–‡–Új
	SHADER.m_spriteShader.SetMatrix(backMat2);
	SHADER.m_spriteShader.DrawTex(&backTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	m_player->Draw();
	m_enemy->Draw();

	// •¶š—ñ•\¦
	SHADER.m_spriteShader.DrawString(0, 0, "ƒQ[ƒ€‰æ–Ê", Math::Vector4(1, 1, 1, 1));

}