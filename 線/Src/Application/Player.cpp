#include "Player.h"

Player::Player()
{
	playerTex.Load("Texture/player.png");

}

Player::~Player()
{
	playerTex.Release();

}

void Player::Init()
{
	playerX = -500;
	playerY = 0;
}

void Player::Update()
{
	//プレイヤー動き
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)playerX += m_moveSpeed;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)playerX -= m_moveSpeed;
	if (GetAsyncKeyState(VK_UP) & 0x8000)playerY += m_moveSpeed;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)playerY -= m_moveSpeed;

	//画面外に出ないようにする処理
	if (playerX > SCREEN_RIGHT - 35)
	{
		playerX = SCREEN_RIGHT - 35;
	}     //後で変える    ↑飛行機の半径
	if (playerX < SCREEN_LEFT + 35)
	{
		playerX = SCREEN_LEFT + 35;
	}
	if (playerY < SCREEN_BOTTOM + 35)
	{
		playerY = SCREEN_BOTTOM + 35;
	}
	if (playerY > SCREEN_TOP - 35)
	{
		playerY = SCREEN_TOP - 35;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		
	}

	playerMat = Math::Matrix::CreateTranslation(playerX, playerY, 0);
	
	
}

void Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(playerMat);
	SHADER.m_spriteShader.DrawTex(&playerTex, Math::Rectangle(64, 0, 64, 64), 1.0f);
	
	
}
